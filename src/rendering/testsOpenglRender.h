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

#ifndef RTESTSOPENGL_H
#define RTESTSOPENGL_H

#ifdef TESTS

#include "render.h"

// types de tests
enum TESTS_OPENGL {
    TEST_TRIANGLE,
    TEST_IMAGE,
    TEST_VIDEO
};

namespace rendering {

class TestsOpenglR: public Render {
    Q_OBJECT

public:
    // interval_time : interval time between each image
    // framesPerSecond : max of frames per second
    TestsOpenglR(const quint16 &framesPerSecond, const quint16 &interval_time);
    virtual ~TestsOpenglR();

    // affiche l'animation pour une certaine durée
    // max_count : nombre de tops pour la durée de la boucle affichage
    void loop_paint(const quint8 &test_funct, const quint32 &max_count);

public slots:
    // Applique les changements à chaque top horloge
    void next_step();

signals:
    // signal de test
    void test_timeout();
    // signal pour lever le vérou de la kinect
    void KinectSignal();

protected:
    // surcharge de la méthode paintGL
    virtual void paintGL();

private:
    void drawTriangle();
    void drawImage();
    void drawVideo();

    // itérations de la boucle animations
    quint32 count;

    // gestion des couleurs
    float color;
    bool color_up_down;

    // 3 valeurs : TEST_TRIANGLE, TEST_IMAGE et TEST_VIDEO
    quint8 test_funct_;
};
}

#endif //TESTS

#endif // RTESTSOPENGL_H
