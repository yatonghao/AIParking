#include "device.h"

#include <QDebug>

extern "C"
{
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
}

ParkingPole::ParkingPole(QObject *parent)
{
    this->sg90_fd = open("/dev/sg90", O_WRONLY);
    if(this->sg90_fd < 0)
    {
        qDebug() << "sg90 open failed";
        return;
    }
    else
    {
       qDebug() << "sg90 open success";
    }
    this->sr04_fd = open("/dev/sr04", O_RDWR);
    if(this->sr04_fd < 0)
    {
        qDebug() << "sr04 open failed";
        close(sg90_fd);
        return;
    }
    else
    {
        qDebug() << "sr04 open success";
        off();
        parkpole_scan_timer  = new QTimer(this);
        connect(parkpole_scan_timer,&QTimer::timeout,this,&ParkingPole::detect);
        parkpole_scan_timer->start(500);
    }
}

ParkingPole::~ParkingPole()
{
    if(sg90_fd>=0)
        close(sg90_fd);
    if(sr04_fd>=0)
        close(sr04_fd);
}

void ParkingPole::on()
{
    if(sg90_fd>=0)
    {
        unsigned char buf=90;
        write(this->sg90_fd, &buf, 1);
        qDebug() <<  "ParkingPole on";
    }

}

void ParkingPole::off()
{
    if(sg90_fd>=0)
    {
        unsigned char buf=180;
        write(this->sg90_fd, &buf, 1);
        qDebug() <<  "ParkingPole off";
    }
}

void ParkingPole::detect()
{
    int ret;
    int time_ns;
    if ((ret = read(this->sr04_fd, &time_ns, 4)) == 4)
    {
        if((int)(time_ns*340/2/1000000/10) < 100 && (int)(time_ns*340/2/1000000/10) >0)
        {
            qDebug() << "distance: "<<(int)(time_ns*340/2/1000000/10)<<"cm";
            emit isHavecar();
        }
    }
}




Rfid::Rfid(QObject *parent)
{
    int ret = -1;
    ret = PcdReset();
    if(ret < 0)
    {
        qDebug() <<  "rc522 rst error";
        return;
    }else
    {
        qDebug() <<  "rc522 rst success";
    }
    M500PcdConfigISOType ( 'A' );

    rfid_scan_timer  = new QTimer(this);
    connect(rfid_scan_timer,&QTimer::timeout,this,&Rfid::detect);
    rfid_scan_timer->start(2000);
}

Rfid::~Rfid()
{
    if(rc522_fd>=0)
        close(rc522_fd);
}

bool Rfid::isDuplicate(const QString &Number, const QDateTime &now)
{
    if (lastNumber==Number) {
        if (lastRecognized.secsTo(now) < timeWindowSeconds) {
            // 时间窗口内的重复识别
            return true;
        }
    }
    return false;
}

void Rfid::processLicensePlate(const QString &Number)
{
    QDateTime now = QDateTime::currentDateTime();

    if (isDuplicate(Number, now)) {
        return;
    }

    // 处理新的车牌识别
    lastNumber = Number;
    lastRecognized = now;
    emit isHavecard(Number);
}


