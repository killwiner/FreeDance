/*************************************************************************/
/* This file is part of Tron.                                            */
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

#include <QApplication>
#include "interf.h"
#include <QtQml>
#include <QQuickView>
#include "win.h"

#include <sys/resource.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
/*
    struct rlimit stack_limits;
    stack_limits.rlim_cur = stack_limits.rlim_max = 16 * 1024 * 1024;
    setrlimit(RLIMIT_STACK, &stack_limits);
*/
    system("ulimit -s 16000");

    QQuickView *view = new QQuickView();
    Win *win = new Win;

    Interf interf;

    view->rootContext()->setContextProperty("interf", &interf);

    QWidget *container = QWidget::createWindowContainer(view, win);
    container->setMinimumSize(1284, 250);
    container->setMaximumSize(1284, 250);
    container->setFocusPolicy(Qt::TabFocus);
    win->getContainer(container);

    view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(container);
    layout->addWidget(interf.getwidget());
    win->setLayout(layout);

    interf.init_values(32, 128, 62, 10, 4, 3, 8);

    win->setGeometry(100,100,1284,600);
    QPalette Pal;
    // set background color
    Pal.setColor(QPalette::Background, Qt::darkGray);
    win->setAutoFillBackground(true);
    win->setPalette(Pal);

    win->show();

    return a.exec();
}
