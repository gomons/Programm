#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "AddRecordDlg.h"
#include "ViewRecordDlg.h"
#include "TextFilterWidget.h"
#include "FiltersContainerWidget.h"
#include "TableViewWidget.h"
#include "TableInfo.h"
#include "SelectHeaderFieldsDlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TableInfo tableInfo;

    auto model = new QSqlTableModel(this);
    model->setTable(tableInfo.tableName);
    model->select();

    auto filtersContainerWidget = new FiltersContainerWidget(model, this);
    SortFilterProxyModel* proxyModel = filtersContainerWidget->getProxyModel();

    auto tableViewWidget = new TableViewWidget(proxyModel, this);
    tableViewWidget->showOnlyHeaders(QStringList() << tableInfo.nameFieldAlias
                                                   << tableInfo.surnameFieldAlias
                                                   << tableInfo.patronymicFieldAlias
                                                   << tableInfo.regionFieldAlias
                                                   << tableInfo.placeFieldAlias
                                                   << tableInfo.belongingFieldAlias
                                                   << tableInfo.contactFieldAlias);

    QVBoxLayout *filterGroupBoxLayout = new QVBoxLayout();
    filterGroupBoxLayout->setSpacing(0);
    filterGroupBoxLayout->setMargin(0);
    ui->filterGroupBox->setLayout(filterGroupBoxLayout);
    filterGroupBoxLayout->addWidget(filtersContainerWidget);

    QVBoxLayout *tableGroupBoxLayout = new QVBoxLayout();
    tableGroupBoxLayout->setSpacing(0);
    tableGroupBoxLayout->setMargin(0);
    ui->tableGroupBox->setLayout(tableGroupBoxLayout);
    tableGroupBoxLayout->addWidget(tableViewWidget);

    connect(ui->selectHeadersAction, SIGNAL(triggered()), tableViewWidget, SLOT(changeShownHeaders()));

    //ui->selectHeadersAction

    //sortFilterModel = new SortFilterProxyModel(this);
    //sortFilterModel->setSourceModel(model);



//    QMap<QString, QString> names;
//    QMap<QString, int> order;
//    names["name"] = tr("Name");
//    order["name"] = 1;
//    names["surname"] = tr("Surname");
//    order["surname"] = 2;
//    names["patronymic"] = tr("Patronymic");
//    order["patronymic"] = 3;
//    names["region"] = tr("Region");
//    order["region"] = 4;
//    names["place"] = tr("Place");
//    order["place"] = 5;
//    names["belonging"] = tr("Belonging");
//    order["belonging"] = 6;
//    names["contact"] = tr("Contact");
//    order["contact"] = 7;
//    showOnlyColumns(names, order);

//    QVBoxLayout *layout = new QVBoxLayout();
//    layout->setDirection(QVBoxLayout::BottomToTop);
//    layout->setMargin(0);
//    layout->setSpacing(0);
//    layout->addItem(new QSpacerItem(0,1000, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //ui->filtersWidgetsContainer->setLayout(layout);
    //ui->filtersWidgetsContainer->setLayoutDirection(Q::BottomToTop);

//    ui->filterFieldCombobox->addItems( QStringList() << tr("Name") << tr("Surname") << tr("Patronymic") << tr("Region") << tr("Place") << tr("Belonging") << tr("Contact"));
//    ui->filterFieldCombobox->model()->sort(0);

//    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRecord()));
//    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeSelectedRecords()));
    //connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(viewRecord(QModelIndex)));

//    connect(ui->filterButton, SIGNAL(clicked()), this, SLOT(filter()));
//    connect(ui->addFilterButton, SIGNAL(clicked()), this, SLOT(addFilter()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::selectHeaders()
//{
//    TableInfo tableInfo;
//    QMap<int, QString> idNameMap = tableInfo.getIdNameMap();
//    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();

//    QStringList currSelectedHeaders;

//    for (int columnID = 0; columnID < filtersContainerWidget->getProxyModel()->columnCount(); ++columnID)
//    {
//        QString name = idNameMap.value(columnID);
//        QString alias = nameAliasMap.value(name);
//        currSelectedHeaders << alias;
//    }

