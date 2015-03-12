#ifndef SELECTHEADERFIELDSDLG_H
#define SELECTHEADERFIELDSDLG_H

#include <QDialog>
#include <QStringList>
#include <QList>

namespace Ui {
class SelectHeaderFieldsDlg;
}

class QCheckBox;

class SelectHeaderFieldsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelectHeaderFieldsDlg(const QStringList &selected = QStringList(), QWidget *parent = 0);
    ~SelectHeaderFieldsDlg();

    QStringList getSelectedHeaderFields();

private:
    Ui::SelectHeaderFieldsDlg *ui;
    QList<QCheckBox*> checkboxes;
};

#endif // SELECTHEADERFIELDSDLG_H
