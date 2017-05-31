#ifdef TESTS

#include "testsuite.h"

std::vector<QObject*> QTestSuite::m_suites;

QTestSuite::QTestSuite() : QObject(), cursor(0)
{
    m_suites.push_back(this);
}

void QTestSuite::loadFile(const QString &file_name) {

    QFile FileData(file_name);

    if (!FileData.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("Ne peut lire le fichier data.");

    QDataStream DataStream(&FileData);
    QString Line;
    QStringList List;

    while (!FileData.atEnd()) {

        Line = FileData.readLine();
        List = Line.split(";");

        ListData.push_back(List);

    }
    FileData.close();
}

void QTestSuite::readFile(const quint16 &nbr)
{

    data.resize(0);

    if(ListData.size() < cursor + nbr)
        QFAIL("Dépassement de capacité sur la liste de données");

    qint16 i = cursor;

    for(; i < cursor + nbr; ++i)
        data.push_back((ListData.begin() + i)->begin());

    cursor = i;
}

#endif // TESTS
