#include "testscircularvector.h"

#ifdef TESTS

namespace tools {

TestsCircularVector::TestsCircularVector()
{

}

void TestsCircularVector::testPushBack()
{
    CircularVector<quint8> circularVector(5);

    for(quint8 i = 5; i < 20; ++i)
        circularVector.push_back(i);

    QCOMPARE(circularVector.at(3), (quint8)18);
}

void TestsCircularVector::testAt()
{
    CircularVector<quint8> circularVector(5);

    for(quint8 i = 5; i < 10; ++i)
        circularVector.push_back(i);

    QCOMPARE(circularVector.at(3), (quint8)8);
    QCOMPARE(circularVector.at(11), (quint8)6);
    QCOMPARE(circularVector.at(-7), (quint8)8);

}

void TestsCircularVector::testLength()
{
    CircularVector<quint8> circularVector(5);

    for(quint8 i = 5; i < 10; ++i)
        circularVector.push_back(i);

    QCOMPARE(circularVector.length(1, 4), (quint32)4);
    QCOMPARE(circularVector.length(3, 1), (quint32)4);
}

void TestsCircularVector::testPtr()
{
    CircularVector<quint8> circularVector(5);
    for(quint8 i = 5; i < 10; ++i)
        circularVector.push_back(i);

    QCOMPARE(circularVector.ptr(1), circularVector.ptr(6));
}
}

#endif //TESTS
