#include <QApplication>
#include "interf.h"
#include <QtQml>
#include <QQuickView>
#include "win.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


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

    interf.init_values(32, 128, 62, 10, 4);

    win->setGeometry(100,100,1284,600);
    QPalette Pal;
    // set background color
    Pal.setColor(QPalette::Background, Qt::darkGray);
    win->setAutoFillBackground(true);
    win->setPalette(Pal);

    win->show();

    return a.exec();
}
