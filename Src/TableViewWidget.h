#ifndef TABLEVIEWWIDGET_H
#define TABLEVIEWWIDGET_H

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class TableViewWidget;
}

class TableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableViewWidget(QAbstractItemModel *model, QWidget *parent = 0);
    ~TableViewWidget();

    void showOnlyHeaders(const QStringList& names);

public slots:
    void changeShownHeaders();

private:
    void RenameModelHeader();

    Ui::TableViewWidget *ui;
    QAbstractItemModel *model;
};

#endif // TABLEVIEWWIDGET_H
