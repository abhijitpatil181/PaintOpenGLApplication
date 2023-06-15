#include "PaintApplication.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintApplication w;
    w.setWindowTitle("Paint Application");
    w.resize(800,600);
    w.show();
    
    return a.exec();
    
}
