#ifndef PROGRESS_H
#define PROGRESS_H

#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>

class Progress : public QWidget
 {

public:
    explicit Progress(QWidget *parent = 0);
    void value(unsigned int v);

private:
     QProgressBar *progressBar;
     QVBoxLayout *layout;

 };

#endif // PROGRESS_H
