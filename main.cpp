#include "hakimi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Hakimi w;
    w.show();
    return a.exec();
}
