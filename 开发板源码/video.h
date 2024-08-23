#ifndef VIDEO_H
#define VIDEO_H
#include <QObject>
#include <QPixmap>
#include <opencv.hpp>
#include <opencv2/opencv.hpp>
#include "hyper_lpr_sdk.h"
#include "opencv2/opencv.hpp"
#include <QTimer>
#include <QDebug>
#include <QDateTime>
using namespace cv;
using namespace std;
class Video: public QObject
{
    Q_OBJECT
public:
    explicit Video(QObject *parent = nullptr);
    ~Video();
    void identify();
    void getOneFrame();
    void getFrame();
signals:
    void sendCarID(QString str);
    void sendFrame(QPixmap pix);
private:
    bool isDuplicate(const QString& plateNumber, const QDateTime& now);
    void processLicensePlate(const QString& plateNumber);

    QRegExp* regExp;
    VideoCapture cap;
    Mat srcImage;
    QPixmap mmp;
    QTimer* cap_timer;

    QString lastPlateNumber;
    QDateTime lastRecognized;
    const int timeWindowSeconds = 30;
};

#endif // VIDEO_H
