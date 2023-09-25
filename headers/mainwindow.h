#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMediaPlayer>

class MainWindow : public QWidget
{
    Q_OBJECT
    QMediaPlayer tick;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 public slots:
    void finish();
};
#endif // MAINWINDOW_H
