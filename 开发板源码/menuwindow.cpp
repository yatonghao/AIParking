#include "menuwindow.h"
#include <QDebug>


MenuWindow::MenuWindow(QWidget *parent) : QMainWindow(parent)
{

    /******************硬件设备初始化************************/
    //停车杆
    parkpole_thread = new QThread();
    parkpole = new ParkingPole;
    parkpole->moveToThread(parkpole_thread);
    parkpole_thread->start();
    connect(this,&MenuWindow::parkpole_on,parkpole,&ParkingPole::on);
    connect(this,&MenuWindow::parkpole_off,parkpole,&ParkingPole::off);
    parkPoleCloseTimer = new QTimer(this);
    connect(parkPoleCloseTimer,&QTimer::timeout, parkpole,&ParkingPole::off);

    //RFID
    rfid_thread = new QThread();
    rfid = new Rfid;
    rfid->moveToThread(rfid_thread);
    rfid_thread->start();
    connect(rfid,&Rfid::isHavecard,this,&MenuWindow::isHaveCarOut); //出库

    //拍照车牌检测
    video = new Video;
    video_thread = new QThread();
    video->moveToThread(video_thread);
    video_thread->start();
    connect(this,&MenuWindow::getFrame,video,&Video::getFrame);
    connect(video,&Video::sendCarID, this,&MenuWindow::isHaveCarIn);//入库

    connect(parkpole,&ParkingPole::isHavecar,video,&Video::identify);//检测


    //播放声音
    audio_thread = new QThread();
    audio = new Audio;
    audio->moveToThread(audio_thread);
    audio_thread->start();
    connect(this,&MenuWindow::playAudio,audio,&Audio::play);

    /********************界面设计*************************/
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(800,480);//设置界面固定大小
    //设置背景
    this->setStyleSheet("MenuWindow{background-color: rgb(120, 181, 255);}");
    //显示图片lable “XXX停车系统”
    pic_label = new QLabel(this);
    pic_label->setGeometry(0,0,800,140);
    pic_label->setStyleSheet("QLabel{border-image: url(:/pic/menu.png);}");

    //返回退出按钮
    exit_button=new myPushButton(":/pic/exit.png","",60,60);
    exit_button->setParent(this);
    exit_button->move(740,0);
    //返回按钮动画定时器
    exitbt_timer =  new QTimer(this);
    //返回退出按钮下处理
    connect(exit_button,&myPushButton::clicked,[=](){
    exit_button->zoom1();//弹跳
    exit_button->zoom2();
    exitbt_timer->start(500);
    connect(exitbt_timer,&QTimer::timeout,[=](){
        exitbt_timer->stop();
        emit loginshow();
       });
    });

    /**********************输入法*********************/
    eInput = new easyInput(this);//输入法实例化
    eInput->installEventFilter(this);//安装事件过滤器
    inputFlag = true;
    this->setFocus(); // 界面初始化时，先把焦点在this处，否则输入法会先出现


    /**********************多窗口*********************/
    //窗口列表
    tabwight = new QTabWidget(this);
    tabwight->setGeometry(0,100,800,350);
    tabwight->setStyleSheet(TABWIGHT_STYLE);//设置样式表
    tabwight->setFocusPolicy(Qt::NoFocus);   //去除虚线边框
    tab1=new QWidget(this);//页面
    tab2=new QWidget(this);
    tab3=new QWidget(this);
    tab4=new QWidget(this);
    tab5=new QWidget(this);
    tab6=new QWidget(this);

    tabwight->setTabPosition(QTabWidget::North);//设置选项卡的方位东南西北，默认在上方
    tabwight->addTab(tab1,QIcon(":/pic/info.png"),tr("基本信息"));//在后面添加选项卡
    tabwight->addTab(tab2,QIcon(":/pic/card.png"),tr("费用设置"));
    tabwight->addTab(tab3,QIcon(":/pic/car.png"),tr("车辆管理"));//在后面添加带图标的选项卡
    tabwight->addTab(tab4,QIcon(":/pic/price.png"),tr("缴费"));//在后面添加带图标的选项卡
    tabwight->addTab(tab5,QIcon(":/pic/video.png"),tr("视频监控"));//在后面添加带图标的选项卡
    tabwight->addTab(tab6,QIcon(":/pic/debug.png"),tr("调试"));//在后面添加带图标的选项卡
    tabwight->setIconSize(QSize(23,23));//设置图标的大小(选项卡的大小也会改变)
    tabwight->setMovable(true);
    tabwight->setTabToolTip(0,tr("Beautiful"));//鼠标悬停弹出提示


    /**********************多窗口1：基本信息*********************/
   //信息表格1
    info_tablewidget = new QTableWidget(tab1);
    info_tablewidget->setGeometry(0,0,800,250);
    info_tablewidget->setStyleSheet(TABLE_WIDGET_STYLE);//样式
    info_tablewidget->setColumnCount(4); //设置列数
    info_tablewidget->setColumnWidth(0, 90);  //0 设置列宽
    info_tablewidget->setColumnWidth(1, 190); //1 设置列宽
    info_tablewidget->setColumnWidth(2, 190);  //2 设置列宽
    info_tablewidget->setColumnWidth(3, 190);  //3 设置列宽  
    QStringList header;
    header<<"姓名"<<"车牌号"<<"卡号"<<"电话";
    info_tablewidget->setHorizontalHeaderLabels(header);
    add_user_widget = new addUser(tab1);
    add_user_widget->hide();
    connect(add_user_widget,&addUser::menuShow,this,&MenuWindow::menuShow);
    connect(add_user_widget,&addUser::addUserSignal,this,&MenuWindow::addUserToDatabase);
    connect(this,&MenuWindow::addUserShow,add_user_widget,&addUser::showAndClean);

    /**********************多窗口2：费用设置*********************/

    //文字
    msg1_label = new QLabel(tab2);
    msg1_label->setText("每分钟费用(元)：");
    QFont ft;
    ft.setPointSize(23);
    msg1_label->setFont(ft);
    msg1_label->setGeometry(100,50,23*8,23);

    //价格选择
    min_price_dsbox = new  QDoubleSpinBox(tab2);
    min_price_dsbox->setGeometry(100+23*8,50-3,80,30);
    price_min = 1.00;//元
    min_price_dsbox->setValue(price_min);
    connect(min_price_dsbox,SIGNAL(valueChanged(double)),this,SIGNAL(min_price_dsbox_slot(double)));


    /**********************多窗口3：车辆管理*********************/

    //文字
    msg2_label = new QLabel(tab3);
    msg2_label->setText("车库现有车辆");
    ft.setPointSize(23);
    msg2_label->setFont(ft);
    msg2_label->setGeometry(30,5,200,23);

    //信息表格1
    park_tablewidget = new QTableWidget(tab3);
    park_tablewidget->setGeometry(0,30,800,250);
    park_tablewidget->setStyleSheet(TABLE_WIDGET_STYLE2);//样式
    park_tablewidget->setColumnCount(3); //设置列数
    park_tablewidget->setColumnWidth(0, 80);  //0 设置列宽
    park_tablewidget->setColumnWidth(1, 160); //1 设置列宽
    park_tablewidget->setColumnWidth(2, 160); //2 设置列宽
    QStringList header1;
    header1<<"车牌号"<<"入库时间" << "出库时间";
    park_tablewidget->setHorizontalHeaderLabels(header1);


    /**********************多窗口4：缴费*********************/
    pay_flag = 0; //显示缴费记录界面
    //信息表格1
    pay_tablewidget = new QTableWidget(tab4);
    pay_tablewidget->setGeometry(0,0,800,250);
    //pay_tablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    pay_tablewidget->setStyleSheet(TABLE_WIDGET_STYLE3);//样式
    pay_tablewidget->setColumnCount(3); //设置列数
    pay_tablewidget->setColumnWidth(0, 80);  //0 设置列宽
    pay_tablewidget->setColumnWidth(1, 180); //1 设置列宽
    pay_tablewidget->setColumnWidth(2, 180);  //2 设置列宽
    QStringList header2;
    header2<<"姓名"<<"卡号"<<"余额";
    pay_tablewidget->setHorizontalHeaderLabels(header2);


    //支付界面处理
     pay_widget = new QWidget(tab4);
     pay_widget->setGeometry(0,0,800,350);
     msg3_label = new QLabel(pay_widget);
     msg3_label->setText("请输入充值卡号：");
     msg3_label->setFont(ft);
     msg3_label->setGeometry(150,50+5,23*8,23);

     msg4_label = new QLabel(pay_widget);
     msg4_label->setText("请输入充值金额：");
     msg4_label->setFont(ft);
     msg4_label->setGeometry(150,50+50,23*8,23);

     msg5_label = new QLabel(pay_widget);
     msg5_label->setText("管理员确认密码：");
     msg5_label->setFont(ft);
     msg5_label->setGeometry(150,50+95,23*8,23);

    cardid_lineEdit = new QLineEdit(pay_widget);
    cardid_lineEdit->setGeometry(150+23*9,50+5-2,160,28);

    money_lineEdit = new QLineEdit(pay_widget);
    money_lineEdit->setGeometry(150+23*9,50+50-2,160,28);

    manger_pswd_lineEdit = new QLineEdit(pay_widget);
    manger_pswd_lineEdit->setGeometry(150+23*9,50+95-2,160,28);
    manger_pswd_lineEdit->setEchoMode(QLineEdit::Password);//密码模式

    sure_pushbutton= new QPushButton(pay_widget);
    sure_pushbutton->setGeometry(280,50+160,110,40);
    sure_pushbutton->setStyleSheet(PUSHBUTTON_STYLE);
    sure_pushbutton->setText("确认充值");
    connect(sure_pushbutton,&QPushButton::clicked,[=](){
    QString passwd = manger_pswd_lineEdit->text();

    if(passwd == QString("1"))//密码正确
    {
        QString cardid = cardid_lineEdit->text();//获取卡号
        double pay_money = money_lineEdit->text().toDouble();//获取支付金额
        //修改数据库表格中的数据
        sql_cmd->prepare("UPDATE Users SET money = money + :amount WHERE NFCId = :cardid");
           sql_cmd->bindValue(":amount", pay_money);
           sql_cmd->bindValue(":cardid", cardid);
           if (sql_cmd->exec()) {
               if (sql_cmd->numRowsAffected() <= 0) {
                   qDebug() << "User not found or balance unchanged.";
               }
               else
               {
                   QMessageBox::warning(this, tr("提示"),tr("充值成功！\n"),QMessageBox::Ok);
                   sql_to_table("money_info");
               }
           } else {
               qDebug() << "Recharge failed:" << sql_cmd->lastError();
               QMessageBox::warning(this, tr("提示"),tr("没有此卡号信息！\n"),QMessageBox::Ok);
           }
    }
    else
    {
        QMessageBox::warning(this, tr("提示"),tr("密码错误！\n"),QMessageBox::Ok);
    }

    });
    pay_widget->hide();
    //支付按钮
    pay_pushbutton = new QPushButton(tab4);
    pay_pushbutton->setGeometry(720,180,80,40);
    pay_pushbutton->setStyleSheet(PUSHBUTTON_STYLE);
    pay_pushbutton->setText("充值");
    connect(pay_pushbutton,&QPushButton::clicked,[=](){
       pay_flag = !pay_flag;
        if(pay_flag==1)//显示充值界面
        {
            pay_widget->show();
            pay_tablewidget->hide();
            pay_pushbutton->setText("返回");
        }
        else
        {
            pay_widget->hide();
            pay_tablewidget->show();
            pay_pushbutton->setText("充值");
        }

    });


    /************************多窗口5：视频监控***********************/

    video_lable = new QLabel(tab5);
    video_lable->setGeometry(0,0,500,300);

    video_flag = 0;
    video_pushbutton= new QPushButton(tab5);
    video_pushbutton->setGeometry(600,240,110,40);
    video_pushbutton->setStyleSheet(PUSHBUTTON_STYLE);
    video_pushbutton->setText("开启监控");

    video_timer = new QTimer(this);
    connect(video_timer,&QTimer::timeout,[=](){
        emit getFrame();
    });
    connect(video,&Video::sendFrame,[=](QPixmap pix){
         //把数据显示到qlabel中
         video_lable->setPixmap(pix);
    });

    connect(video_pushbutton,&QPushButton::clicked,[=](){
       video_flag = !video_flag;
       if(video_flag==1){
       video_pushbutton->setText("关闭监控");
        video_timer->start(50);

       }else{
       video_pushbutton->setText("开启监控");
       video_timer->stop();
       video_lable->clear();
       }
    });


    /************************多窗口6：调试***********************/
    msg6_label = new QLabel(tab6);
    msg6_label->setText("停车杆手动开关");
    msg6_label->setFont(ft);
    msg6_label->setGeometry(40,20,200,23);

    msg7_label = new QLabel(tab6);
    msg7_label->setText("RFID卡测试");
    msg7_label->setFont(ft);
    msg7_label->setGeometry(400,20,200,23);

    //rfid
    rfid_lable = new QLabel(tab6);
    rfid_lable->setGeometry(400,60,200,28);
    rfid_lable->setFont(ft);
    rfid_lable->setStyleSheet("background-color: rgba(255, 255, 255, 100);");

    rfid_pushbutton= new QPushButton(tab6);
    rfid_pushbutton->setGeometry(440,120,110,40);
    rfid_pushbutton->setStyleSheet(PUSHBUTTON_STYLE);
    rfid_pushbutton->setText("获取卡号");
    connect(rfid_pushbutton,&QPushButton::clicked,[=](){
       rfid_lable->setText(this->cardId);
    });

    //停车杆开按钮
    popl_on_button = new myPushButton(":/pic/on.png","",50,50);
    popl_on_button->setParent(tab6);
    popl_on_button->move(40,100);
    //钮按下处理
    connect(popl_on_button,&myPushButton::clicked,[=](){
    popl_on_button->zoom1();//弹跳
    popl_on_button->zoom2();
        emit parkpole_on();
    });
    //停车杆关按钮
    popl_off_button = new myPushButton(":/pic/off.png","",50,50);
    popl_off_button->setParent(tab6);
    popl_off_button->move(120,100);
    //钮按下处理
    connect(popl_off_button,&myPushButton::clicked,[=](){
    popl_off_button->zoom1();//弹跳
    popl_off_button->zoom2();
        emit parkpole_off();
    });

    /**********************数据库处理*********************/
    //初始化数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sql.db"); //设置路径名

    //打开数据库 按顺序写入到表格
    if(db.open())
    {
        sql_cmd  = new QSqlQuery(db);
        //创建用户信息表格
        QString createsql = "create table if not exists Users ("
                            "UserID INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "Username TEXT, phone TEXT,"
                            "LicensePlate TEXT UNIQUE,"
                            "NFCId TEXT UNIQUE,money REAL NOT NULL DEFAULT 0)";
        if(!sql_cmd->exec(createsql))
        {
           qDebug()<<sql_cmd->lastError().text();
        }
        //车辆信息表格
        createsql = "create table if not exists VehicleEntries (entryID integer primary key autoincrement,"
                    "LicensePlate TEXT, "
                    "EntryTime DATETIME, "
                    "ExitTime DATETIME, "
                    "FOREIGN KEY(LicensePlate) REFERENCES Users(LicensePlate))";
        if(!sql_cmd->exec(createsql))
        {
           qDebug()<<sql_cmd->lastError().text();
        }

        sql_to_table("info");
        sql_to_table("car_info");
        sql_to_table("money_info");
    }


    //添加成员按钮
    add_button = new myPushButton(":/pic/add.png","",30,30);
    add_button->setParent(tab1);
    add_button->move(700,0);
    add_button->raise();//最上面
    //钮按下处理
    connect(add_button,&myPushButton::clicked,[=](){
    add_button->zoom1();//弹跳
    add_button->zoom2();
        add_user_widget->show();
    });
}

