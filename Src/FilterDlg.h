#ifndef FILTERDLG_H
#define FILTERDLG_H

#include <QDialog>

namespace Ui {
class FilterDlg;
}

class FiltersContainerWidget;
class SortFilterProxyModel;

class FilterDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDlg(SortFilterProxyModel *model, QWidget *parent = 0);
    ~FilterDlg();

    void retranslate();

private:
    Ui::FilterDlg *ui;
    FiltersContainerWidget *filtersContainerWidget;
};

#endif // FILTERDLG_H
