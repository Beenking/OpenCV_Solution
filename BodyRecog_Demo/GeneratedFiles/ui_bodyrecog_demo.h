/********************************************************************************
** Form generated from reading UI file 'bodyrecog_demo.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BODYRECOG_DEMO_H
#define UI_BODYRECOG_DEMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BodyRecog_DemoClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QVBoxLayout *_1;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BodyRecog_DemoClass)
    {
        if (BodyRecog_DemoClass->objectName().isEmpty())
            BodyRecog_DemoClass->setObjectName(QString::fromUtf8("BodyRecog_DemoClass"));
        BodyRecog_DemoClass->resize(957, 599);
        centralWidget = new QWidget(BodyRecog_DemoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 660, 500));
        _1 = new QVBoxLayout(groupBox);
        _1->setSpacing(0);
        _1->setContentsMargins(0, 0, 0, 0);
        _1->setObjectName(QString::fromUtf8("_1"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(810, 470, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(810, 510, 75, 23));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(750, 100, 171, 141));
        BodyRecog_DemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BodyRecog_DemoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 957, 23));
        BodyRecog_DemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BodyRecog_DemoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BodyRecog_DemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BodyRecog_DemoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BodyRecog_DemoClass->setStatusBar(statusBar);

        retranslateUi(BodyRecog_DemoClass);

        QMetaObject::connectSlotsByName(BodyRecog_DemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *BodyRecog_DemoClass)
    {
        BodyRecog_DemoClass->setWindowTitle(QApplication::translate("BodyRecog_DemoClass", "BodyRecog_Demo", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("BodyRecog_DemoClass", "ColorFrame", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("BodyRecog_DemoClass", "Open", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("BodyRecog_DemoClass", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BodyRecog_DemoClass: public Ui_BodyRecog_DemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BODYRECOG_DEMO_H
