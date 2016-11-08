#include "TableViewWidget.h"
#include "ui_TableViewWidget.h"
#include "SortFilterProxyModel.h"
#include "BorrowerTableInfo.h"

TableViewWidget::TableViewWidget(QSqlRelationalTableModel *model,
                                 SortFilterProxyModel *proxyModel,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewWidget),
    model(model),
    proxyModel(proxyModel)
{
    ui->setupUi(this);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSectionsMovable(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //ui->tableView->setItemDelegate

    renameHeaders();

    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(rowDoubleClicked(QModelIndex)));
}

TableViewWidget::~TableViewWidget()
{
    delete ui;
}

void TableViewWidget::retranslate()
{
    ui->retranslateUi(this);
    renameHeaders();
}

void TableViewWidget::showOnlyHeaders(const QStringList& names)
{
    BorrowerTableInfo tableInfo;
    QMap<int, QString> idNameMap = tableInfo.getIdNameMap();
    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();

    QAbstractItemModel *model = ui->tableView->model();

    for (int columnID = 0; columnID < model->columnCount(); ++columnID)
    {
        QString name = idNameMap.value(columnID);
        QString alias = nameAliasMap.value(name);

        if (names.contains(alias))
            ui->tableView->setColumnHidden(columnID, false);
        else
            ui->tableView->setColumnHidden(columnID, true);
    }
}

QStringList TableViewWidget::getShownHeaders()
{
    BorrowerTableInfo tableInfo;
    QMap<int, QString> idNameMap = tableInfo.getIdNameMap();
    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();

    QStringList shownHeaders;
    QAbstractItemModel *model = ui->tableView->model();

    for (int columnID = 0; columnID < model->columnCount(); ++columnID)
    {
        if (!ui->tableView->isColumnHidden(columnID))
        {
            QString name = idNameMap.value(columnID);
            QString alias = nameAliasMap.value(name);
            shownHeaders << alias;
        }
    }

    return shownHeaders;
}

QList<int> TableViewWidget::getSelectedRows()
{
    QItemSelection itemSelection = ui->tableView->selectionModel()->selection();
    QItemSelection sourceItemSelection = proxyModel->mapSelectionToSource(itemSelection);
    QModelIndexList selectedIndexes = sourceItemSelection.indexes();

    QSet<int> rows;
    foreach (QModelIndex index, selectedIndexes)
        rows << index.row();

    return rows.toList();
}

void TableViewWidget::rowDoubleClicked(QModelIndex index)
{
    QModelIndex sourceIndex = proxyModel->mapToSource(index);
    emit rowDoubleClicked(sourceIndex.row());
}

void TableViewWidget::renameHeaders()
{
    BorrowerTableInfo tableInfo;
    QMap<int, QString> idNameMap = tableInfo.getIdNameMap();
    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();

    QAbstractItemModel *model = ui->tableView->model();

    for (int columnID = 0; columnID < model->columnCount(); ++columnID)
    {
        if (idNameMap.contains(columnID))
        {
            QString name = idNameMap.value(columnID);
            QString alias = nameAliasMap.value(name);
            model->setHeaderData(columnID, Qt::Horizontal, alias);
        }
    }
}

QTableView *TableViewWidget::tableView() { return ui->tableView; }



