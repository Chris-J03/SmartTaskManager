#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectToDatabase();
    displayDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddTask_clicked()
{
    QString task = ui->txtAddTask->text();
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
        displayDatabase();
    }
}

void MainWindow::displayDatabase() {
    QSqlQuery query("SELECT name, status FROM tasks");
    ui->taskOutput->clear();
    while (query.next()) {
        QString name = query.value(0).toString();
        int status = query.value(1).toInt();

        QString statusText = (status == 0) ? "Pending" : "Done";
        ui->taskOutput->append(name + " - " + statusText);
    }
}

void MainWindow::connectToDatabase() {
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