MenuWindow::~MenuWindow()
{
    if(parkpole_thread->isRunning())
    {
        parkpole_thread->quit();
        parkpole_thread->wait();
    }
    parkpole->deleteLater();
    parkpole_thread->deleteLater();

    if(rfid_thread->isRunning())
    {
        rfid_thread->quit();
        rfid_thread->wait();
    }
    rfid->deleteLater();
    rfid_thread->deleteLater();

    if(video_thread->isRunning())
    {
        video_thread->quit();
        video_thread->wait();
    }
    video->deleteLater();
    video_thread->deleteLater();


    if(audio_thread->isRunning())
    {
        audio_thread->quit();
        audio_thread->wait();
    }
    audio->deleteLater();
    audio_thread->deleteLater();
}

//获取数据库中的信息更新显示到表格中
int MenuWindow::sql_to_table(QString table_name)
{

    if(table_name == "info")
    {
        info_tablewidget->clear();
        QStringList header;
        header<<"姓名"<<"车牌号"<<"卡号"<<"电话";
        info_tablewidget->setHorizontalHeaderLabels(header);

        QString str = "select * from Users;";
        sql_cmd->prepare(str);
        if (sql_cmd->exec())
        {
            this->curr_row=0;
            while (sql_cmd->next())
            {

                QStringList msg;
                msg.clear();
                msg << sql_cmd->value(1).toString()
                    << sql_cmd->value(3).toString()
                    << sql_cmd->value(4).toString()
                    << sql_cmd->value(2).toString();

                this->curr_row++;
                info_tablewidget->setRowCount(this->curr_row); //设置行数为
                for(int i=0; i<msg.size(); i++)
                 info_tablewidget->setItem(this->curr_row-1,i,new QTableWidgetItem(msg[i]));

            }
        }
    }
    else if(table_name == "car_info")
    {
        park_tablewidget->clear();
        QStringList header1;
        header1<<"车牌号"<<"入库时间" << "出库时间";
        park_tablewidget->setHorizontalHeaderLabels(header1);


        QString str = "select * from VehicleEntries;";
        sql_cmd->prepare(str);
        if (sql_cmd->exec())
        {
            this->curr_row=0;
            while (sql_cmd->next())
            {

            QStringList msg;
            msg.clear();
            msg << sql_cmd->value(1).toString()
                << sql_cmd->value(2).toString()
                << sql_cmd->value(3).toString();
            qDebug() << msg;
            this->curr_row++;
            park_tablewidget->setRowCount(this->curr_row); //设置行数为
            for(int i=0; i<msg.size(); i++)
             park_tablewidget->setItem(this->curr_row-1,i,new QTableWidgetItem(msg[i]));

            }
        }
    }else if(table_name == "money_info")
    {
        pay_tablewidget->clear();
        QStringList header2;
        header2<<"姓名"<<"卡号"<<"余额";
        pay_tablewidget->setHorizontalHeaderLabels(header2);

        QString str = "select * from Users;";
        sql_cmd->prepare(str);
        if (sql_cmd->exec())
        {
            this->curr_row=0;
            while (sql_cmd->next())
            {

            QStringList msg;
            msg.clear();
            msg << sql_cmd->value(1).toString()
                << sql_cmd->value(4).toString()
                << sql_cmd->value(5).toString();

            this->curr_row++;
            pay_tablewidget->setRowCount(this->curr_row); //设置行数为
            for(int i=0; i<msg.size(); i++)
             pay_tablewidget->setItem(this->curr_row-1,i,new QTableWidgetItem(msg[i]));

            }
        }
    }
    return 0;
}

