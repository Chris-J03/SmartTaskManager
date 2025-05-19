#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

void connectToDatabase() {
    // Create the database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tasks.db");  // SQLite file will be created in the same directory

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }

    qDebug() << "Database connected successfully!";

    // Create a table if not existing
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, name TEXT, status INTEGER)");
}

void displayDatabase() {
    QSqlQuery query;
    query.exec("SELECT * FROM tasks");
    //query.exec("SELECT * FROM status");
    while (query.next()) {
        qDebug() << "Task:" << query.value("name").toString(); //<< "Status:" << query.value("status").toString();
    }
}

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
    connectToDatabase();
    return a.exec();
}
