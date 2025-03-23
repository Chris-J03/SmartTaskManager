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


void MainWindow::on_btnDisplayTask_clicked()
{
    displayDatabase();
}

