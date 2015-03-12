#ifndef FILTERSCONTAINERWIDGET_H
#define FILTERSCONTAINERWIDGET_H

#include <QWidget>
#include <QSet>
#include "AbstractFilterWidget.h"
#include "SortFilterProxyModel.h"

namespace Ui {
class FiltersContainerWidget;
}

class QGridLayout;

class FiltersContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FiltersContainerWidget(QAbstractItemModel *sourceModel, QWidget *parent = 0);
    ~FiltersContainerWidget();

    SortFilterProxyModel* getProxyModel();

private slots:
    void filter();

    void addFilterWidget();
    void removeFilterWidget(const QString& filterName);

private:
    bool isFilterWidgetPresent(const QString &filterName);
    AbstractFilterWidget* createFilterWidget(const QString &filterName);

    Ui::FiltersContainerWidget *ui;
    SortFilterProxyModel *sortFilterModel;
    QGridLayout* layout;
    QSet<AbstractFilterWidget*> filtersWidgets;
};

#endif // FILTERSCONTAINERWIDGET_H
