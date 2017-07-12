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

#ifndef TESTSRENDER_H
#define TESTSRENDER_H

#ifdef TESTS

#include "testsuite.h"
#include "testsOpenglRender.h"
#include "loadimgs.h"

namespace rendering {

class TestsRender: public QTestSuite {
     Q_OBJECT

public:
    TestsRender(rendering::TestsOpenglR *render);
    virtual ~TestsRender();

private:
    rendering::TestsOpenglR *render_;

    // window size
    int width, height;

private slots:

    void affiche_fenetre();
    void fenetre_active();
    void timer();
    void generation_d_un_triangle();
    void affichage_d_une_image();
    void affichage_d_une_video();
};

}

#endif // TESTS

#endif // TESTS_H
