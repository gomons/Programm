#include "TableViewWidget.h"
#include "ui_TableViewWidget.h"
#include "TableInfo.h"
#include "SelectHeaderFieldsDlg.h"

TableViewWidget::TableViewWidget(QAbstractItemModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewWidget),
    model(model)
{
    ui->setupUi(this);

    RenameModelHeader();

    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSectionsMovable(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
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

void TableViewWidget::RenameModelHeader()
{
    TableInfo tableInfo;
    QMap<int, QString> idNameMap = tableInfo.getIdNameMap();
    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();

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

void TableViewWidget::changeShownHeaders()
{
    TableInfo tableInfo;
    QMap<int, QString> idNameMap = tableInfo.getIdNameMap();
    QMap<QString, QString> nameAliasMap = tableInfo.getNameAliasMap();

    QStringList shownHeaders;

    for (int columnID = 0; columnID < model->columnCount(); ++columnID)
    {
        if (!ui->tableView->isColumnHidden(columnID))
        {
            QString name = idNameMap.value(columnID);
            QString alias = nameAliasMap.value(name);
            shownHeaders << alias;
        }
    }

    SelectHeaderFieldsDlg dlg(shownHeaders);
    int res = dlg.exec();
    if (res == QDialog::Accepted)
    {
        QStringList newShownHeaders = dlg.getSelectedHeaderFields();
        showOnlyHeaders(newShownHeaders);
    }
}
