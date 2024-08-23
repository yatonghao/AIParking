/*
* 语音合成（Text To Speech，TTS）技术能够自动将任意文字实时转换为连续的
* 自然语音，是一种能够在任何时间、任何地点，向任何人提供语音信息服务的
* 高效便捷手段，非常符合信息时代海量数据、动态更新和个性化查询的需求。
*/
//export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/topeet/Desktop/tts/libs/x64

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "../../include/qtts.h"
#include "../../include/msp_cmn.h"
#include "../../include/msp_errors.h"
typedef int SR_DWORD;
typedef short int SR_WORD ;

/* wav音频头部格式 */
typedef struct _wave_pcm_hdr
{
	char            riff[4];                // = "RIFF"
	int				size_8;                 // = FileSize - 8
	char            wave[4];                // = "WAVE"
	char            fmt[4];                 // = "fmt "
	int				fmt_size;				// = 下一个结构体的大小 : 16

	short int       format_tag;             // = PCM : 1
	short int       channels;               // = 通道数 : 1
	int				samples_per_sec;        // = 采样率 : 8000 | 6000 | 11025 | 16000
	int				avg_bytes_per_sec;      // = 每秒字节数 : samples_per_sec * bits_per_sample / 8
	short int       block_align;            // = 每采样点字节数 : wBitsPerSample / 8
	short int       bits_per_sample;        // = 量化比特数: 8 | 16

	char            data[4];                // = "data";
	int				data_size;              // = 纯数据长度 : FileSize - 44 
} wave_pcm_hdr;

/* 默认wav音频头部数据 */
wave_pcm_hdr default_wav_hdr = 
{
	{ 'R', 'I', 'F', 'F' },
	0,
	{'W', 'A', 'V', 'E'},
	{'f', 'm', 't', ' '},
	16,
	1,
	1,
	16000,
	32000,
	2,
	16,
	{'d', 'a', 't', 'a'},
	0  
};
/* 文本合成 */
int text_to_speech(const char* src_text, const char* des_path, const char* params)
{
	int          ret          = -1;
	FILE*        fp           = NULL;
	const char*  sessionID    = NULL;
	unsigned int audio_len    = 0;
	wave_pcm_hdr wav_hdr      = default_wav_hdr;
	int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

	if (NULL == src_text || NULL == des_path)
	{
		printf("params is error!\n");
		return ret;
	}
	fp = fopen(des_path, "wb");
	if (NULL == fp)
	{
		printf("open %s error.\n", des_path);
		return ret;
	}
	/* 开始合成 */
	sessionID = QTTSSessionBegin(params, &ret);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionBegin failed, error code: %d.\n", ret);
		fclose(fp);
		return ret;
	}
	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSTextPut failed, error code: %d.\n",ret);
		QTTSSessionEnd(sessionID, "TextPutError");
		fclose(fp);
		return ret;
	}
	printf("正在合成 ...\n");
	fwrite(&wav_hdr, sizeof(wav_hdr) ,1, fp); //添加wav音频头，使用采样率为16000
	while (1) 
	{
		/* 获取合成音频 */
		const void* data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
		if (MSP_SUCCESS != ret)
			break;
		if (NULL != data)
		{
			fwrite(data, audio_len, 1, fp);
		    wav_hdr.data_size += audio_len; //计算data_size大小
		}
		if (MSP_TTS_FLAG_DATA_END == synth_status)
			break;
	}
	printf("\n");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSAudioGet failed, error code: %d.\n",ret);
		QTTSSessionEnd(sessionID, "AudioGetError");
		fclose(fp);
		return ret;
	}
	/* 修正wav文件头数据的大小 */
	wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);
	
	/* 将修正过的数据写回文件头部,音频文件为wav格式 */
	fseek(fp, 4, 0);
	fwrite(&wav_hdr.size_8,sizeof(wav_hdr.size_8), 1, fp); //写入size_8的值
	fseek(fp, 40, 0); //将文件指针偏移到存储data_size值的位置
	fwrite(&wav_hdr.data_size,sizeof(wav_hdr.data_size), 1, fp); //写入data_size的值
	fclose(fp);
	fp = NULL;
	/* 合成完毕 */
	ret = QTTSSessionEnd(sessionID, "Normal");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionEnd failed, error code: %d.\n",ret);
	}

	return ret;
}

