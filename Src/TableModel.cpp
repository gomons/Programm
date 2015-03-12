#include "TableModel.h"

TableModel::TableModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db)
{
}

TableModel::~TableModel()
{
}