//过滤事件
bool MenuWindow::eventFilter(QObject *watched, QEvent *event)
{

    if(watched == eInput)
        switch (event->type()) {
        case QEvent::Hide:
             tabwight->setGeometry(0,100,800,320);
            break;
        case QEvent::Show:
        {
            if(inputFlag == false){
                eInput->hide();
                return false;
            }
             tabwight->setGeometry(0,100,800,180);
        }
            break;
        default:
            break;
        }
    else if(watched==tab4 || watched==tab2 || watched==tab3 || watched==tab1)
    {
        inputFlag = false;
    }

    else inputFlag = true;

    return QWidget::eventFilter(watched,event);//将事件传递给父类
}

void MenuWindow::min_price_dsbox_slot(double d)
{
     price_min = d;

}


void MenuWindow::menuShow()
{
    add_user_widget->hide();
}

void MenuWindow::addUserToDatabase()
{
    sql_cmd->prepare("INSERT INTO Users (Username, Phone,LicensePlate, NFCId, money) "
                   "VALUES (:username, :phone, :licensePlate ,:NFCId,:money)");
     sql_cmd->bindValue(":username", add_user_widget->username);
     sql_cmd->bindValue(":phone", add_user_widget->phone);
     sql_cmd->bindValue(":licensePlate", add_user_widget->licensePlate);
     sql_cmd->bindValue(":NFCId", add_user_widget->nfcCardNumber);
     sql_cmd->bindValue(":money", 0);

     if (!sql_cmd->exec()) {
         qDebug() << "Insert user failed:" << sql_cmd->lastError();
          QMessageBox::warning(this, tr("提示"),tr("添加失败\n"),QMessageBox::Ok);
     }
     else
    {
         QMessageBox::warning(this, tr("提示"),tr("添加成功\n"),QMessageBox::Ok);
         sql_to_table("info");
         sql_to_table("money_info");
     }
}