void get_network_file()
{
	//1.初始化网络
    int  tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	//2.绑定服务器  
	//设置链接的服务器地址信息 
	struct sockaddr_in  addr;  
	addr.sin_family   = AF_INET; //IPV4 协议  
	addr.sin_port     = htons(9999); //端口
	addr.sin_addr.s_addr = inet_addr("0.0.0.0"); //服务器的IP 地址
		//解决端口复用
	int on=1;
	setsockopt(tcp_socket,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	on=1;
	setsockopt(tcp_socket,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));

		//2.绑定服务器地址信息
	int ret=bind(tcp_socket,(struct sockaddr *)&addr,sizeof(addr));
	if(ret < 0)
	{
		perror("");
		close(tcp_socket);
		return ;
	}
	else
	{
		printf("绑定成功\n");
	}

		//3.设置服务器为监听模式 
	ret=listen(tcp_socket,5);
	if(ret < 0)
	{
		perror("");
		close(tcp_socket);
		return ;
	}
	else
	{
		printf("设置监听成功\n");
	}
		//4.接收客户端的链接请求 
	printf("等待服务器链接进来\n");
	int  new_socket=accept(tcp_socket,NULL,NULL);
		 if(new_socket < 0)
		 {
			perror("");
			close(tcp_socket);
			return ;
		 }
		 else
		 {
			 printf("链接成功！！\n");
		 }

		char* text = (char*)malloc(1000);
		char temp_buffer[100];
		int total_size = 0;

		bzero(text, 1000);

		while (1) {
			bzero(temp_buffer, 100);
			int size = read(new_socket, temp_buffer, 99);
			if (size <= 0) {
				break;
			}
			
			// 确保接收的数据不会超出 text 缓冲区
			if (total_size + size >= 1000) {
				printf("接收到的数据过多，无法存储\n");
				break;
			}

			// 拼接到 text 缓冲区
			strncat(text, temp_buffer, size);
			total_size += size;
		}

		printf("收到待合成文本: %s\n", text);

	ret                  = MSP_SUCCESS;
	const char* login_params         = "appid = 1ca69c70, work_dir = .";//登录参数,appid与msc库绑定,请勿随意改动
	/*
	* rdn:           合成音频数字发音方式
	* volume:        合成音频的音量
	* pitch:         合成音频的音调
	* speed:         合成音频对应的语速
	* voice_name:    合成发音人
	* sample_rate:   合成音频采样率
	* text_encoding: 合成文本编码格式
	*
	*/
	const char* session_begin_params = "engine_type = local,voice_name=xiaoyan, text_encoding = UTF8, tts_res_path = fo|res/tts/xiaoyan.jet;fo|res/tts/common.jet, sample_rate = 16000, speed = 50, volume = 50, pitch = 50, rdn = 2";
	const char* filename             = "tts_sample.wav"; //合成的语音文件名称
	/* 用户登录 */
	ret = MSPLogin(NULL, NULL, login_params); //第一个参数是用户名，第二个参数是密码，第三个参数是登录参数，用户名和密码可在http://www.xfyun.cn注册获取
	if (MSP_SUCCESS != ret)
	{
		printf("MSPLogin failed, error code: %d.\n", ret);
		goto exit ;//登录失败，退出登录
	}
		/* 文本合成 */
	printf("开始合成 ...\n");
	ret = text_to_speech(text, filename, session_begin_params);
	if (MSP_SUCCESS != ret)
	{
		printf("text_to_speech failed, error code: %d.\n", ret);
	}
	printf("合成完毕\n");
	free(text);

	close(new_socket); 
		new_socket=accept(tcp_socket,NULL,NULL);
			 if(new_socket < 0)
			 {
				perror("");
				return ;
			 }
			 else
			 {
				 printf("链接成功！！\n");
			 }

	//把语音文件发出去
		int  audio_fd = open("tts_sample.wav",O_RDWR);
		if(audio_fd < 0)
		{
			perror("open");
			exit(0);
		}
		while(1)
		{
			
			//读取本地文件的数据 
			char buf[4096]={0}; 
			int size = read(audio_fd,buf,4096);
				if(size <= 0)
				{
					break;
				}
			
			//发送网络中 
			write(new_socket,buf,size);
			printf("已经成功发送%d个字节数据\n", size);
			
		}
		//关闭所有打开的文件 
		close(audio_fd);
exit:
	MSPLogout(); //退出登录
	close(new_socket);
	close(tcp_socket);
}

int main(int argc, char* argv[])
{
while(1)
{

	get_network_file();

}
}

