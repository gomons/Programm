#ifndef ADDRECORDDLG_H
#define ADDRECORDDLG_H

#include <QDialog>

namespace Ui {
class AddRecordDlg;
}

class QSqlTableModel;

class AddRecordDlg : public QDialog
{
    Q_OBJECT

public:
    AddRecordDlg(QSqlTableModel *model, QWidget *parent = 0);
    AddRecordDlg(QSqlTableModel *model, int row, QWidget *parent = 0);
    ~AddRecordDlg();

private slots:
    void edit();
    void loadPhoto();

private:
    void connectSignalsAndSlots();
    QString getTableData(int row, int id);
    void setTableData(int row, int id, const QString &data);

    QString writePhotoAndGetName();

    void showPhoto(const QString &fileName);
    void showPhoto(const QByteArray &data);
    void showPhoto(const QPixmap &pixmap);

    QByteArray readFile(const QString &fileName);
    QString getHash(const QByteArray &data);

    Ui::AddRecordDlg *ui;
    QSqlTableModel *model;
    int row;
    QByteArray photoData;

    const QString noPhotoFilename;
};

#endif // ADDRECORDDLG_H
