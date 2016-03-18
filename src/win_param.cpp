#include "win_param.h"
#include "stdio.h"

WinParam::WinParam(QWidget *parent, int const &p0_, int const &p1_, int const &p2_)
    : QDialog(parent), p0(p0_), p1(p1_), p2(p2_)
{
    QPushButton *button = new QPushButton(this);
    button->setFont(QFont("Times", 12, QFont::Bold));
    button->setText( "Ok" );

    QLabel *label0 = new QLabel("blue filter param");
    QLabel *label1 = new QLabel("red filter param");
    QLabel *label2 = new QLabel("number of pass");

    QLCDNumber *lcd0 = new QLCDNumber(3);
    lcd0->setSegmentStyle(QLCDNumber::Filled);
    lcd0->display(p0);

    QLCDNumber *lcd1 = new QLCDNumber(3);
    lcd1->setSegmentStyle(QLCDNumber::Filled);
    lcd1->display(p1);

    QLCDNumber *lcd2 = new QLCDNumber(3);
    lcd2->setSegmentStyle(QLCDNumber::Filled);
    lcd2->display(p2);

    slider0 = new QSlider(Qt::Horizontal);
    slider0->setRange(0, 255);
    slider0->setValue(p0);

    slider1 = new QSlider(Qt::Horizontal);
    slider1->setRange(0, 255);
    slider1->setValue(p1);

    slider2 = new QSlider(Qt::Horizontal);
    slider2->setRange(0, 64);
    slider2->setValue(p2);

    lcd0->setStyleSheet("background-color: black; color: red;");
    lcd1->setStyleSheet("background-color: black; color: red;");
    lcd2->setStyleSheet("background-color: black; color: red;");

    connect(button, SIGNAL(clicked()), this, SLOT(close()));
    connect(slider0, SIGNAL(valueChanged(int)), lcd0, SLOT(display(int)));
    connect(slider1, SIGNAL(valueChanged(int)), lcd1, SLOT(display(int)));
    connect(slider2, SIGNAL(valueChanged(int)), lcd2, SLOT(display(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label0);
    layout->addWidget(lcd0);
    layout->addWidget(slider0);
    layout->addWidget(label1);
    layout->addWidget(lcd1);
    layout->addWidget(slider1);
    layout->addWidget(label2);
    layout->addWidget(lcd2);
    layout->addWidget(slider2);

    layout->addWidget(button);

    setLayout(layout);

}

void WinParam::closeEvent(QCloseEvent *event) {
    p0 = slider0->value();
    p1 = slider1->value();
    p2 = slider2->value();
}
