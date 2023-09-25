#include "headers/mainwindow.h"

#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <vector>
#include <iostream>
#include <QPalette>
#include <cmath>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <fstream>

enum status{
    unedited,
    correct,
    incorrect,
};

class Letter : public QLineEdit{
    Q_OBJECT
 public:
    status condition = unedited;
};

class Text : public QWidget{
 signals:
    void signalFinish();
 private:
    Q_OBJECT
 public:
    int curChar = 0;
    QMediaPlayer tick;
    std::vector<Letter*> letters;
    Text(std::string rawText, QGridLayout* layout){
        for(int i = 0; i < rawText.size(); ++i){
            letters.emplace_back(new Letter);
            letters.back()->setText(QString(rawText[i]));
            letters.back()->setReadOnly(true);
            letters.back()->setMinimumWidth(50);
            letters.back()->setMaximumWidth(50);
            letters.back()->setMinimumHeight(50);
            QFont f;
            f.setPixelSize(50);
            letters.back()->setFont(f);
            letters.back()->setAlignment(Qt::AlignCenter);
            letters.back()->setStyleSheet("QLineEdit {  border: 2px solid black;"
                                          "border-radius: 5px;}");
            layout->addWidget(letters.back(), int (i/int(std::max(int(std::sqrt(rawText.size())), 30))), i%(int(std::max(int(std::sqrt(rawText.size())), 30))));
            std::cout << int (i/5) << i%5 << std::endl;
        }
    }
    void keyPressEvent(QKeyEvent *event)
    {
       std::cout << event->text().toStdString() << std::endl;
       if(event->key() == Qt::Key_Shift);
       else if(event->key() == Qt::Key_Control);
       else if(event->key() == Qt::Key_Alt);
       else if(event->key() == Qt::Key_Backspace){
           if(curChar > 0){
               tick.setMedia(QUrl("qrc:sources/backspace.wav"));
               tick.play();
               curChar--;
           }
           letters[curChar]->condition = unedited;
           letters[curChar]->setStyleSheet("QLineEdit {  border: 2px solid black;"
                                           "background: white;"
                                           "border-radius: 5px;}");

       }
       else if(curChar < letters.size() && event->text() == letters[curChar]->text() ){

           letters[curChar]->condition = correct;
           letters[curChar]->setStyleSheet("QLineEdit {  border: 2px solid black;"
                                          "background: rgb(200,255,200);"
                                           "border-radius: 5px;}");
           tick.setMedia(QUrl("qrc:sources/correct.wav"));
           tick.play();
           curChar ++;
       }
       else if(curChar < letters.size() && event->text() != letters[curChar]->text()){
           letters[curChar]->condition = incorrect;
           letters[curChar]->setStyleSheet("QLineEdit {  border: 2px solid black;"
                                           "background: rgb(255,200,200);"
                                           "border-radius: 5px;}");
           tick.setMedia(QUrl("qrc:sources/incorrect.wav"));
           tick.play();
           curChar ++;

       }
       if(curChar == letters.size()){
            emit signalFinish();
       }
   }
};

int main(int argc, char *argv[])
{
    QPalette* pal = new QPalette();
    pal->setColor(QPalette::Window, Qt::white);
    QApplication a(argc, argv);

    QString textPath = QFileDialog::getOpenFileName(nullptr,
                                         "Open TXT file",
                                         "/opt/",
                                         "TXT files (*.txt)");
    std::ifstream file(textPath.toStdString());

    std::string text;
    std::string buf;
    while(getline(file, buf)){
             text += buf;
          }
    std::cout << text << "hehe" << std::endl;
    MainWindow* mainWindow = new MainWindow();
    mainWindow->setMinimumHeight(50 * int(std::sqrt(text.size())) + 50);
    mainWindow->setMinimumWidth(60 * std::max(int(std::sqrt(text.size())), 30));
    mainWindow->setPalette(*pal);

    QGridLayout* letters = new QGridLayout(mainWindow);
    Text mainText(text, letters);
    mainText.grabKeyboard();
    QObject::connect(&mainText, &Text::signalFinish, mainWindow, &MainWindow::finish);
    mainWindow->show();
    return a.exec();
}


#include "main.moc"
