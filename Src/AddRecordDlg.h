#ifndef ADDRECORDDLG_H
#define ADDRECORDDLG_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class AddRecordDlg;
}

class QSqlRelationalTableModel;
class QDataWidgetMapper;

class AddRecordDlg : public QDialog
{
    Q_OBJECT

public:
    AddRecordDlg(QSqlRelationalTableModel *model, QWidget *parent = 0);
    AddRecordDlg(QSqlRelationalTableModel *model, int row, QWidget *parent = 0);
    ~AddRecordDlg();

private slots:
    void accepted();
    void removePhoto();
    void loadPhoto();

private:
    void prepareDlg();
    bool showPhoto();

    Ui::AddRecordDlg *ui;
    QSqlRelationalTableModel *model;
    QDataWidgetMapper *mapper;
    QPixmap photoPixmap;
    QString oldPhotoFilepath;
};

#endif // ADDRECORDDLG_H
