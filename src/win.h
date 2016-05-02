#ifndef WIN_H
#define WIN_H
#include <QWidget>

class Win : public QWidget
{
public:
    Win();
    void getContainer(QWidget *);

protected:
    // to delete the container, without this we have a sigsegv error
    // la libération de container ne se fait pas toute seule
    void closeEvent(QCloseEvent *);

private:
    QWidget *container;
};

#endif // WIN_H
