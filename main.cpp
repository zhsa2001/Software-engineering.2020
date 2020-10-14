#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>

void openmydb();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    openmydb();
    MainWindow w;
    w.show();

    return a.exec();
}

void openmydb(){
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("mydb");
    db.setUserName("root");
    db.setPassword("1234");
    db.setHostName("localhost");
    db.setPort(3306);
    db.open();
}
