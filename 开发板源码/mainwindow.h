#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include "mypushbutton.h"
#include "easyInput/easyinput.h"
#include "menuwindow.h"
#include <QProcess>
#include <QTimer>

#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //显示背景
    QLabel * pic_lable;


    /* 文本编辑区 */
    QLineEdit * name_lineEdit;
    QLineEdit * passwd_lineEdit;



//    //输入法
    easyInput *eInput;
    bool   inputFlag;   //是否开启输入法标志位

    //登入按钮
    myPushButton * login_pushbutton;

    //主界面
    MenuWindow * menuwindow;

    //进程
    QProcess * my_pro;
    QTimer * pro_timer;
    QTimer * pro_timer2;


private:
    Ui::MainWindow *ui;

    bool eventFilter(QObject *watched, QEvent *event);

private slots:

};
#endif // MAINWINDOW_H
