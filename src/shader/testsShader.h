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

#ifndef TESTSSHADER_H
#define TESTSSHADER_H

#ifdef TESTS

#include "testsuite.h"
#include "../rendering/testsOpenglRender.h"
#include "../rendering/loadimgs.h"
#include "testsShaderRender.h"

namespace shader {

class TestsShader: public QTestSuite {
    Q_OBJECT

public:
    TestsShader();
    ~TestsShader();

private:

private slots:
    void testLoadFileFail();
    void testLoadFileSucces();
    void testBuildFail();
    void testBuildSucces();
    void testControlBuildFail();
    void testControlBuildSucces();
    void testControlLinkFail();
    void testControlLinkSucces();
    void testAffichage();
};

}

#endif // TESTS

#endif // TESTSSHADER_H
