#include "spider2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Spider2 w;
    w.show();
    return a.exec();
}
