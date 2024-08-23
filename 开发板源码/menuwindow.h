#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "mypushbutton.h"
#include <QTimer>
#include <QTime>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>
#include <QTableWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QListWidgetItem>
#include <QSqlError>
#include <QSqlQuery>
#include "device.h"
#include "easyinput.h"
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include "config.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <QThread>
#include <QLineEdit>
#include "adduser.h"
#include <QVariant>
#include <QPixmap>
#include "video.h"
#include "audio.h"

class MenuWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MenuWindow(QWidget *parent = nullptr);
   ~MenuWindow();

    /********************界面设计*********************/
    //返回按钮
    myPushButton * exit_button;
    QTimer * exitbt_timer;
    //图片
    QLabel * pic_label;


    /**********************多窗口*********************/
    //窗口表
    QTabWidget * tabwight;
    //页面
    QWidget *tab1;
    QWidget *tab2;
    QWidget *tab3;
    QWidget *tab4;
    QWidget *tab5;
    QWidget *tab6;


    /*****************多窗口1：基本信息*****************/
    //信息表格1
    QTableWidget * info_tablewidget;
    int curr_row;// 行
    myPushButton * add_button;
    addUser* add_user_widget;


    /*****************多窗口2：费用设置*****************/
    QLabel * msg1_label;
    QDoubleSpinBox * min_price_dsbox;
    float price_min;

    /*****************多窗口3：车辆管理*****************/
    QLabel * msg2_label;
    //信息表格
    QTableWidget * park_tablewidget;

    /*****************多窗口4：缴费*****************/
    QLabel * msg3_label;//请输入充值卡号：
    QLabel * msg4_label;//请输入充值金额
    QLabel * msg5_label;//请输入密码

    bool pay_flag;
    QWidget * pay_widget;
    QLineEdit * cardid_lineEdit;
    QLineEdit * money_lineEdit;
    QLineEdit * manger_pswd_lineEdit;
    QPushButton * pay_pushbutton;
    QPushButton * sure_pushbutton;
    //信息表格
    QTableWidget * pay_tablewidget;

     /************************多窗口5：视频监控***********************/
    bool video_flag;
    QLabel * video_lable;
    QPushButton * video_pushbutton;


    /*****************多窗口5：调试********************/
    //停车杆开关
    myPushButton * popl_on_button;
    myPushButton * popl_off_button;
    QPushButton * rfid_pushbutton;
    QLabel * rfid_lable;

    QLabel * msg6_label;//停车杆
    QLabel * msg7_label;//

    /**********************输入法*********************/
    //输入法
    easyInput *eInput;
    bool   inputFlag;   //是否开启输入法标志位


    /**********************设备*********************/
    //停车杆
    QThread *parkpole_thread;
    ParkingPole *parkpole;
    QTimer* parkPoleCloseTimer;

    //rfid设备
    QThread *rfid_thread;
    Rfid * rfid;
    QString cardId;

    //摄像头
    Video* video;
    QTimer * video_timer;
    QThread *video_thread;

    //播放声音
    QThread *audio_thread;
    Audio *audio;


    /*********数据库处理函数**********/
    int sql_to_table(QString table_name);

private:
    bool eventFilter(QObject *watched, QEvent *event);


    QString fileName;
    QSqlDatabase db;    //数据库管理器
    QSqlQuery *sql_cmd;  //命令管理器

signals:
    void loginshow();
    void addUserShow();
    void parkpole_on();
    void parkpole_off();
    void getFrame();
    void playAudio(QString str);

public slots:
    void min_price_dsbox_slot(double d);
    void isHaveCarOut(QString cardId);
    void isHaveCarIn(QString carId);
    void menuShow();
    void addUserToDatabase();
private:
    bool checkUsersExists(const QString& licensePlate);
    bool checkLicensePlateExists(const QString& licensePlate);
    bool insertVehicleEntry(const QString& licensePlate);

    double calculateParkingCost(const QString& licensePlate, double ratePerHour);
};

#endif // MENUWINDOW_H
