#ifndef FILTERSCONTAINERWIDGET_H
#define FILTERSCONTAINERWIDGET_H

#include <QSet>
#include <QWidget>

namespace Ui {
class FiltersContainerWidget;
}

class QGridLayout;

class AbstractFilterWidget;
class SortFilterProxyModel;

class FiltersContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FiltersContainerWidget(SortFilterProxyModel *model, QWidget *parent = 0);
    ~FiltersContainerWidget();

signals:
    void beforeFilter();
    void afterFilter();

private slots:
    void filter();
    void addFilterWidget();
    void removeFilterWidget(const QString& filterName);

private:
    bool isFilterWidgetPresent(const QString &filterName);
    AbstractFilterWidget* createFilterWidget(const QString &filterName);

    Ui::FiltersContainerWidget *ui;
    SortFilterProxyModel *model;
    QGridLayout* layout;
    QSet<AbstractFilterWidget*> filtersWidgets;
};

#endif // FILTERSCONTAINERWIDGET_H
