#ifndef ABSTRACTFILTERWIDGET_H
#define ABSTRACTFILTERWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include "AbstractTextMatcher.h"

class AbstractFilterWidget: public QWidget
{
    Q_OBJECT

public:
    AbstractFilterWidget(QWidget * parent = 0, Qt::WindowFlags f = 0) :
        QWidget(parent, f)
    {}
    virtual ~AbstractFilterWidget()
    {}

    virtual void setFilterName(const QString &name)
    {
        this->name = name;
    }
    virtual QString getFilterName()
    {
        return name;
    }

    virtual QSharedPointer<AbstractTextMatcher> getTextMatcher() = 0;

signals:
    void filterRemoved(const QString &filterName);

private:
    QString name;
};

#endif // ABSTRACTFILTERWIDGET_H