void Rfid::detect()
{
    ucStatusReturn = PcdRequest ( PICC_REQIDL, ucArray_ID );
    if ( ucStatusReturn == MI_OK )
    {
       if ( PcdAnticoll ( ucArray_ID ) == MI_OK )
       {
             PcdSelect(ucArray_ID);      // 选卡
             ucStatusReturn = PcdAuthState(KEYA, (snr*4 + 3) , KeyValue, ucArray_ID );//校验密码
             if(ucStatusReturn !=  MI_OK)
             {
                sprintf(cStr, "%02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3]);
                QString cardId(cStr);
                qDebug() <<"The Card ID is: " << cardId;  //打印卡片ID
                processLicensePlate(cardId);
             }
             else
             {
                   qDebug() <<"rc522 card number err!\r\n";
             }
       }
       else
       {
             PcdHalt();
       }
    }
}

int Rfid::PcdReset()
{
    this->rc522_fd = open("/dev/nfc", O_RDWR);

    if(this->rc522_fd < 0)
    {
        qDebug() <<  "open rc522 error";
        return -1;
    }
    else
    {
        qDebug() <<  "open rc522 success";
    }

    WriteRawRC ( CommandReg, 0x0f );

    while ( ReadRawRC ( CommandReg ) & 0x10 );

     //定义发送和接收常用模式 和Mifare卡通讯，CRC初始值0x6363
     WriteRawRC ( ModeReg, 0x3D );
     WriteRawRC ( TReloadRegL, 30 );      //16位定时器低位
     WriteRawRC ( TReloadRegH, 0 );      //16位定时器高位
     WriteRawRC ( TModeReg, 0x8D );      //定义内部定时器的设置
     WriteRawRC ( TPrescalerReg, 0x3E );   //设置定时器分频系数
     WriteRawRC ( TxAutoReg, 0x40 );       //调制发送信号为100%ASK
     return 1;
}

void Rfid::WriteRawRC(unsigned char Address, unsigned char Value)
{
    unsigned char buf[2];

    buf[0] = Address;
    buf[1] = Value;
    write(this->rc522_fd,buf,2);
}

unsigned char Rfid::ReadRawRC(unsigned char Address)
{
    unsigned char buf[1];

    buf[0] = Address;
     read(this->rc522_fd,buf,1);
     return buf[0];
}

char Rfid::M500PcdConfigISOType(unsigned char ucType)
{
    if ( ucType == 'A')                     //ISO14443_A
     {
        ClearBitMask ( Status2Reg, 0x08 );
        WriteRawRC ( ModeReg, 0x3D );         //3F
        WriteRawRC ( RxSelReg, 0x86 );        //84
        WriteRawRC( RFCfgReg, 0x7F );         //4F
        WriteRawRC( TReloadRegL, 30 );
        WriteRawRC ( TReloadRegH, 0 );
        WriteRawRC ( TModeReg, 0x8D );
        WriteRawRC ( TPrescalerReg, 0x3E );
        usleep(10000);
        PcdAntennaOn ();//开天线
     }
     else
     {
        return MI_ERR;
     }
    return MI_OK;
}

void Rfid::ClearBitMask(unsigned char ucReg, unsigned char ucMask)
{
    unsigned char ucTemp;

    ucTemp = ReadRawRC (ucReg);
    WriteRawRC (ucReg, ucTemp & ( ~ ucMask)); // clear bit mask
}

void Rfid::PcdAntennaOn()
{
    unsigned char uc;

    uc = ReadRawRC (TxControlReg);
    if (! ( uc & 0x03 ))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}

void Rfid::SetBitMask(unsigned char ucReg, unsigned char ucMask)
{
    unsigned char ucTemp;

    ucTemp = ReadRawRC ( ucReg );
    WriteRawRC (ucReg, ucTemp | ucMask); // set bit mask
}

char Rfid::PcdRequest(unsigned char ucReq_code, unsigned char *pTagType)
{
    char cStatus;
    unsigned char ucComMF522Buf [ MAXRLEN ];
    unsigned int ulLen;

    //清理指示MIFARECyptol单元接通以及所有卡的数据通信被加密的情况
    ClearBitMask ( Status2Reg, 0x08 );
    //发送的最后一个字节的 七位
    WriteRawRC ( BitFramingReg, 0x07 );

    //ClearBitMask ( TxControlReg, 0x03 );
    //TX1,TX2管脚的输出信号传递经发送调制的13.56的能量载波信号
    //usleep(10000);
    SetBitMask ( TxControlReg, 0x03 );

    ucComMF522Buf [ 0 ] = ucReq_code;   //存入 卡片命令字

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE, ucComMF522Buf, 1, ucComMF522Buf,& ulLen );  //寻卡

    if ( ( cStatus == MI_OK ) && ( ulLen == 0x10 ) )  //寻卡成功返回卡类型
    {
       * pTagType = ucComMF522Buf[0];
       * ( pTagType + 1 ) = ucComMF522Buf[1];
    }
    else
    {
        cStatus = MI_ERR;
    }

    return cStatus;
}

