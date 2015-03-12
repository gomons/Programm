#ifndef VIEWRECORDDLG_H
#define VIEWRECORDDLG_H

#include <QDialog>

namespace Ui {
class ViewRecordDlg;
}

class QSqlTableModel;

class ViewRecordDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecordDlg(QSqlTableModel *model, int row, QWidget *parent = 0);
    ~ViewRecordDlg();

private slots:
    void edit();
    void print();

private:
    void showInfo();

    Ui::ViewRecordDlg *ui;
    QSqlTableModel *model;
    int row;
};

#endif // VIEWRECORDDLG_H
