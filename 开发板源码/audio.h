#ifndef AUDIO_H
#define AUDIO_H
#include <QObject>
#include <QTcpSocket>
#include <QFile>
class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = nullptr);
    ~Audio();
    void play(QString str);
private:
    bool isPlaying = false;  // 用于跟踪播放状态
};

#endif // AUDIO_H
