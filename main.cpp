#include "breakthroughwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BreakThroughWidget w;     //példányosítjuk a játékot, majd megjelenítjük
    w.show();

    return a.exec();
}
