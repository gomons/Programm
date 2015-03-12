#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include "AddRecordDlg.h"
#include "FilterDlg.h"
#include "FiltersContainerWidget.h"
#include "SortFilterProxyModel.h"
#include "TableInfo.h"
#include "TableViewWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TableInfo tableInfo;

    model = new QSqlTableModel(this);
    model->setTable(tableInfo.tableName);
    model->select();

    proxyModel = new SortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    filterDlg = new FilterDlg(proxyModel, this);

    tableViewWidget = new TableViewWidget(model, proxyModel, this);
    tableViewWidget->showOnlyHeaders(QStringList() << tableInfo.nameFieldAlias
                                                   << tableInfo.surnameFieldAlias
                                                   << tableInfo.patronymicFieldAlias
                                                   << tableInfo.regionFieldAlias
                                                   << tableInfo.placeFieldAlias
                                                   << tableInfo.belongingFieldAlias
                                                   << tableInfo.contactFieldAlias);

    QVBoxLayout *tableGroupBoxLayout = new QVBoxLayout();
    tableGroupBoxLayout->setSpacing(0);
    tableGroupBoxLayout->setMargin(0);
    ui->tableGroupBox->setLayout(tableGroupBoxLayout);
    tableGroupBoxLayout->addWidget(tableViewWidget);

    connect(ui->selectHeadersAction, SIGNAL(triggered()), tableViewWidget, SLOT(changeShownHeaders()));
    connect(ui->filterAction, SIGNAL(triggered()), this, SLOT(showFilters()));;

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeRecord()));

    connect(filterDlg, SIGNAL(beforeFilter()), tableViewWidget, SLOT(saveShownHeaders()));
    connect(filterDlg, SIGNAL(afterFilter()), tableViewWidget, SLOT(restoreShownHeaders()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRecord()
{
    AddRecordDlg dlg(model, this);
    dlg.exec();
}

void MainWindow::removeRecord()
{
    QList<int> rows = tableViewWidget->getSelectedRows();

    if (rows.empty())
        return;

    QMessageBox::StandardButton res = QMessageBox::question(this,
                                                            tr("Removing records."),
                                                            tr("Do you realy want delete ") + QString::number(rows.size()) + tr(" records?"));
    if (res != QMessageBox::Yes)
        return;

    foreach (int row, rows)
    {
        bool removed = model->removeRow(row);
        if (!removed)
        {
            QMessageBox::critical(this,
                                  tr("Database error."),
                                  tr("Can not remove record. Error: ") + model->lastError().text());
            model->revertAll();
            return;
        }
    }

    model->submitAll();
    model->select();
}

void MainWindow::showFilters()
{
    filterDlg->show();
}

//void MainWindow::viewRecord(const QModelIndex &modelIndex)
//{
//    QModelIndex sourceIndex = sortFilterModel->mapToSource(modelIndex);
//    ViewRecordDlg dlg(model, sourceIndex.row(), this);
//    dlg.exec();
//}

