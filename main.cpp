#include "vcfmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VCFManager w;
    w.show();

    return a.exec();
}
