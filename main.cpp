#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(600,400);//将对话框宽设为600，高设置为400
    w.show();

    return a.exec();
}
