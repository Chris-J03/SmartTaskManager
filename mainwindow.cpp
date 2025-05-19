#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddTask_clicked()
{
    QString task = ui->txtAddTask->text();
    addToDatabase(task);
}

void MainWindow::on_btnDisplayTask_clicked() {
    QSqlQuery query("SELECT name, status FROM tasks");
    while (query.next()) {
        QString name = query.value(0).toString();
        int status = query.value(1).toInt();

        QString statusText = (status == 0) ? "Pending" : "Done";
        ui->taskOutput->append(name + " - " + statusText);
    }
}

