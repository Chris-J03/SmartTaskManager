#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QStyledItemDelegate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddTask_clicked();
    void onItemChanged(QListWidgetItem *item);
    void on_btnClear_clicked();
    void showContextMenu(const QPoint &pos);
    void deleteSelectedTask();
private:
    Ui::MainWindow *ui;

    void displayDatabase();
    void connectToDatabase();
};

#endif // MAINWINDOW_H
