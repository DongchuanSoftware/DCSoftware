#include "mainwindow.h"
#include <QApplication>
#include<QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QTranslator trl;
    if(trl.load(":/Languages/Chinese/qt_zh_CN.qm"))
    {
        a.installTranslator(&trl);
    }
    
    MainWindow w;
    w.showMaximized();
    
    return a.exec();
}