void MenuWindow::isHaveCarIn(QString carId)
{
    if (checkUsersExists(carId.mid(1))) {
        if(!checkLicensePlateExists(carId.mid(1)))
        {
            if (insertVehicleEntry(carId.mid(1))) {
                qDebug() << "Vehicle entry recorded successfully.";
                sql_to_table("car_info");
                emit parkpole_on();
                parkPoleCloseTimer->start(10000);
                emit playAudio(QString("%1，入库成功").arg(carId));
            } else {
                qDebug() << "Failed to record vehicle entry.";
            }
        }
    } else {
        qDebug() << "未注册车牌号：" << carId;
        emit playAudio(QString("未注册车辆"));
    }
}
bool MenuWindow::checkUsersExists(const QString &licensePlate)
{
    sql_cmd->prepare("SELECT COUNT(*) FROM Users WHERE LicensePlate = :licensePlate");
        sql_cmd->bindValue(":licensePlate", licensePlate);
        if (sql_cmd->exec()) {
            if (sql_cmd->next()) {
                return sql_cmd->value(0).toInt() > 0;  // 检查计数是否大于0
            }
        } else {
            qDebug() << "Query failed:" << sql_cmd->lastError();
        }
        return false;  // 默认返回不存在
}
bool MenuWindow::checkLicensePlateExists(const QString &licensePlate)
{
    sql_cmd->prepare("SELECT COUNT(*) FROM VehicleEntries WHERE LicensePlate = :licensePlate");
        sql_cmd->bindValue(":licensePlate", licensePlate);
        if (sql_cmd->exec()) {
            if (sql_cmd->next()) {
                return sql_cmd->value(0).toInt() > 0;  // 检查计数是否大于0
            }
        } else {
            qDebug() << "Query failed:" << sql_cmd->lastError();
        }
        return false;  // 默认返回不存在
}

