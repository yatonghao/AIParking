#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "device.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);//去除标题栏
    this->setFixedSize(800,480);//设置界面固定大小

    //创建主界面对象
    menuwindow = new MenuWindow();
    menuwindow->hide();
    //主界面返回处理
    connect(menuwindow,&MenuWindow::loginshow,[=](){
        this->show();
        menuwindow->hide();
    });

    //显示图片lable
    pic_lable = new QLabel(this);
    pic_lable->setGeometry(0,0,800,480);
    pic_lable->setStyleSheet("QLabel{border-image: url(:/pic/login_menu.png);}");


    /* 文本编辑区 */
    name_lineEdit = new QLineEdit(this);
    name_lineEdit->setStyleSheet(TEXTEDIT_STYLE);
    name_lineEdit->setFont(QFont("宋体", 11));//设置默认字体：字体，字体大小
    name_lineEdit->setGeometry(395,220,140,25);//设置位置


    passwd_lineEdit = new QLineEdit(this);
    passwd_lineEdit->setStyleSheet(TEXTEDIT_STYLE);
    passwd_lineEdit->setFont(QFont("宋体", 11));//设置默认字体：字体，字体大小
    passwd_lineEdit->setGeometry(395,273,140,25);
    passwd_lineEdit->setEchoMode(QLineEdit::Password);//密码模式


//    passwd_lineEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //关闭水平滚动条
//    passwd_lineEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //关闭垂直滚动条


    //输入法
    eInput = new easyInput(this);//输入法实例化
    eInput->installEventFilter(this);//安装事件过滤器
    inputFlag = true;
    this->setFocus(); // 界面初始化时，先把焦点在this处，否则输入法会先出现

    //按钮
    login_pushbutton = new myPushButton(":/pic/login.png","",150,50);
    login_pushbutton->setParent(this);
    login_pushbutton->move(340,350-120);

    //钮按下处理
    connect(login_pushbutton,&myPushButton::clicked,[=](){
        login_pushbutton->zoom1();//弹跳
        login_pushbutton->zoom2();
         QString name = name_lineEdit->text();
         QString passwd = passwd_lineEdit->text();

         if(name == QString("1") && passwd == "1")
         {
              this->hide();
              menuwindow->show();
         }
         else
         {
             QMessageBox::warning(this, tr("密码提示"),tr("密码错误！\n"),QMessageBox::Ok);
         }
        });

}

MainWindow::~MainWindow()
{
    delete ui;
}

//过滤事件
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == eInput)
        switch (event->type()) {
        case QEvent::Hide:

            name_lineEdit->setGeometry(395,220,140,25);
            passwd_lineEdit->setGeometry(395,273,140,25);
            pic_lable->setGeometry(0,0,800,480);
            login_pushbutton->move(340,350);
            break;
        case QEvent::Show:
        {
            if(inputFlag == false){
                eInput->hide();
                return false;
            }
            name_lineEdit->setGeometry(395,220-65,140,25);
            passwd_lineEdit->setGeometry(395,273-70,140,25);
            pic_lable->setGeometry(0,0,800,350);
            login_pushbutton->move(340,350-120);

        }
            break;
        default:
            break;
        }
    return QWidget::eventFilter(watched,event);//将事件传递给父类
}





