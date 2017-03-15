#include "breakthroughwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BreakThroughWidget w;
    w.show();

    return a.exec();
}
