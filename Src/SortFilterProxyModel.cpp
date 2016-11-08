#include "SortFilterProxyModel.h"
#include "BorrowerTableInfo.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlField>
#include "ColorMap.h"

#include <QDebug>
#include <QSqlRelation>

SortFilterProxyModel::SortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{}

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
        QString colorDisplayName = QSortFilterProxyModel::data(index(idx.row(), tableInfo.colorIdFieldID), Qt::DisplayRole).toString();
        ColorMap colorMap;
        QColor color = colorMap.getColor(colorDisplayName);
        return color;
    }
    QVariant currData = QSortFilterProxyModel::data(idx, role);
    return currData;
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
