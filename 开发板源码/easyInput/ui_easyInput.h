/********************************************************************************
** Form generated from reading UI file 'easyInput.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EASYINPUT_H
#define UI_EASYINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_easyInput
{
public:
    QGridLayout *gridLayout_3;
    QWidget *widgetTop;
    QHBoxLayout *lay2;
    QPushButton *btnPre;
    QLabel *labPY;
    QLabel *labCh1;
    QLabel *labCh2;
    QLabel *labCh3;
    QLabel *labCh4;
    QLabel *labCh5;
    QWidget *widgetPreNext;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnNext;
    QPushButton *btnClose;
    QWidget *widgetMain;
    QGridLayout *gridLayout;
    QPushButton *btn3;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btns;
    QPushButton *btnd;
    QPushButton *btng;
    QPushButton *btnk;
    QPushButton *btnl;
    QPushButton *btnz;
    QPushButton *btnx;
    QPushButton *btnj;
    QPushButton *btnc;
    QPushButton *btnv;
    QPushButton *btnb;
    QPushButton *btnn;
    QPushButton *btnm;
    QPushButton *btnh;
    QPushButton *btn0;
    QPushButton *btn4;
    QPushButton *btnDot;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btnf;
    QPushButton *btno;
    QPushButton *btnp;
    QPushButton *btna;
    QPushButton *btni;
    QPushButton *btnq;
    QPushButton *btnu;
    QPushButton *btnw;
    QPushButton *btne;
    QPushButton *btny;
    QPushButton *btnt;
    QPushButton *btnr;
    QPushButton *btnUpper;
    QPushButton *btnType;
    QPushButton *btnEnter;
    QPushButton *btnSpace;
    QPushButton *btnDelete;

    void setupUi(QWidget *easyInput)
    {
        if (easyInput->objectName().isEmpty())
            easyInput->setObjectName(QStringLiteral("easyInput"));
        easyInput->resize(575, 189);
        easyInput->setStyleSheet(QStringLiteral(""));
        gridLayout_3 = new QGridLayout(easyInput);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetTop = new QWidget(easyInput);
        widgetTop->setObjectName(QStringLiteral("widgetTop"));
        lay2 = new QHBoxLayout(widgetTop);
        lay2->setSpacing(0);
        lay2->setObjectName(QStringLiteral("lay2"));
        lay2->setContentsMargins(9, 9, 9, 0);
        btnPre = new QPushButton(widgetTop);
        btnPre->setObjectName(QStringLiteral("btnPre"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnPre->sizePolicy().hasHeightForWidth());
        btnPre->setSizePolicy(sizePolicy);
        btnPre->setFocusPolicy(Qt::NoFocus);

        lay2->addWidget(btnPre);

        labPY = new QLabel(widgetTop);
        labPY->setObjectName(QStringLiteral("labPY"));
        labPY->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labPY);

        labCh1 = new QLabel(widgetTop);
        labCh1->setObjectName(QStringLiteral("labCh1"));
        labCh1->setScaledContents(true);
        labCh1->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh1);

        labCh2 = new QLabel(widgetTop);
        labCh2->setObjectName(QStringLiteral("labCh2"));
        labCh2->setScaledContents(true);
        labCh2->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh2);

        labCh3 = new QLabel(widgetTop);
        labCh3->setObjectName(QStringLiteral("labCh3"));
        labCh3->setScaledContents(true);
        labCh3->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh3);

        labCh4 = new QLabel(widgetTop);
        labCh4->setObjectName(QStringLiteral("labCh4"));
        labCh4->setScaledContents(true);
        labCh4->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh4);

        labCh5 = new QLabel(widgetTop);
        labCh5->setObjectName(QStringLiteral("labCh5"));
        labCh5->setScaledContents(true);
        labCh5->setAlignment(Qt::AlignCenter);

        lay2->addWidget(labCh5);

        widgetPreNext = new QWidget(widgetTop);
        widgetPreNext->setObjectName(QStringLiteral("widgetPreNext"));
        horizontalLayout = new QHBoxLayout(widgetPreNext);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        btnNext = new QPushButton(widgetPreNext);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        sizePolicy.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
        btnNext->setSizePolicy(sizePolicy);
        btnNext->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(btnNext);


        lay2->addWidget(widgetPreNext);

        btnClose = new QPushButton(widgetTop);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnClose->sizePolicy().hasHeightForWidth());
        btnClose->setSizePolicy(sizePolicy1);
        btnClose->setFocusPolicy(Qt::NoFocus);

        lay2->addWidget(btnClose);


        gridLayout_3->addWidget(widgetTop, 0, 0, 1, 2);

        widgetMain = new QWidget(easyInput);
        widgetMain->setObjectName(QStringLiteral("widgetMain"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetMain->sizePolicy().hasHeightForWidth());
        widgetMain->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(widgetMain);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btn3 = new QPushButton(widgetMain);
        btn3->setObjectName(QStringLiteral("btn3"));
        sizePolicy1.setHeightForWidth(btn3->sizePolicy().hasHeightForWidth());
        btn3->setSizePolicy(sizePolicy1);
        btn3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn3, 0, 2, 1, 1);

        btn5 = new QPushButton(widgetMain);
        btn5->setObjectName(QStringLiteral("btn5"));
        sizePolicy1.setHeightForWidth(btn5->sizePolicy().hasHeightForWidth());
        btn5->setSizePolicy(sizePolicy1);
        btn5->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn5, 0, 4, 1, 1);

        btn6 = new QPushButton(widgetMain);
        btn6->setObjectName(QStringLiteral("btn6"));
        sizePolicy1.setHeightForWidth(btn6->sizePolicy().hasHeightForWidth());
        btn6->setSizePolicy(sizePolicy1);
        btn6->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn6, 0, 5, 1, 1);

        btn7 = new QPushButton(widgetMain);
        btn7->setObjectName(QStringLiteral("btn7"));
        sizePolicy1.setHeightForWidth(btn7->sizePolicy().hasHeightForWidth());
        btn7->setSizePolicy(sizePolicy1);
        btn7->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn7, 0, 6, 1, 1);

        btn8 = new QPushButton(widgetMain);
        btn8->setObjectName(QStringLiteral("btn8"));
        sizePolicy1.setHeightForWidth(btn8->sizePolicy().hasHeightForWidth());
        btn8->setSizePolicy(sizePolicy1);
        btn8->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn8, 0, 7, 1, 1);

        btn9 = new QPushButton(widgetMain);
        btn9->setObjectName(QStringLiteral("btn9"));
        sizePolicy1.setHeightForWidth(btn9->sizePolicy().hasHeightForWidth());
        btn9->setSizePolicy(sizePolicy1);
        btn9->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn9, 0, 8, 1, 1);

        btns = new QPushButton(widgetMain);
        btns->setObjectName(QStringLiteral("btns"));
        sizePolicy1.setHeightForWidth(btns->sizePolicy().hasHeightForWidth());
        btns->setSizePolicy(sizePolicy1);
        btns->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btns, 2, 2, 1, 1);

        btnd = new QPushButton(widgetMain);
        btnd->setObjectName(QStringLiteral("btnd"));
        sizePolicy1.setHeightForWidth(btnd->sizePolicy().hasHeightForWidth());
        btnd->setSizePolicy(sizePolicy1);
        btnd->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnd, 2, 3, 1, 1);

        btng = new QPushButton(widgetMain);
        btng->setObjectName(QStringLiteral("btng"));
        sizePolicy1.setHeightForWidth(btng->sizePolicy().hasHeightForWidth());
        btng->setSizePolicy(sizePolicy1);
        btng->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btng, 2, 5, 1, 1);

        btnk = new QPushButton(widgetMain);
        btnk->setObjectName(QStringLiteral("btnk"));
        sizePolicy1.setHeightForWidth(btnk->sizePolicy().hasHeightForWidth());
        btnk->setSizePolicy(sizePolicy1);
        btnk->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnk, 2, 8, 1, 1);

        btnl = new QPushButton(widgetMain);
        btnl->setObjectName(QStringLiteral("btnl"));
        sizePolicy1.setHeightForWidth(btnl->sizePolicy().hasHeightForWidth());
        btnl->setSizePolicy(sizePolicy1);
        btnl->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnl, 2, 9, 1, 1);

        btnz = new QPushButton(widgetMain);
        btnz->setObjectName(QStringLiteral("btnz"));
        sizePolicy1.setHeightForWidth(btnz->sizePolicy().hasHeightForWidth());
        btnz->setSizePolicy(sizePolicy1);
        btnz->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnz, 3, 2, 1, 1);

        btnx = new QPushButton(widgetMain);
        btnx->setObjectName(QStringLiteral("btnx"));
        sizePolicy1.setHeightForWidth(btnx->sizePolicy().hasHeightForWidth());
        btnx->setSizePolicy(sizePolicy1);
        btnx->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnx, 3, 3, 1, 1);

        btnj = new QPushButton(widgetMain);
        btnj->setObjectName(QStringLiteral("btnj"));
        sizePolicy1.setHeightForWidth(btnj->sizePolicy().hasHeightForWidth());
        btnj->setSizePolicy(sizePolicy1);
        btnj->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnj, 2, 7, 1, 1);

        btnc = new QPushButton(widgetMain);
        btnc->setObjectName(QStringLiteral("btnc"));
        sizePolicy1.setHeightForWidth(btnc->sizePolicy().hasHeightForWidth());
        btnc->setSizePolicy(sizePolicy1);
        btnc->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnc, 3, 4, 1, 1);

        btnv = new QPushButton(widgetMain);
        btnv->setObjectName(QStringLiteral("btnv"));
        sizePolicy1.setHeightForWidth(btnv->sizePolicy().hasHeightForWidth());
        btnv->setSizePolicy(sizePolicy1);
        btnv->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnv, 3, 5, 1, 1);

        btnb = new QPushButton(widgetMain);
        btnb->setObjectName(QStringLiteral("btnb"));
        sizePolicy1.setHeightForWidth(btnb->sizePolicy().hasHeightForWidth());
        btnb->setSizePolicy(sizePolicy1);
        btnb->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnb, 3, 6, 1, 1);

        btnn = new QPushButton(widgetMain);
        btnn->setObjectName(QStringLiteral("btnn"));
        sizePolicy1.setHeightForWidth(btnn->sizePolicy().hasHeightForWidth());
        btnn->setSizePolicy(sizePolicy1);
        btnn->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnn, 3, 7, 1, 1);

        btnm = new QPushButton(widgetMain);
        btnm->setObjectName(QStringLiteral("btnm"));
        sizePolicy1.setHeightForWidth(btnm->sizePolicy().hasHeightForWidth());
        btnm->setSizePolicy(sizePolicy1);
        btnm->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnm, 3, 8, 1, 1);

        btnh = new QPushButton(widgetMain);
        btnh->setObjectName(QStringLiteral("btnh"));
        sizePolicy1.setHeightForWidth(btnh->sizePolicy().hasHeightForWidth());
        btnh->setSizePolicy(sizePolicy1);
        btnh->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnh, 2, 6, 1, 1);

        btn0 = new QPushButton(widgetMain);
        btn0->setObjectName(QStringLiteral("btn0"));
        sizePolicy1.setHeightForWidth(btn0->sizePolicy().hasHeightForWidth());
        btn0->setSizePolicy(sizePolicy1);
        btn0->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn0, 0, 9, 1, 1);

        btn4 = new QPushButton(widgetMain);
        btn4->setObjectName(QStringLiteral("btn4"));
        sizePolicy1.setHeightForWidth(btn4->sizePolicy().hasHeightForWidth());
        btn4->setSizePolicy(sizePolicy1);
        btn4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn4, 0, 3, 1, 1);

        btnDot = new QPushButton(widgetMain);
        btnDot->setObjectName(QStringLiteral("btnDot"));
        sizePolicy1.setHeightForWidth(btnDot->sizePolicy().hasHeightForWidth());
        btnDot->setSizePolicy(sizePolicy1);
        btnDot->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnDot, 0, 10, 1, 1);

        btn1 = new QPushButton(widgetMain);
        btn1->setObjectName(QStringLiteral("btn1"));
        sizePolicy1.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy1);
        btn1->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn1, 0, 0, 1, 1);

        btn2 = new QPushButton(widgetMain);
        btn2->setObjectName(QStringLiteral("btn2"));
        sizePolicy1.setHeightForWidth(btn2->sizePolicy().hasHeightForWidth());
        btn2->setSizePolicy(sizePolicy1);
        btn2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btn2, 0, 1, 1, 1);

        btnf = new QPushButton(widgetMain);
        btnf->setObjectName(QStringLiteral("btnf"));
        sizePolicy1.setHeightForWidth(btnf->sizePolicy().hasHeightForWidth());
        btnf->setSizePolicy(sizePolicy1);
        btnf->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnf, 2, 4, 1, 1);

        btno = new QPushButton(widgetMain);
        btno->setObjectName(QStringLiteral("btno"));
        sizePolicy1.setHeightForWidth(btno->sizePolicy().hasHeightForWidth());
        btno->setSizePolicy(sizePolicy1);
        btno->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btno, 1, 9, 1, 1);

        btnp = new QPushButton(widgetMain);
        btnp->setObjectName(QStringLiteral("btnp"));
        sizePolicy1.setHeightForWidth(btnp->sizePolicy().hasHeightForWidth());
        btnp->setSizePolicy(sizePolicy1);
        btnp->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnp, 1, 10, 1, 1);

        btna = new QPushButton(widgetMain);
        btna->setObjectName(QStringLiteral("btna"));
        sizePolicy1.setHeightForWidth(btna->sizePolicy().hasHeightForWidth());
        btna->setSizePolicy(sizePolicy1);
        btna->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btna, 2, 1, 1, 1);

        btni = new QPushButton(widgetMain);
        btni->setObjectName(QStringLiteral("btni"));
        sizePolicy1.setHeightForWidth(btni->sizePolicy().hasHeightForWidth());
        btni->setSizePolicy(sizePolicy1);
        btni->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btni, 1, 8, 1, 1);

        btnq = new QPushButton(widgetMain);
        btnq->setObjectName(QStringLiteral("btnq"));
        sizePolicy1.setHeightForWidth(btnq->sizePolicy().hasHeightForWidth());
        btnq->setSizePolicy(sizePolicy1);
        btnq->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnq, 1, 1, 1, 1);

        btnu = new QPushButton(widgetMain);
        btnu->setObjectName(QStringLiteral("btnu"));
        sizePolicy1.setHeightForWidth(btnu->sizePolicy().hasHeightForWidth());
        btnu->setSizePolicy(sizePolicy1);
        btnu->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnu, 1, 7, 1, 1);

        btnw = new QPushButton(widgetMain);
        btnw->setObjectName(QStringLiteral("btnw"));
        sizePolicy1.setHeightForWidth(btnw->sizePolicy().hasHeightForWidth());
        btnw->setSizePolicy(sizePolicy1);
        btnw->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnw, 1, 2, 1, 1);

        btne = new QPushButton(widgetMain);
        btne->setObjectName(QStringLiteral("btne"));
        sizePolicy1.setHeightForWidth(btne->sizePolicy().hasHeightForWidth());
        btne->setSizePolicy(sizePolicy1);
        btne->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btne, 1, 3, 1, 1);

        btny = new QPushButton(widgetMain);
        btny->setObjectName(QStringLiteral("btny"));
        sizePolicy1.setHeightForWidth(btny->sizePolicy().hasHeightForWidth());
        btny->setSizePolicy(sizePolicy1);
        btny->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btny, 1, 6, 1, 1);

        btnt = new QPushButton(widgetMain);
        btnt->setObjectName(QStringLiteral("btnt"));
        sizePolicy1.setHeightForWidth(btnt->sizePolicy().hasHeightForWidth());
        btnt->setSizePolicy(sizePolicy1);
        btnt->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnt, 1, 5, 1, 1);

        btnr = new QPushButton(widgetMain);
        btnr->setObjectName(QStringLiteral("btnr"));
        sizePolicy1.setHeightForWidth(btnr->sizePolicy().hasHeightForWidth());
        btnr->setSizePolicy(sizePolicy1);
        btnr->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnr, 1, 4, 1, 1);

        btnUpper = new QPushButton(widgetMain);
        btnUpper->setObjectName(QStringLiteral("btnUpper"));
        sizePolicy1.setHeightForWidth(btnUpper->sizePolicy().hasHeightForWidth());
        btnUpper->setSizePolicy(sizePolicy1);
        btnUpper->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnUpper, 3, 0, 1, 2);

        btnType = new QPushButton(widgetMain);
        btnType->setObjectName(QStringLiteral("btnType"));
        sizePolicy1.setHeightForWidth(btnType->sizePolicy().hasHeightForWidth());
        btnType->setSizePolicy(sizePolicy1);
        btnType->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnType, 4, 0, 1, 1);

        btnEnter = new QPushButton(widgetMain);
        btnEnter->setObjectName(QStringLiteral("btnEnter"));
        sizePolicy1.setHeightForWidth(btnEnter->sizePolicy().hasHeightForWidth());
        btnEnter->setSizePolicy(sizePolicy1);
        btnEnter->setMaximumSize(QSize(16777215, 16777215));
        btnEnter->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnEnter, 4, 10, 1, 1);

        btnSpace = new QPushButton(widgetMain);
        btnSpace->setObjectName(QStringLiteral("btnSpace"));
        sizePolicy1.setHeightForWidth(btnSpace->sizePolicy().hasHeightForWidth());
        btnSpace->setSizePolicy(sizePolicy1);
        btnSpace->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnSpace, 4, 1, 1, 9);

        btnDelete = new QPushButton(widgetMain);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        sizePolicy1.setHeightForWidth(btnDelete->sizePolicy().hasHeightForWidth());
        btnDelete->setSizePolicy(sizePolicy1);
        btnDelete->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(btnDelete, 3, 9, 1, 2);


        gridLayout_3->addWidget(widgetMain, 1, 1, 1, 1);


        retranslateUi(easyInput);

        QMetaObject::connectSlotsByName(easyInput);
    } // setupUi

    void retranslateUi(QWidget *easyInput)
    {
        btnPre->setText(QApplication::translate("easyInput", "<", 0));
        labPY->setText(QString());
        labCh1->setText(QString());
        labCh2->setText(QString());
        labCh3->setText(QString());
        labCh4->setText(QString());
        labCh5->setText(QString());
        btnNext->setText(QApplication::translate("easyInput", ">", 0));
        btnClose->setText(QApplication::translate("easyInput", "\357\271\200", 0));
        btn3->setText(QApplication::translate("easyInput", "3", 0));
        btn5->setText(QApplication::translate("easyInput", "5", 0));
        btn6->setText(QApplication::translate("easyInput", "6", 0));
        btn7->setText(QApplication::translate("easyInput", "7", 0));
        btn8->setText(QApplication::translate("easyInput", "8", 0));
        btn9->setText(QApplication::translate("easyInput", "9", 0));
        btns->setText(QApplication::translate("easyInput", "s", 0));
        btnd->setText(QApplication::translate("easyInput", "d", 0));
        btng->setText(QApplication::translate("easyInput", "g", 0));
        btnk->setText(QApplication::translate("easyInput", "k", 0));
        btnl->setText(QApplication::translate("easyInput", "l", 0));
        btnz->setText(QApplication::translate("easyInput", "z", 0));
        btnx->setText(QApplication::translate("easyInput", "x", 0));
        btnj->setText(QApplication::translate("easyInput", "j", 0));
        btnc->setText(QApplication::translate("easyInput", "c", 0));
        btnv->setText(QApplication::translate("easyInput", "v", 0));
        btnb->setText(QApplication::translate("easyInput", "b", 0));
        btnn->setText(QApplication::translate("easyInput", "n", 0));
        btnm->setText(QApplication::translate("easyInput", "m", 0));
        btnh->setText(QApplication::translate("easyInput", "h", 0));
        btn0->setText(QApplication::translate("easyInput", "0", 0));
        btn4->setText(QApplication::translate("easyInput", "4", 0));
        btnDot->setText(QApplication::translate("easyInput", ".", 0));
        btn1->setText(QApplication::translate("easyInput", "1", 0));
        btn2->setText(QApplication::translate("easyInput", "2", 0));
        btnf->setText(QApplication::translate("easyInput", "f", 0));
        btno->setText(QApplication::translate("easyInput", "o", 0));
        btnp->setText(QApplication::translate("easyInput", "p", 0));
        btna->setText(QApplication::translate("easyInput", "a", 0));
        btni->setText(QApplication::translate("easyInput", "i", 0));
        btnq->setText(QApplication::translate("easyInput", "q", 0));
        btnu->setText(QApplication::translate("easyInput", "u", 0));
        btnw->setText(QApplication::translate("easyInput", "w", 0));
        btne->setText(QApplication::translate("easyInput", "e", 0));
        btny->setText(QApplication::translate("easyInput", "y", 0));
        btnt->setText(QApplication::translate("easyInput", "t", 0));
        btnr->setText(QApplication::translate("easyInput", "r", 0));
        btnUpper->setText(QString());
        btnType->setText(QApplication::translate("easyInput", "En", 0));
        btnEnter->setText(QApplication::translate("easyInput", "\347\241\256\350\256\244", 0));
        btnSpace->setText(QApplication::translate("easyInput", "\347\251\272\346\240\274", 0));
        btnDelete->setText(QString());
        Q_UNUSED(easyInput);
    } // retranslateUi

};

namespace Ui {
    class easyInput: public Ui_easyInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EASYINPUT_H
