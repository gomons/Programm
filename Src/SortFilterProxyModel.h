#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QMap>
#include "AbstractTextMatcher.h"

class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterProxyModel(QObject * parent = 0);
    ~SortFilterProxyModel();

    void resetTextMatchers();
    void addTextMatcher(const QString &name, QSharedPointer<AbstractTextMatcher> matcher);

    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QMap<QString, QSharedPointer<AbstractTextMatcher>> textMatchers;
};

#endif // SORTFILTERPROXYMODEL_H
