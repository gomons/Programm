#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QStringList>

#include "SortFilterProxyModel.h"

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
    void Filter();

private:
    void showOnlyColumns(const QStringList &columns);

    Ui::MainWindow *ui;
    QSqlTableModel *model;
    SortFilterProxyModel *sortFilterModel;
};

#endif // MAINWINDOW_H
