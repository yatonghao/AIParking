#ifndef ADDUSER_H
#define ADDUSER_H
#include "easyInput/easyinput.h"
#include <QFrame>
namespace Ui {
class addUser;
}

class addUser : public QFrame
{
    Q_OBJECT

public:
    explicit addUser(QWidget *parent = nullptr);
    ~addUser();

    //输入法
    easyInput *eInput;
    bool   inputFlag;   //是否开启输入法标志位
signals:
    void menuShow();
    void addUserSignal();

public slots:
void showAndClean();
private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

public:
    QString username;
    QString phone;
    QString nfcCardNumber;
    QString licensePlate;
private:
    Ui::addUser *ui;

    bool eventFilter(QObject *watched, QEvent *event);

};

#endif // ADDUSER_H
