#include "interf.h"
#include <QDebug>

using namespace std;

Interf::Interf() {
    SP_run = QSharedPointer<Run>(new Run());
}

QWidget *Interf::getwidget() {
    return SP_run->getwidget();
}

void Interf::receiveFromQml_fbt(QString val) {

    std::istringstream v_l(val.toStdString().c_str());
    int val_i;
    v_l >> val_i;
    sendToQml_fbs(val_i);
}

void Interf::getrun(QSharedPointer<Run> &r) {
        SP_run = r;
}

void Interf::receiveFromQml_fbs(int val) {
    qDebug() << "Received in C++ from QML:" << val;
    sendToQml_fbt(QString::number(val));
}

void Interf::receiveFromQml_menuBar(int menu_value, QString file_name) {
    qDebug() << "Received in C++ from QML:" << menu_value << " - " << file_name;
    SP_run->load(file_name);
}


