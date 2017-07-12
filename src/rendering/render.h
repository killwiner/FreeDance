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

#ifndef RENDER_H
#define RENDER_H

#include <QtOpenGL>
#include <QGLWidget>
#include <opencv2/core.hpp>
#include <iostream>
#include <QSharedPointer>

#define QSPVImage QSharedPointer< std::vector<cv::Mat> >

namespace rendering {

class Render : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:

    Render();
    // interval_time : interval time between each image
    // framesPerSecond : max of frames per second
    Render(const quint16 &framesPerSecond, const quint16 &interval_time);
    virtual ~Render();

    // accesseurs
    bool toClose() const;

    // set a vector of images for a video
    void setImages(const QSPVImage &VImage);
    // set only one image
    void setImage(const cv::Mat *Image);

public slots:
    // actions gérées sur chaque top horloge
    virtual void timeOutSlot();

signals:
    // événement lorsqu'on ferme la fenêtre
    void close();

protected:
    QTimer *t_Timer;

    GLuint texture;
    QSPVImage PVImage_;

    // actions gérées lors de la fermeture de la fenêtre
    void closeEvent(QCloseEvent *event);

    // méthodes virtuelles sur l'affichage OpenGL
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();

private:
    // Etat courant de la fenêtre, fermée ou non
    bool closing;

};
}

#endif // RENDER_H
