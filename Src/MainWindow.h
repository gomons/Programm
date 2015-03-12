#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QStringList>

#include "AbstractFilterWidget.h"
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

//    void addFilter();
//    void removeFilter(const QString filterName);
//    void filter();


private:
    void showOnlyColumns(const QMap<QString, QString> &names, const QMap<QString, int> &order);

    Ui::MainWindow *ui;
    QSqlTableModel *model;
    SortFilterProxyModel *sortFilterModel;

    //QMap<QString, AbstractFilterWidget*> filtersWidgets;
};

#endif // MAINWINDOW_H
