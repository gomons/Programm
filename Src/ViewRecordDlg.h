#ifndef VIEWRECORDDLG_H
#define VIEWRECORDDLG_H

#include <QDialog>

namespace Ui {
class ViewRecordDlg;
}

class QSqlRelationalTableModel;

class ViewRecordDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecordDlg(QSqlRelationalTableModel *model, int row, QWidget *parent = 0);
    ~ViewRecordDlg();

signals:
    void edit(int row);

private slots:
    void edit();
    void print();
    void showInfo();

private:
    Ui::ViewRecordDlg *ui;
    QSqlRelationalTableModel *model;
    int row;
};

#endif // VIEWRECORDDLG_H
