#include "SortFilterProxyModel.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

SortFilterProxyModel::~SortFilterProxyModel()
{
}

void SortFilterProxyModel::resetRegExps()
{
    nameRegExp = QRegExp();
    surnameRegExp = QRegExp();
    patronymicRegExp = QRegExp();
}

void SortFilterProxyModel::setNameRegExp(const QRegExp& regExp)
{
    nameRegExp = regExp;
}

void SortFilterProxyModel::setSurnameRegExp(const QRegExp& regExp)
{
    surnameRegExp = regExp;
}

void SortFilterProxyModel::setPatronymicRegExp(const QRegExp& regExp)
{
    patronymicRegExp = regExp;
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!nameRegExp.isEmpty())
    {
        QModelIndex nameIndex = sourceModel()->index(sourceRow, 1, sourceParent);
        QString name = sourceModel()->data(nameIndex).toString();
        if (!nameRegExp.exactMatch(name))
            return false;
    }

    if (!surnameRegExp.isEmpty())
    {
        QModelIndex surnameIndex = sourceModel()->index(sourceRow, 2, sourceParent);
        QString surname = sourceModel()->data(surnameIndex).toString();
        if (!surnameRegExp.exactMatch(surname))
            return false;
    }

    if (!patronymicRegExp.isEmpty())
    {
        QModelIndex patronymicIndex = sourceModel()->index(sourceRow, 3, sourceParent);
        QString patronymic = sourceModel()->data(patronymicIndex).toString();
        if (!patronymicRegExp.exactMatch(patronymic))
            return false;
    }

    return true;
}
