#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

void addToDatabase(QString task) {
    if (task == "") {
        qDebug() << "Cannot insert empty string!";
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (name, status) VALUES (:name, :status)");
    query.bindValue(":name", task);
    query.bindValue(":status", 0);
    if (!query.exec()) {
        qDebug() << "Insert error:" << query.lastError().text();
    } else {
        qDebug() << "Task inserted!";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
