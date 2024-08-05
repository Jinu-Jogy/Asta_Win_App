/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *mainPage;
    QHBoxLayout *horizontalLayout_6;
    QWidget *mainwidget;
    QVBoxLayout *verticalLayout;
    QWidget *downloadWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *downloadWidgetLabel;
    QPushButton *downloadWidgetButton;
    QWidget *playWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *playWidgetLabel;
    QPushButton *playWidgetButton;
    QWidget *writeExtrenalStorageWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *writeWidgetLabel;
    QPushButton *writeWidgetButton;
    QWidget *readExtrenalStorageWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *readWidgetLabel;
    QPushButton *readWidgetButton;
    QPushButton *muteButton;
    QPushButton *unmuteButton;
    QPushButton *deleteDeviceDataAndRestartButton;
    QPushButton *restartAppButton;
    QWidget *brightnessWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSlider *brightnessSlider;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_2;
    QSlider *playerVolumeSlider;
    QSpacerItem *verticalSpacer;
    QWidget *previewWidget;
    QHBoxLayout *horizontalLayout_10;
    QProgressBar *progressBar;
    QWidget *blackPage;
    QHBoxLayout *horizontalLayout_7;
    QWidget *ToggleUIWidget;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *turnUIOffButton;
    QPushButton *turnUIOnButton;
    QVBoxLayout *overlayLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(909, 615);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        mainPage = new QWidget();
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        horizontalLayout_6 = new QHBoxLayout(mainPage);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        mainwidget = new QWidget(mainPage);
        mainwidget->setObjectName(QString::fromUtf8("mainwidget"));
        mainwidget->setMinimumSize(QSize(400, 0));
        mainwidget->setMaximumSize(QSize(400, 16777215));
        verticalLayout = new QVBoxLayout(mainwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        downloadWidget = new QWidget(mainwidget);
        downloadWidget->setObjectName(QString::fromUtf8("downloadWidget"));
        horizontalLayout_5 = new QHBoxLayout(downloadWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        downloadWidgetLabel = new QLabel(downloadWidget);
        downloadWidgetLabel->setObjectName(QString::fromUtf8("downloadWidgetLabel"));

        horizontalLayout_5->addWidget(downloadWidgetLabel);

        downloadWidgetButton = new QPushButton(downloadWidget);
        downloadWidgetButton->setObjectName(QString::fromUtf8("downloadWidgetButton"));

        horizontalLayout_5->addWidget(downloadWidgetButton);


        verticalLayout->addWidget(downloadWidget);

        playWidget = new QWidget(mainwidget);
        playWidget->setObjectName(QString::fromUtf8("playWidget"));
        horizontalLayout_4 = new QHBoxLayout(playWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        playWidgetLabel = new QLabel(playWidget);
        playWidgetLabel->setObjectName(QString::fromUtf8("playWidgetLabel"));

        horizontalLayout_4->addWidget(playWidgetLabel);

        playWidgetButton = new QPushButton(playWidget);
        playWidgetButton->setObjectName(QString::fromUtf8("playWidgetButton"));

        horizontalLayout_4->addWidget(playWidgetButton);


        verticalLayout->addWidget(playWidget);

        writeExtrenalStorageWidget = new QWidget(mainwidget);
        writeExtrenalStorageWidget->setObjectName(QString::fromUtf8("writeExtrenalStorageWidget"));
        horizontalLayout = new QHBoxLayout(writeExtrenalStorageWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        writeWidgetLabel = new QLabel(writeExtrenalStorageWidget);
        writeWidgetLabel->setObjectName(QString::fromUtf8("writeWidgetLabel"));

        horizontalLayout->addWidget(writeWidgetLabel);

        writeWidgetButton = new QPushButton(writeExtrenalStorageWidget);
        writeWidgetButton->setObjectName(QString::fromUtf8("writeWidgetButton"));

        horizontalLayout->addWidget(writeWidgetButton);


        verticalLayout->addWidget(writeExtrenalStorageWidget);

        readExtrenalStorageWidget = new QWidget(mainwidget);
        readExtrenalStorageWidget->setObjectName(QString::fromUtf8("readExtrenalStorageWidget"));
        horizontalLayout_2 = new QHBoxLayout(readExtrenalStorageWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        readWidgetLabel = new QLabel(readExtrenalStorageWidget);
        readWidgetLabel->setObjectName(QString::fromUtf8("readWidgetLabel"));

        horizontalLayout_2->addWidget(readWidgetLabel);

        readWidgetButton = new QPushButton(readExtrenalStorageWidget);
        readWidgetButton->setObjectName(QString::fromUtf8("readWidgetButton"));

        horizontalLayout_2->addWidget(readWidgetButton);


        verticalLayout->addWidget(readExtrenalStorageWidget);

        muteButton = new QPushButton(mainwidget);
        muteButton->setObjectName(QString::fromUtf8("muteButton"));

        verticalLayout->addWidget(muteButton);

        unmuteButton = new QPushButton(mainwidget);
        unmuteButton->setObjectName(QString::fromUtf8("unmuteButton"));

        verticalLayout->addWidget(unmuteButton);

        deleteDeviceDataAndRestartButton = new QPushButton(mainwidget);
        deleteDeviceDataAndRestartButton->setObjectName(QString::fromUtf8("deleteDeviceDataAndRestartButton"));

        verticalLayout->addWidget(deleteDeviceDataAndRestartButton);

        restartAppButton = new QPushButton(mainwidget);
        restartAppButton->setObjectName(QString::fromUtf8("restartAppButton"));

        verticalLayout->addWidget(restartAppButton);

        brightnessWidget = new QWidget(mainwidget);
        brightnessWidget->setObjectName(QString::fromUtf8("brightnessWidget"));
        horizontalLayout_3 = new QHBoxLayout(brightnessWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(brightnessWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        brightnessSlider = new QSlider(brightnessWidget);
        brightnessSlider->setObjectName(QString::fromUtf8("brightnessSlider"));
        brightnessSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(brightnessSlider);


        verticalLayout->addWidget(brightnessWidget);

        widget = new QWidget(mainwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_9 = new QHBoxLayout(widget);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_9->addWidget(label_2);

        playerVolumeSlider = new QSlider(widget);
        playerVolumeSlider->setObjectName(QString::fromUtf8("playerVolumeSlider"));
        playerVolumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(playerVolumeSlider);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_6->addWidget(mainwidget);

        previewWidget = new QWidget(mainPage);
        previewWidget->setObjectName(QString::fromUtf8("previewWidget"));
        horizontalLayout_10 = new QHBoxLayout(previewWidget);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        progressBar = new QProgressBar(previewWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimum(0);
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setTextVisible(true);

        horizontalLayout_10->addWidget(progressBar);


        horizontalLayout_6->addWidget(previewWidget);

        stackedWidget->addWidget(mainPage);
        blackPage = new QWidget();
        blackPage->setObjectName(QString::fromUtf8("blackPage"));
        horizontalLayout_7 = new QHBoxLayout(blackPage);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        stackedWidget->addWidget(blackPage);

        verticalLayout_3->addWidget(stackedWidget);

        ToggleUIWidget = new QWidget(centralwidget);
        ToggleUIWidget->setObjectName(QString::fromUtf8("ToggleUIWidget"));
        horizontalLayout_8 = new QHBoxLayout(ToggleUIWidget);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        turnUIOffButton = new QPushButton(ToggleUIWidget);
        turnUIOffButton->setObjectName(QString::fromUtf8("turnUIOffButton"));

        horizontalLayout_8->addWidget(turnUIOffButton);

        turnUIOnButton = new QPushButton(ToggleUIWidget);
        turnUIOnButton->setObjectName(QString::fromUtf8("turnUIOnButton"));

        horizontalLayout_8->addWidget(turnUIOnButton);


        verticalLayout_3->addWidget(ToggleUIWidget);

        overlayLayout = new QVBoxLayout();
        overlayLayout->setObjectName(QString::fromUtf8("overlayLayout"));

        verticalLayout_3->addLayout(overlayLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 909, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Asta CMS", nullptr));
        downloadWidgetLabel->setText(QCoreApplication::translate("MainWindow", "Download the video", nullptr));
        downloadWidgetButton->setText(QCoreApplication::translate("MainWindow", "Download the video", nullptr));
        playWidgetLabel->setText(QCoreApplication::translate("MainWindow", "Play the video", nullptr));
        playWidgetButton->setText(QCoreApplication::translate("MainWindow", "Play the video", nullptr));
        writeWidgetLabel->setText(QCoreApplication::translate("MainWindow", "write External Storage", nullptr));
        writeWidgetButton->setText(QCoreApplication::translate("MainWindow", "Write external storage", nullptr));
        readWidgetLabel->setText(QCoreApplication::translate("MainWindow", "Read External Storage", nullptr));
        readWidgetButton->setText(QCoreApplication::translate("MainWindow", "Read external storage", nullptr));
        muteButton->setText(QCoreApplication::translate("MainWindow", "Mute system", nullptr));
        unmuteButton->setText(QCoreApplication::translate("MainWindow", "Unmute System", nullptr));
        deleteDeviceDataAndRestartButton->setText(QCoreApplication::translate("MainWindow", "Delete Device data and Restart the App", nullptr));
        restartAppButton->setText(QCoreApplication::translate("MainWindow", "Restart the App", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Brightness", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Player Volume", nullptr));
        turnUIOffButton->setText(QCoreApplication::translate("MainWindow", "Turn UI Off", nullptr));
        turnUIOnButton->setText(QCoreApplication::translate("MainWindow", "Turn UI On", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
