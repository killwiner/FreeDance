#ifndef INTERF_H
#define INTERF_H

#include <sstream>
#include <QObject>
#include "run.h"

class Interf : public QObject
{
    Q_OBJECT

public:

    explicit Interf();
    QWidget *getwidget();

signals:
    void sendToQml_fbt(QString val);
    void sendToQml_fbs(int val);

public:
    Q_INVOKABLE void receiveFromQml_fbt(QString val);
    Q_INVOKABLE void receiveFromQml_fbs(int val);
    Q_INVOKABLE void receiveFromQml_menuBar(int menu_value, QString file_name);

    void getrun(QSharedPointer<Run> &);

private:
    QSharedPointer<Run> SP_run;
};

#endif // INTERF_H
