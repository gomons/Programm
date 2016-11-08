#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

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

    bool init();

public slots:
    void removeRecords();

    void changeRecordsColorToRed();
    void changeRecordsColorToYellow();
    void changeRecordsColorToGreen();
    void changeRecordsColorToBlue();
    void changeRecordsColorToWhite();

    void changeRecordsColor(QColor color);

    void showAddRecordDlg();
    void showEditRecordDlg(int row);
    void showViewRecordDlg(int row);
    void showFilterDlg();
    void showSelectHeaderFieldsDlg();
    void showAboutDlg();

    void print();

    void translateToEnglish();
    void transletToRussion();

private:
    void f();

    Ui::MainWindow *ui;
    QSqlRelationalTableModel *model;
    SortFilterProxyModel *proxyModel;
    TableViewWidget *tableViewWidget;
    FilterDlg *filterDlg;

    QTranslator programmTranslator;
    QTranslator qtTranslator;
};

#endif // MAINWINDOW_H