char Rfid::PcdComMF522(unsigned char ucCommand, unsigned char *pInData, unsigned char ucInLenByte, unsigned char *pOutData, unsigned int *pOutLenBit)
{
    char cStatus = MI_ERR;
    unsigned char ucIrqEn   = 0x00;
    unsigned char ucWaitFor = 0x00;
    unsigned char ucLastBits;
    unsigned char ucN;
    unsigned int ul;

    switch ( ucCommand )
    {
       case PCD_AUTHENT:      //Mifare认证
          ucIrqEn   = 0x12;   //允许错误中断请求ErrIEn  允许空闲中断IdleIEn
          ucWaitFor = 0x10;   //认证寻卡等待时候 查询空闲中断标志位
          break;

       case PCD_TRANSCEIVE:   //接收发送 发送接收
          ucIrqEn   = 0x77;   //允许TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
          ucWaitFor = 0x30;   //寻卡等待时候 查询接收中断标志位与 空闲中断标志位
          break;

       default:
         break;
    }
    //IRqInv置位管脚IRQ与Status1Reg的IRq位的值相反
    WriteRawRC ( ComIEnReg, ucIrqEn | 0x80 );
    //Set1该位清零时，CommIRqReg的屏蔽位清零
    ClearBitMask ( ComIrqReg, 0x80 );
    //写空闲命令
    WriteRawRC ( CommandReg, PCD_IDLE );

    //置位FlushBuffer清除内部FIFO的读和写指针以及ErrReg的BufferOvfl标志位被清除
    SetBitMask ( FIFOLevelReg, 0x80 );

    for ( ul = 0; ul < ucInLenByte; ul ++ )
    {
        WriteRawRC ( FIFODataReg, pInData [ ul ] ); //写数据进FIFOdata
    }

    WriteRawRC ( CommandReg, ucCommand );         //写命令

    if ( ucCommand == PCD_TRANSCEIVE )
    {
        //StartSend置位启动数据发送 该位与收发命令使用时才有效
        SetBitMask(BitFramingReg,0x80);
    }

    ul = 1000;                             //根据时钟频率调整，操作M1卡最大等待时间25ms

    do                                     //认证 与寻卡等待时间
    {
         ucN = ReadRawRC ( ComIrqReg );    //查询事件中断
         ul --;
    } while ( ( ul != 0 ) && ( ! ( ucN & 0x01 ) ) && ( ! ( ucN & ucWaitFor ) ) );

    ClearBitMask ( BitFramingReg, 0x80 );  //清理允许StartSend位

    if ( ul != 0 )
    {
      //读错误标志寄存器BufferOfI CollErr ParityErr ProtocolErr
      if ( ! ( ReadRawRC ( ErrorReg ) & 0x1B ) )
      {
        cStatus = MI_OK;

        if ( ucN & ucIrqEn & 0x01 )       //是否发生定时器中断
          cStatus = MI_NOTAGERR;

        if ( ucCommand == PCD_TRANSCEIVE )
        {
          //读FIFO中保存的字节数
          ucN = ReadRawRC ( FIFOLevelReg );

          //最后接收到得字节的有效位数
          ucLastBits = ReadRawRC ( ControlReg ) & 0x07;

          if ( ucLastBits )

            //N个字节数减去1（最后一个字节）+最后一位的位数 读取到的数据总位数
            * pOutLenBit = ( ucN - 1 ) * 8 + ucLastBits;
          else
            * pOutLenBit = ucN * 8;      //最后接收到的字节整个字节有效

          if ( ucN == 0 )
            ucN = 1;

          if ( ucN > MAXRLEN )
            ucN = MAXRLEN;

          for ( ul = 0; ul < ucN; ul ++ )
            pOutData [ ul ] = ReadRawRC ( FIFODataReg );

          }
      }
      else
        cStatus = MI_ERR;
    }

    SetBitMask ( ControlReg, 0x80 );           // stop timer now
    WriteRawRC ( CommandReg, PCD_IDLE );

    return cStatus;
}

char Rfid::PcdAnticoll(unsigned char *pSnr)
{
    char cStatus;
    unsigned char uc, ucSnr_check = 0;
    unsigned char ucComMF522Buf [ MAXRLEN ];
    unsigned int ulLen;

    //清MFCryptol On位 只有成功执行MFAuthent命令后，该位才能置位
    ClearBitMask ( Status2Reg, 0x08 );
    //清理寄存器 停止收发
    WriteRawRC ( BitFramingReg, 0x00);
    //清ValuesAfterColl所有接收的位在冲突后被清除
    ClearBitMask ( CollReg, 0x80 );

    ucComMF522Buf [ 0 ] = 0x93;           //卡片防冲突命令
    ucComMF522Buf [ 1 ] = 0x20;

    cStatus = PcdComMF522 ( PCD_TRANSCEIVE,
                            ucComMF522Buf,
                            2,
                            ucComMF522Buf,
                            & ulLen);      //与卡片通信

    if ( cStatus == MI_OK)                //通信成功
    {
      for ( uc = 0; uc < 4; uc ++ )
      {
         * ( pSnr + uc )  = ucComMF522Buf [ uc ]; //读出UID
         ucSnr_check ^= ucComMF522Buf [ uc ];
      }

      if ( ucSnr_check != ucComMF522Buf [ uc ] )
        cStatus = MI_ERR;
    }

    SetBitMask ( CollReg, 0x80 );

    return cStatus;
}

