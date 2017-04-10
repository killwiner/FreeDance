#ifndef TESTSUITE_H
#define TESTSUITE_H

#ifdef TESTS

#include <QFile>
#include <QDataStream>
#include <QString>

// Classe de base pour tester les objets

#include <QtTest/QtTest>
#include <vector>

class QTestSuite : public QObject
{
    Q_OBJECT

public:

// Nombre d'objets à tester
    static std::vector<QObject*> m_suites;
    explicit QTestSuite();

protected:

    void loadFile(const QString &file_name);
    // nbr : nombre de lignes à lire
    void readFile(const quint16& nbr);

    //itérateurs sur chaque ligne du tableau de données
    std::vector<QStringList::iterator> data;

//private:
    // tableau de données
    std::vector<QStringList> ListData;

    // indentation sur le tableau de données
    quint16 cursor;
};

#endif // TESTS
#endif // TESTSUITE_H
