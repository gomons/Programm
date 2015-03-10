#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QRegExp>

class SortFilterProxyModel : public QSortFilterProxyModel
{
public:
    SortFilterProxyModel(QObject * parent = 0);
    ~SortFilterProxyModel();

    void resetRegExps();

    void setNameRegExp(const QRegExp& regExp);
    void setSurnameRegExp(const QRegExp& regExp);
    void setPatronymicRegExp(const QRegExp& regExp);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;


private:
    QRegExp nameRegExp;
    QRegExp surnameRegExp;
    QRegExp patronymicRegExp;
};

#endif // SORTFILTERPROXYMODEL_H
