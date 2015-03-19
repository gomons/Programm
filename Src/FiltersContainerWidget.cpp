#include "FiltersContainerWidget.h"
#include "ui_FiltersContainerWidget.h"
#include <QLabel>
#include <QToolButton>
#include "AbstractFilterWidget.h"
#include "IntFilterWidget.h"
#include "SortFilterProxyModel.h"
#include "BorrowerTableInfo.h"
#include "TextFilterWidget.h"

FiltersContainerWidget::FiltersContainerWidget(SortFilterProxyModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FiltersContainerWidget),
    model(model)
{
    ui->setupUi(this);

    fillFiltersComboBox();

    layout = new QGridLayout();
    layout->setSpacing(2);
    layout->setMargin(2);
    ui->filtersWidgetsContainer->setLayout(layout);

    connect(ui->addFilterButton, SIGNAL(clicked()), this, SLOT(addFilterWidget()));
    connect(ui->filterButton, SIGNAL(clicked()), this, SLOT(filter()));
}

FiltersContainerWidget::~FiltersContainerWidget()
{
    delete ui;
}

void FiltersContainerWidget::retranslate()
{
    ui->retranslateUi(this);
    fillFiltersComboBox();
}

void FiltersContainerWidget::filter()
{
    model->resetTextMatchers();

    foreach (AbstractFilterWidget *filterWidget, filtersWidgets)
    {
        QString filterName = filterWidget->getFilterName();
        QSharedPointer<AbstractTextMatcher> filterTextMatcher = filterWidget->getTextMatcher();
        model->addTextMatcher(filterName, filterTextMatcher);
    }

    model->invalidate();

    emit filteringComplete();
}

void FiltersContainerWidget::addFilterWidget()
{
    QString filterName = ui->filterNameCombobox->currentText();

    if (isFilterWidgetPresent(filterName))
        return;

    AbstractFilterWidget* filterWidget = createFilterWidget(filterName);
    if (!filterWidget)
        return;

    filtersWidgets << filterWidget;
    filterWidget->setFilterName(filterName);

    QLabel *filterNameLabel = new QLabel(filterName);
    QToolButton *deleteButton = new QToolButton();
    deleteButton->setStyleSheet("border: none");
    deleteButton->setIcon(QIcon(":/icons/remove.png"));

    int currRow = layout->rowCount();
    layout->addWidget(filterNameLabel, currRow, 0);
    layout->addWidget(filterWidget, currRow, 1);
    layout->addWidget(deleteButton, currRow, 2);

    connect(deleteButton, SIGNAL(clicked()), filterNameLabel, SLOT(deleteLater()));
    connect(deleteButton, SIGNAL(clicked()), filterWidget, SLOT(deleteLater()));
    connect(deleteButton, SIGNAL(clicked()), deleteButton, SLOT(deleteLater()));

    connect(filterWidget, SIGNAL(filterRemoved(QString)), this, SLOT(removeFilterWidget(QString)));
}

void FiltersContainerWidget::removeFilterWidget(const QString &filterName)
{
    foreach (AbstractFilterWidget *filterWidget, filtersWidgets)
    {
        if (filterWidget->getFilterName() == filterName)
        {
            filtersWidgets.remove(filterWidget);
            return;
        }
    }
}

void FiltersContainerWidget::fillFiltersComboBox()
{
    ui->filterNameCombobox->clear();

    BorrowerTableInfo tableInfo;
    QStringList filterNames;
    filterNames << tableInfo.nameFieldAlias
                << tableInfo.surnameFieldAlias
                << tableInfo.patronymicFieldAlias
                << tableInfo.activityFieldAlias
                << tableInfo.loanGuaranteeFieldAlias
                << tableInfo.belongingFieldAlias
                << tableInfo.amountFieldAlias
                << tableInfo.regionFieldAlias
                << tableInfo.placeFieldAlias
                << tableInfo.contactFieldAlias;

    ui->filterNameCombobox->addItems(filterNames);
}

bool FiltersContainerWidget::isFilterWidgetPresent(const QString &filterName)
{
     foreach (AbstractFilterWidget *filterWidget, filtersWidgets)
        if (filterWidget->getFilterName() == filterName)
            return true;
    return false;
}

AbstractFilterWidget* FiltersContainerWidget::createFilterWidget(const QString &filterName)
{
    BorrowerTableInfo tableInfo;

    QMap<QString, QString> nameTypeMap = tableInfo.getNameTypeMap();
    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();

    QString name = nameAliasMap.key(filterName);
    QString type = nameTypeMap.value(name);

    if (type == tableInfo.textType)
    {
        auto filterWidget = new TextFilterWidget(this);
        filterWidget->setFilterName(filterName);
        return filterWidget;
    }
    else if (type == tableInfo.integerType)
    {
        auto filterWidget = new IntegerFilterWidget(this);
        filterWidget->setFilterName(filterName);
        return filterWidget;
    }

    return nullptr;
}
