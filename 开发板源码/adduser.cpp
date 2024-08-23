#include "adduser.h"
#include "ui_adduser.h"

addUser::addUser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::addUser)
{
    ui->setupUi(this);


    eInput = new easyInput(this);//输入法实例化
    eInput->installEventFilter(this);//安装事件过滤器
    inputFlag = true;
    this->setFocus(); // 界面初始化时，先把焦点在this处，否则输入法会先出现
}

addUser::~addUser()
{
    delete ui;
}

void addUser::showAndClean()
{
    ui->name->clear();
    ui->phone->clear();
    ui->cardId->clear();
    ui->carId->clear();
    this->show();
}


void addUser::on_pushButton_2_clicked()
{
    username = ui->name->text();
    phone = ui->phone->text();
    nfcCardNumber = ui->cardId->text();
    licensePlate = ui->carId->text();
    emit addUserSignal();
}

void addUser::on_pushButton_clicked()
{
    emit menuShow();
}

bool addUser::eventFilter(QObject *watched, QEvent *event)
{
        if(watched == eInput)
            switch (event->type()) {
            case QEvent::Hide:
                break;
            case QEvent::Show:
            {
                if(inputFlag == false){
                    eInput->hide();
                    return false;
                }
            }
                break;
            default:
                break;
            }
        return QWidget::eventFilter(watched,event);//将事件传递给父类
}
