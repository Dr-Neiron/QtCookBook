#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator myTranslator;
    myTranslator.load(":/translations/qtcookbook_" + QLocale::system().name());
    a.installTranslator(&myTranslator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
