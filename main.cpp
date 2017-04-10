#include "qutecursor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuteCursor w;
    w.show();

    return a.exec();
}