char Rfid::PcdSelect(unsigned char *pSnr)
{
    char ucN;
    unsigned char uc;
    unsigned char ucComMF522Buf [ MAXRLEN ];
    unsigned int  ulLen;


    ucComMF522Buf [ 0 ] = PICC_ANTICOLL1;
    ucComMF522Buf [ 1 ] = 0x70;
    ucComMF522Buf [ 6 ] = 0;

    for ( uc = 0; uc < 4; uc ++ )
    {
      ucComMF522Buf [ uc + 2 ] = * ( pSnr + uc );
      ucComMF522Buf [ 6 ] ^= * ( pSnr + uc );
    }

    CalulateCRC ( ucComMF522Buf, 7, & ucComMF522Buf [ 7 ] );

    ClearBitMask ( Status2Reg, 0x08 );

    ucN = PcdComMF522 ( PCD_TRANSCEIVE,
                       ucComMF522Buf,
                       9,
                       ucComMF522Buf,
                       & ulLen );

    if ( ( ucN == MI_OK ) && ( ulLen == 0x18 ) )
      ucN = MI_OK;
    else
      ucN = MI_ERR;

    return ucN;
}

void Rfid::CalulateCRC(unsigned char *pIndata, unsigned char ucLen, unsigned char *pOutData)
{
    unsigned char uc, ucN;

    ClearBitMask(DivIrqReg,0x04);

    WriteRawRC(CommandReg,PCD_IDLE);

    SetBitMask(FIFOLevelReg,0x80);

    for ( uc = 0; uc < ucLen; uc ++)
      WriteRawRC ( FIFODataReg, * ( pIndata + uc ) );

    WriteRawRC ( CommandReg, PCD_CALCCRC );

    uc = 0xFF;

    do
    {
        ucN = ReadRawRC ( DivIrqReg );
        uc --;
    } while ( ( uc != 0 ) && ! ( ucN & 0x04 ) );

    pOutData [ 0 ] = ReadRawRC ( CRCResultRegL );
    pOutData [ 1 ] = ReadRawRC ( CRCResultRegM );
}

char Rfid::PcdAuthState(unsigned char ucAuth_mode, unsigned char ucAddr, unsigned char *pKey, unsigned char *pSnr)
{
    char cStatus;
    unsigned char uc, ucComMF522Buf [ MAXRLEN ];
    unsigned int ulLen;

    ucComMF522Buf [ 0 ] = ucAuth_mode;
    ucComMF522Buf [ 1 ] = ucAddr;

    for ( uc = 0; uc < 6; uc ++ )
      ucComMF522Buf [ uc + 2 ] = * ( pKey + uc );

    for ( uc = 0; uc < 6; uc ++ )
      ucComMF522Buf [ uc + 8 ] = * ( pSnr + uc );

    cStatus = PcdComMF522 ( PCD_AUTHENT,
                            ucComMF522Buf,
                            12,
                            ucComMF522Buf,
                            & ulLen );

    if ( ( cStatus != MI_OK ) || ( ! ( ReadRawRC ( Status2Reg ) & 0x08 ) ) )
      cStatus = MI_ERR;

    return cStatus;
}

char Rfid::PcdHalt()
{
    unsigned char ucComMF522Buf [ MAXRLEN ];
    unsigned int  ulLen;


    ucComMF522Buf [ 0 ] = PICC_HALT;
    ucComMF522Buf [ 1 ] = 0;

     CalulateCRC ( ucComMF522Buf, 2, & ucComMF522Buf [ 2 ] );
    PcdComMF522 ( PCD_TRANSCEIVE,
                  ucComMF522Buf,
                  4,
                  ucComMF522Buf,
                  & ulLen );

    return MI_OK;
}
