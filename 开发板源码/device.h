#ifndef USART_H
#define USART_H
#include <QObject>
#include "rc522.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>
#include <asm/ioctls.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <QTimer>
#include <QDateTime>
#define  MAXRLEN 18
//停车杆类
class ParkingPole: public QObject
{
    Q_OBJECT
public:
    explicit ParkingPole(QObject *parent = nullptr);
    ~ParkingPole();
public slots:
    void on();
    void off();
    void detect();

signals:
    void isHavecar();
private:
    int sg90_fd =-1;
    int sr04_fd =-1;
    QTimer* parkpole_scan_timer;
};


//rfid 卡类
class Rfid: public QObject
{
    Q_OBJECT
public:
    explicit Rfid(QObject *parent = nullptr);
    ~Rfid();
public slots:
    void detect();
    
signals:
    void isHavecard(QString);
private:
    void processLicensePlate(const QString &Number);
    bool isDuplicate(const QString &Number, const QDateTime &now);

    int PcdReset(void);
    void WriteRawRC(unsigned char Address, unsigned char Value);
    unsigned char ReadRawRC(unsigned char Address);
    char M500PcdConfigISOType ( unsigned char ucType );
    void ClearBitMask(unsigned char ucReg, unsigned char ucMask);
    void PcdAntennaOn(void);
    void SetBitMask(unsigned char ucReg, unsigned char ucMask);
    char PcdRequest (unsigned char ucReq_code, unsigned char * pTagType);
    char PcdComMF522 ( unsigned char ucCommand, unsigned char * pInData, unsigned char ucInLenByte, unsigned char * pOutData,unsigned int * pOutLenBit );
    char PcdAnticoll ( unsigned char * pSnr );
    char PcdSelect ( unsigned char * pSnr );
    void CalulateCRC ( unsigned char * pIndata, unsigned char ucLen, unsigned char * pOutData );
    char PcdAuthState ( unsigned char ucAuth_mode, unsigned char ucAddr, unsigned char * pKey, unsigned char * pSnr );
    char PcdHalt( void );

    unsigned char KeyValue[6]={0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // 卡A密钥
    char cStr [ 30 ];
    unsigned char ucArray_ID [4];    /*先后存放IC卡的类型和UID(IC卡序列号)*/
    unsigned char ucStatusReturn, snr=1;      /*返回状态*/
    int rc522_fd;
    QTimer* rfid_scan_timer;

    QString lastNumber;
    QDateTime lastRecognized;
    const int timeWindowSeconds = 30;
};


#endif // USART_H
