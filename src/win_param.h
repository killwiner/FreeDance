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
    explicit WinParam(QWidget *parent, int const &, int const &, int const &);
    void closeEvent(QCloseEvent *event);
private:
    int p0, p1, p2;
    QSlider *slider0, *slider1, *slider2;
 };

#endif // WIN_PARAM_H
