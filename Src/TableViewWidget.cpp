#include "TableViewWidget.h"
#include "ui_TableViewWidget.h"
#include "SelectHeaderFieldsDlg.h"
#include "SortFilterProxyModel.h"
#include "TableInfo.h"

TableViewWidget::TableViewWidget(SortFilterProxyModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewWidget),
    model(model)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSectionsMovable(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    renameHeaders();
}

TableViewWidget::~TableViewWidget()
{
    delete ui;
}

void TableViewWidget::showOnlyHeaders(const QStringList& names)
{
    TableInfo tableInfo;
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

QList<int> TableViewWidget::getSelectedRows()
{
    QItemSelection itemSelection = ui->tableView->selectionModel()->selection();
    QItemSelection sourceItemSelection = model->mapSelectionToSource(itemSelection);
    QModelIndexList selectedIndexes = sourceItemSelection.indexes();

    QList<int> rows;
    foreach (QModelIndex index, selectedIndexes)
        rows << index.row();

    return rows;
}

void TableViewWidget::changeShownHeaders()
{
    QStringList shownHeaders = getShownHeaders();

    SelectHeaderFieldsDlg dlg(shownHeaders);
    int res = dlg.exec();
    if (res == QDialog::Accepted)
    {
        QStringList newShownHeaders = dlg.getSelectedHeaderFields();
        showOnlyHeaders(newShownHeaders);
    }
}

void TableViewWidget::saveShownHeaders()
{
    savedShownHeaders = getShownHeaders();
}

void TableViewWidget::restoreShownHeaders()
{
    showOnlyHeaders(savedShownHeaders);
}

void TableViewWidget::renameHeaders()
{
    TableInfo tableInfo;
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

QStringList TableViewWidget::getShownHeaders()
{
    TableInfo tableInfo;
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


