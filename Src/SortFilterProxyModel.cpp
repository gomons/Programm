#include "SortFilterProxyModel.h"
#include "BorrowerTableInfo.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlField>

SortFilterProxyModel::SortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    updateColorsMap();
}

SortFilterProxyModel::~SortFilterProxyModel()
{}

void SortFilterProxyModel::resetTextMatchers()
{
    textMatchers.clear();
}

void SortFilterProxyModel::addTextMatcher(const QString &name, QSharedPointer<AbstractTextMatcher> matcher)
{
    textMatchers.insert(name, matcher);
}

QVariant SortFilterProxyModel::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::BackgroundRole)
    {
        BorrowerTableInfo tableInfo;
        int currBorrowerId = QSortFilterProxyModel::data(index(idx.row(), tableInfo.idFieldID), Qt::DisplayRole).toInt();
        if (borrowerIdColorMap.contains(currBorrowerId))
        {
            QColor rowColor = borrowerIdColorMap.value(currBorrowerId);
            return rowColor;
        }
    }
    QVariant currData = QSortFilterProxyModel::data(idx, role);
    return currData;
}

void SortFilterProxyModel::updateColorsMap()
{
    borrowerIdColorMap.clear();

    QString sql = "SELECT * FROM colors";
    QSqlQuery query;
    query.exec(sql);
    query.next();
    while(query.isValid())
    {
        QSqlRecord record = query.record();
        QColor color = record.value(1).toString();
        int borrowerId = record.value(2).toInt();
        borrowerIdColorMap.insert(borrowerId, color);
        query.next();
    }
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    BorrowerTableInfo tableInfo;

    QMap<int, QString> idNameMap = tableInfo.getIdNameMap();
    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();
    QStringList aliases = tableInfo.getAliases();

    foreach (const QString &matcherName, textMatchers.keys())
    {
        if (aliases.contains(matcherName))
        {
            QString name = nameAliasMap.key(matcherName);
            int id = idNameMap.key(name);
            QModelIndex index = sourceModel()->index(sourceRow, id, sourceParent);
            QString text = sourceModel()->data(index).toString();
            bool matchRes = textMatchers.value(matcherName)->isTextMatch(text);
            if (!matchRes)
                return false;
        }
    }
    return true;
}
