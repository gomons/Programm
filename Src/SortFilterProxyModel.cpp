#include "SortFilterProxyModel.h"
#include "TableInfo.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

SortFilterProxyModel::~SortFilterProxyModel()
{
}

void SortFilterProxyModel::resetTextMatchers()
{
    textMatchers.clear();
}

void SortFilterProxyModel::addTextMatcher(const QString &name, QSharedPointer<AbstractTextMatcher> matcher)
{
    textMatchers.insert(name, matcher);
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    TableInfo tableInfo;

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