bool MenuWindow::insertVehicleEntry(const QString &licensePlate)
{
    sql_cmd->prepare("INSERT INTO VehicleEntries (LicensePlate, EntryTime) VALUES (:licensePlate, datetime('now'))");
    sql_cmd->bindValue(":licensePlate", licensePlate);
    if (!sql_cmd->exec()) {
        qDebug() << "Insert vehicle entry failed:" << sql_cmd->lastError();
        return false;
    }
    return true;
}

void MenuWindow::isHaveCarOut(QString cardId)
{
    this->cardId = cardId;
    double ratePerHour = price_min;  // 假定每小时费率为1.5元

    sql_cmd->prepare("SELECT * FROM VehicleEntries WHERE LicensePlate = :LicensePlate");
    sql_cmd->bindValue(":LicensePlate", cardId);

    if (sql_cmd->exec()) {
        if (sql_cmd->next()) {
            //扣费
            int cost = calculateParkingCost(cardId, ratePerHour);
            sql_cmd->prepare("SELECT money FROM Users WHERE LicensePlate = :LicensePlate");
            sql_cmd->bindValue(":LicensePlate", cardId);
            if (sql_cmd->exec()) {
                if (sql_cmd->next()) {
                    double currentBalance = sql_cmd->value("money").toDouble();
                    double newBalance = currentBalance - cost;
                    sql_cmd->prepare("UPDATE Users SET money = :new_balance WHERE LicensePlate = :LicensePlate");
                    sql_cmd->bindValue(":new_balance", newBalance);
                    sql_cmd->bindValue(":LicensePlate", cardId);
                    if (sql_cmd->exec()) {
                        // 如果记录存在，执行删除操作
                        sql_cmd->prepare("DELETE FROM VehicleEntries WHERE LicensePlate = :LicensePlate");
                        sql_cmd->bindValue(":LicensePlate", cardId);
                        if (sql_cmd->exec()) {
                            qDebug() << "车辆" << cardId << "出库成功，记录已删除。";
                            sql_to_table("car_info");
                            sql_to_table("money_info");
                            emit parkpole_on();
                            parkPoleCloseTimer->start(10000);
                            emit playAudio(QString("消费%1元，出库成功").arg(cost));
                        } else {
                            qDebug() << "删除记录失败:" << sql_cmd->lastError().text();
                        }
                    } else {
                        qDebug() << "更新余额失败:" << sql_cmd->lastError().text();
                    }

                }
            } else {
                qDebug() << "查询失败:" << sql_cmd->lastError().text();
                return;
            }
        } else {
            qDebug() << "未找到车辆" << cardId << "的入库记录，无法执行出库操作。";
            emit playAudio(QString("车辆已出库，请勿重复刷卡"));
        }
    } else {
        qDebug() << "查询失败:" << sql_cmd->lastError().text();
    }
}

double MenuWindow::calculateParkingCost(const QString &licensePlate, double ratePerHour)
{
    // 查询入库时间
        sql_cmd->prepare("SELECT EntryTime FROM VehicleEntries WHERE LicensePlate = :licensePlate AND ExitTime IS NULL");
        sql_cmd->bindValue(":licensePlate", licensePlate);
        if (sql_cmd->exec() && sql_cmd->next()) {
            QDateTime entryTime = sql_cmd->value(0).toDateTime();
            QDateTime exitTime = QDateTime::currentDateTime();
            int parkedSeconds = entryTime.secsTo(exitTime);
            double hours = parkedSeconds / 3600.0;
            double cost = hours * ratePerHour;
            // 确保最小费用为1元
            cost = std::max(cost, 1.0);
            return cost;
        }
        return 0.0;
}
