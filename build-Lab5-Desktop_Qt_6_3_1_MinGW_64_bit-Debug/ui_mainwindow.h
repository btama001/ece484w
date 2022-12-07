/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelpic;
    QPushButton *pushButton;
    QSlider *brightSlider;
    QSlider *contSlider;
    QLabel *b_label;
    QLabel *c_label;
    QPushButton *saveButton;
    QPushButton *TransferButton;
    QPushButton *TransferModButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(820, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        labelpic = new QLabel(centralwidget);
        labelpic->setObjectName(QString::fromUtf8("labelpic"));
        labelpic->setGeometry(QRect(90, 40, 591, 291));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 370, 121, 31));
        brightSlider = new QSlider(centralwidget);
        brightSlider->setObjectName(QString::fromUtf8("brightSlider"));
        brightSlider->setGeometry(QRect(370, 390, 160, 22));
        brightSlider->setOrientation(Qt::Horizontal);
        contSlider = new QSlider(centralwidget);
        contSlider->setObjectName(QString::fromUtf8("contSlider"));
        contSlider->setGeometry(QRect(370, 450, 160, 22));
        contSlider->setOrientation(Qt::Horizontal);
        b_label = new QLabel(centralwidget);
        b_label->setObjectName(QString::fromUtf8("b_label"));
        b_label->setGeometry(QRect(570, 390, 131, 20));
        c_label = new QLabel(centralwidget);
        c_label->setObjectName(QString::fromUtf8("c_label"));
        c_label->setGeometry(QRect(570, 440, 131, 20));
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(60, 420, 121, 31));
        TransferButton = new QPushButton(centralwidget);
        TransferButton->setObjectName(QString::fromUtf8("TransferButton"));
        TransferButton->setGeometry(QRect(210, 370, 121, 51));
        TransferModButton = new QPushButton(centralwidget);
        TransferModButton->setObjectName(QString::fromUtf8("TransferModButton"));
        TransferModButton->setGeometry(QRect(210, 450, 121, 51));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 470, 121, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 820, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelpic->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        b_label->setText(QCoreApplication::translate("MainWindow", "Brightness", nullptr));
        c_label->setText(QCoreApplication::translate("MainWindow", "Contrast", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save Image", nullptr));
        TransferButton->setText(QCoreApplication::translate("MainWindow", "Transfer Original", nullptr));
        TransferModButton->setText(QCoreApplication::translate("MainWindow", "Transfer Mod.", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Overlay", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
