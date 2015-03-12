#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlTableModel>

class TableModel: public QSqlTableModel
{
public:
    TableModel(QObject * parent = 0, QSqlDatabase db = QSqlDatabase());
    ~TableModel();
};

#endif // TABLEMODEL_H
