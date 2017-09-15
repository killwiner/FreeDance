/*************************************************************************/
/* This file is part of FreeDance.                                       */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

#ifndef TESTSCIRCULARVECTOR_H
#define TESTSCIRCULARVECTOR_H

#ifdef TESTS

#include "testsuite.h"
#include "circularvector.h"

namespace tools {

class TestsCircularVector : public QTestSuite {
    Q_OBJECT

public:
    TestsCircularVector();

private slots:
    void testPushBack();
    void testAt();
    void testLength();
};
}
#endif // TESTS

#endif // TESTSCIRCULARVECTOR_H
