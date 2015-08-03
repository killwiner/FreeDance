#include "progress.h"

Progress::Progress(QWidget *parent)
    : QWidget(parent)
{
    progressBar = new QProgressBar(this);
    progressBar->setGeometry(10, 10, 190, 40);
    progressBar->setRange(0, 100);
    progressBar->setOrientation(Qt::Horizontal);

    QLabel *label = new QLabel("Progress :");

    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(progressBar);

    setLayout(layout);

}

void Progress::value(unsigned int v) {
    progressBar->setValue(v);
    update();
}
