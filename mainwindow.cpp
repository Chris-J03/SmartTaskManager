#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->taskDisplay, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);
    connect(ui->txtAddTask, &QLineEdit::returnPressed, this, &MainWindow::on_btnAddTask_clicked);
    connectToDatabase();
    displayDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddTask_clicked() {
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
        ui->txtAddTask->clear();
    }
}

void MainWindow::displayDatabase() {
    QSqlQuery query("SELECT id, name, status FROM tasks");
    ui->taskDisplay->clear();
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int status = query.value(2).toInt();

        QListWidgetItem* item = new QListWidgetItem(name, ui->taskDisplay);
        item->setData(Qt::UserRole, id);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);  // Make it checkable
        if (status == 0) {
            item->setCheckState(Qt::Unchecked);
        } else {
            item->setCheckState(Qt::Checked);
        }
    }
}

void MainWindow::connectToDatabase() {
    // Create the database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tasks.db");

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }

    qDebug() << "Database connected successfully!";

    // CREATE TABLE
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, status INTEGER)")) {
        qDebug() << "Create table error:" << query.lastError().text();
    }
}

void MainWindow::onItemChanged(QListWidgetItem* item) {
    if (!item) return;

    int taskId = item->data(Qt::UserRole).toInt();
    int newStatus = (item->checkState() == Qt::Checked) ? 1 : 0;

    QSqlQuery query;
    query.prepare("UPDATE tasks SET status = :status WHERE id = :id");
    query.bindValue(":status", newStatus);
    query.bindValue(":id", taskId);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
    }
}

void MainWindow::on_btnClear_clicked() {
    QSqlQuery query;
    query.exec("DELETE FROM tasks");
    displayDatabase();
}
