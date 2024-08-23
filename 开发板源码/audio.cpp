#include "audio.h"

Audio::Audio(QObject *parent) : QObject(parent)
{
}

Audio::~Audio()
{
}

void Audio::play(QString str)
{
    if(isPlaying)
         return;
    isPlaying = true;
    QTcpSocket *tcpSocket=new QTcpSocket();
    tcpSocket->connectToHost("10.203.56.214", 9999);
    if (!tcpSocket->waitForConnected(1000)) { // 阻塞等待连接，5秒超时
            qDebug() << "连接失败：" << tcpSocket->errorString();
            delete tcpSocket;
            return;
        }

    QByteArray data = str.toUtf8();
    const char* cStr = data.constData();
    tcpSocket->write(cStr, data.size());
    tcpSocket->flush();

    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    tcpSocket->connectToHost("10.203.56.214", 9999);
    if (!tcpSocket->waitForConnected(1000)) { // 阻塞等待连接，5秒超时
            qDebug() << "连接失败：" << tcpSocket->errorString();
            delete tcpSocket;
            return;
        }

    QFile file("voicefile.wav");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "无法打开文件进行写入";
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        delete tcpSocket;
        return;
    }

    QByteArray buffer;
    while (tcpSocket->waitForReadyRead(10000)) {
        QByteArray data = tcpSocket->readAll();
        if (!data.isEmpty()) {
            buffer.append(data);
            qDebug() << "接收到" << data.size() << "字节的数据";
        } else {
            qDebug() << "收到空数据包";
        }
    }

    if (buffer.isEmpty()) {
        qDebug() << "未接收到任何数据，文件为空";
    } else {
        file.write(buffer);
        file.flush();
        qDebug() << "接收并保存了" << buffer.size() << "字节的数据";
    }
   tcpSocket->disconnectFromHost();
   tcpSocket->close();
   delete tcpSocket;

   // 播放接收到的音频文件
   system("aplay voicefile.wav");
   isPlaying = false;
}


