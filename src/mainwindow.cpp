#include "headers/mainwindow.h"
#include <iostream>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QTimer>
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
}

void MainWindow::finish(){
    std::cout << "la fin" << std::endl;
    QLineEdit* finishScreen = new QLineEdit();
    finishScreen->setMinimumWidth(this->width());
    finishScreen->setMinimumHeight(this->height());
    finishScreen->setStyleSheet("QLineEdit {background: rgb(200,255,200);}");
    finishScreen->setAlignment(Qt::AlignCenter);
    finishScreen->setText("Victory");
    QFont f;
    f.setPixelSize(100);
    f.setItalic(true);
    f.setBold(true);
    finishScreen->setFont(f);
    delete this->layout();
    QHBoxLayout * finalLayout = new QHBoxLayout(this);
    finalLayout->addWidget(finishScreen);
    QTimer t;
    tick.setMedia(QUrl("qrc:sources/victory.wav"));
    tick.play();
    QTimer::singleShot(5000, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
}

