#ifndef TABLEVIEWWIDGET_H
#define TABLEVIEWWIDGET_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class TableViewWidget;
}

class QSqlRelationalTableModel;
class SortFilterProxyModel;

class TableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableViewWidget(QSqlRelationalTableModel *model,
                             SortFilterProxyModel *proxyModel,
                             QWidget *parent = 0);
    ~TableViewWidget();

    void showOnlyHeaders(const QStringList& names);
    QStringList getShownHeaders();

    QList<int> getSelectedRows();

signals:
    void rowDoubleClicked(int);

private slots:
    void rowDoubleClicked(QModelIndex index);

private:
    void renameHeaders();

    Ui::TableViewWidget *ui;
    QSqlRelationalTableModel *model;
    SortFilterProxyModel *proxyModel;
    QStringList savedShownHeaders;
};

#endif // TABLEVIEWWIDGET_H
