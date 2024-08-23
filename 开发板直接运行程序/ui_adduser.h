/********************************************************************************
** Form generated from reading UI file 'adduser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUSER_H
#define UI_ADDUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addUser
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *phone;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *carId;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *cardId;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QFrame *addUser)
    {
        if (addUser->objectName().isEmpty())
            addUser->setObjectName(QString::fromUtf8("addUser"));
        addUser->resize(377, 489);
        layoutWidget = new QWidget(addUser);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 20, 251, 261));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        name = new QLineEdit(layoutWidget);
        name->setObjectName(QString::fromUtf8("name"));

        horizontalLayout->addWidget(name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        phone = new QLineEdit(layoutWidget);
        phone->setObjectName(QString::fromUtf8("phone"));

        horizontalLayout_2->addWidget(phone);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        carId = new QLineEdit(layoutWidget);
        carId->setObjectName(QString::fromUtf8("carId"));

        horizontalLayout_3->addWidget(carId);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        cardId = new QLineEdit(layoutWidget);
        cardId->setObjectName(QString::fromUtf8("cardId"));

        horizontalLayout_4->addWidget(cardId);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_5->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(addUser);

        QMetaObject::connectSlotsByName(addUser);
    } // setupUi

    void retranslateUi(QFrame *addUser)
    {
        addUser->setWindowTitle(QCoreApplication::translate("addUser", "Frame", nullptr));
        label->setText(QCoreApplication::translate("addUser", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("addUser", "\347\224\265\350\257\235\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("addUser", "\350\275\246\347\211\214\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("addUser", "\345\215\241\345\217\267\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("addUser", "\345\217\226\346\266\210", nullptr));
        pushButton_2->setText(QCoreApplication::translate("addUser", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addUser: public Ui_addUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUSER_H
