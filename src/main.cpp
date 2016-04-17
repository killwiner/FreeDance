#include <QApplication>
#include "interf.h"
#include <QtQml>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QQuickView *view = new QQuickView();
    QWidget *win = new QWidget;
    //QSharedPointer<Run> SP_run(new Run());

    Interf interf;
    //interf.getrun(SP_run);
    view->rootContext()->setContextProperty("interf", &interf);

    QWidget *container = QWidget::createWindowContainer(view, win);
    container->setMinimumSize(1310, 250);
    container->setMaximumSize(1310, 250);
    container->setFocusPolicy(Qt::TabFocus);

    view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(container);
    layout->addWidget(interf.getwidget());
    win->setLayout(layout);

    win->show();

    return a.exec();
}
