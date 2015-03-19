#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QSqlRelationalTableModel;

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
    void removeRecords();
    void showAddRecordDlg();
    void showEditRecordDlg(int row);
    void showViewRecordDlg(int row);
    void showFilterDlg();
    void showSelectHeaderFieldsDlg();
    void showAboutDlg();

private:
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *model;
    SortFilterProxyModel *proxyModel;
    TableViewWidget *tableViewWidget;
    FilterDlg *filterDlg;
};

#endif // MAINWINDOW_H
