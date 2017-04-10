#include "tests.h"

int main(int argc, char *argv[])
{

    QApplication Application(argc, argv);

    #ifdef TESTS

    rendering::TestsOpenglR renderImgs(24, 1000);
    Tests tests(&renderImgs);

    #endif //TESTS

}
