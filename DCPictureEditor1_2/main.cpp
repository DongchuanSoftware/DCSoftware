#include "mainwindow.h"
#include <QApplication>
#include<QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QTranslator trl;
    trl.load(":/Languages/Chinese/qt_zh_CN.qm");
    a.installTranslator(&trl);
    
    MainWindow w;
    w.show();
    
    return a.exec();
}