//    SelectHeaderFieldsDlg dlg(currSelectedHeaders);
//    int res = dlg.exec();
//    if (res == QDialog::Accepted)
//    {
//        QStringList selectedHeaders = dlg.getSelectedHeaderFields();
//        tableViewWidget->showOnlyHeaders(selectedHeaders);
//    }
//}

//void MainWindow::addRecord()
//{
//    AddRecordDlg dlg(model, this);
//    dlg.exec();
//}

//void MainWindow::viewRecord(const QModelIndex &modelIndex)
//{
//    QModelIndex sourceIndex = sortFilterModel->mapToSource(modelIndex);
//    ViewRecordDlg dlg(model, sourceIndex.row(), this);
//    dlg.exec();
//}

//void MainWindow::removeSelectedRecords()
//{
//    QItemSelection itemSelection = ui->tableView->selectionModel()->selection();
//    QItemSelection sourceItemSelection = sortFilterModel->mapSelectionToSource(itemSelection);
//    QModelIndexList selectedIndexes = sourceItemSelection.indexes();


//    QModelIndex index;
//    foreach(index, selectedIndexes)
//    {
//        bool removed = model->removeRow(index.row());
//        if (!removed)
//        {
//            QMessageBox::critical(this,
//                                  tr("Database error."),
//                                  tr("Can not remove record. Error: ") + model->lastError().text());
//            emit select();
//            return;
//        }
//    }

//    model->submitAll();
//    model->select();
//}

//void MainWindow::addFilter()
//{
//    QString fieldName = ui->filterFieldCombobox->currentText();
//    ui->filterFieldCombobox->removeItem(ui->filterFieldCombobox->currentIndex());
//    if (ui->filterFieldCombobox->count() == 0)
//        ui->addFilterButton->setEnabled(false);

//    auto widget = new TextFilterWidget();
//    widget->setFilterName(fieldName);
//    connect(widget, SIGNAL(removed(QString)), this, SLOT(removeFilter(QString)));
//    filtersWidgets.insert(fieldName, widget);

//    ui->filtersWidgetsContainer->layout()->addWidget(widget);
//}

//void MainWindow::removeFilter(const QString filterName)
//{
//    ui->filterFieldCombobox->addItem(filterName);
//    ui->filterFieldCombobox->model()->sort(0);

//    QWidget *filterWidget = filtersWidgets.value(filterName);
//    filtersWidgets.remove(filterName);
//    delete filterWidget;

//    ui->addFilterButton->setEnabled(true);
//}

//void MainWindow::filter()
//{
//    sortFilterModel->resetRegExps();

//    foreach (QString key, filtersWidgets.keys())
//    {
//        AbstractFilterWidget *filterWidget = filtersWidgets.value(key);

//        if (key == tr("Name"))
//        {
//            sortFilterModel->setNameRegExp(filterWidget->getRegExp());
//            continue;
//        }

//        if (key == tr("Surname"))
//        {
//            sortFilterModel->setSurnameRegExp(filterWidget->getRegExp());
//            continue;
//        }

//        if (key == tr("Patronymic"))
//        {
//            sortFilterModel->setPatronymicRegExp(filterWidget->getRegExp());
//            continue;
//        }
//    }

//    sortFilterModel->invalidate();
//}

//void MainWindow::showOnlyColumns(const QMap<QString, QString> &names, const QMap<QString, int> &order)
//{
//    QTableView *view = ui->tableView;
//    QAbstractItemModel *model = view->model();

//    for (int columnID = 0; columnID < model->columnCount(); ++columnID)
//    {
//        QString columnName = model->headerData(columnID, Qt::Horizontal).toString();
//        if (names.keys().contains(columnName))
//        {
//            view->setColumnHidden(columnID, false);
//            model->setHeaderData(columnID, Qt::Horizontal, names.value(columnName));
//        }
//        else
//            view->setColumnHidden(columnID, true);
//    }

//    QHeaderView *headerView = view->horizontalHeader();
//    for (int i = 1; i <= names.size(); ++i)
//    {
//        auto name = names[order.key(i)];

//        for (int columnID = 0; columnID < model->columnCount(); ++columnID)
//        {
//            QString columnName = model->headerData(columnID, Qt::Horizontal).toString();
//            if (columnName == name)
//            {
//                auto visualIndex = headerView->visualIndex(columnID);
//                headerView->moveSection(visualIndex, i);
//                break;
//            }
//        }
//    }
//}
