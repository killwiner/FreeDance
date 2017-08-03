#ifndef TESTSDRAW_H
#define TESTSDRAW_H

#ifdef TESTS

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "draw.h"
#include "../rendering/loadimgs.h"

namespace draw {

class TestsDraw: public QTestSuite {
    Q_OBJECT

public:
    TestsDraw(rendering::TestsOpenglR *render);

private slots:
    void drawLine();
    void drawPoint();

private:
    rendering::TestsOpenglR *render_;
};

}

#endif // TESTS

#endif // TESTSDRAW_H
