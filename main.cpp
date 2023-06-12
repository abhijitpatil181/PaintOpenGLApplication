#include "PaintApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintApplication w;
    w.setWindowTitle("Welcome To Paint Application");
    w.show();
    return a.exec();
}
