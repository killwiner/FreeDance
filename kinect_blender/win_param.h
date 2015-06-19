#ifndef WIN_PARAM_H
#define WIN_PARAM_H

#include <QApplication>
#include <QFont>
#include <QLCDNumber>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialog>

class WinParam : public QDialog
 {

public:
    explicit WinParam(QWidget *parent = 0, int *p0_ = 0, int *p1_ = 0);
    void closeEvent(QCloseEvent *event);
private:
     QPushButton *button;
     QSlider *slider0;
     QSlider *slider1;

     int *p0, *p1;

 };

#endif // WIN_PARAM_H
