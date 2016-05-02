#include "win.h"
#include <QDebug>

Win::Win()
{
}

void Win::closeEvent(QCloseEvent *e) {
    delete container;
}

void Win::getContainer(QWidget *c) {
    container = c;
}
