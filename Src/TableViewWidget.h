#ifndef TABLEVIEWWIDGET_H
#define TABLEVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class TableViewWidget;
}

class SortFilterProxyModel;

class TableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableViewWidget(SortFilterProxyModel *model, QWidget *parent = 0);
    ~TableViewWidget();

    void showOnlyHeaders(const QStringList& names);
    QList<int> getSelectedRows();

public slots:
    void changeShownHeaders();
    void saveShownHeaders();
    void restoreShownHeaders();

private:
    void renameHeaders();
    QStringList getShownHeaders();

    Ui::TableViewWidget *ui;
    SortFilterProxyModel *model;

    QStringList savedShownHeaders;
};

#endif // TABLEVIEWWIDGET_H
