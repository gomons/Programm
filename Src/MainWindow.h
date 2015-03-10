#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void submit();
    void select();

private slots:
    void addRecord();
    void viewRecord(const QModelIndex &modelIndex);
    void removeSelectedRecords();

private:
    void showOnlyColumns(const QStringList &columns);

    Ui::MainWindow *ui;
    QSqlTableModel *model;
    QSortFilterProxyModel *sortFilterModel;
};

#endif // MAINWINDOW_H
