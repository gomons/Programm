#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QSqlTableModel;

class TableViewWidget;
class SortFilterProxyModel;
class FiltersContainerWidget;
class FilterDlg;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addRecord();
    void removeRecord();
    void showFilters();
    void showAbout();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    SortFilterProxyModel *proxyModel;
    TableViewWidget *tableViewWidget;
    FilterDlg *filterDlg;
};

#endif // MAINWINDOW_H
