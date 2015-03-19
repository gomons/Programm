#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRelationalTableModel>
#include "AboutDlg.h"
#include "AddRecordDlg.h"
#include "FilterDlg.h"
#include "SelectHeaderFieldsDlg.h"
#include "SortFilterProxyModel.h"
#include "BorrowerTableInfo.h"
#include "TableViewWidget.h"
#include "ViewRecordDlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BorrowerTableInfo tableInfo;

    model = new QSqlRelationalTableModel(this);
    model->setTable(tableInfo.tableName);
    model->setRelation(tableInfo.regionFieldID, QSqlRelation("region", "id", "name"));
    model->setRelation(tableInfo.belongingFieldID, QSqlRelation("belonging", "id", "description"));
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    model->select();

    proxyModel = new SortFilterProxyModel(this);
    proxyModel->setSourceModel(model);

    QStringList showedHeaders;
    showedHeaders << tableInfo.nameFieldAlias
                  << tableInfo.surnameFieldAlias
                  << tableInfo.patronymicFieldAlias
                  << tableInfo.regionFieldAlias
                  << tableInfo.placeFieldAlias
                  << tableInfo.belongingFieldAlias
                  << tableInfo.contactFieldAlias;
    tableViewWidget = new TableViewWidget(model, proxyModel, this);
    tableViewWidget->showOnlyHeaders(showedHeaders);

    QVBoxLayout *tableGroupBoxLayout = new QVBoxLayout();
    tableGroupBoxLayout->setSpacing(0);
    tableGroupBoxLayout->setMargin(0);
    ui->tableGroupBox->setLayout(tableGroupBoxLayout);
    tableGroupBoxLayout->addWidget(tableViewWidget);

    filterDlg = new FilterDlg(proxyModel, this);

    connect(ui->removeButton,           SIGNAL(clicked()),              this,   SLOT(removeRecords()));
    connect(ui->addButton,              SIGNAL(clicked()),              this,   SLOT(showAddRecordDlg()));
    connect(tableViewWidget,            SIGNAL(rowDoubleClicked(int)),  this,   SLOT(showViewRecordDlg(int)));
    connect(ui->selectHeadersAction,    SIGNAL(triggered()),            this,   SLOT(showSelectHeaderFieldsDlg()));
    connect(ui->aboutAction,            SIGNAL(triggered()),            this,   SLOT(showAboutDlg()));
    connect(ui->exitAction,             SIGNAL(triggered()),            this,   SLOT(close()));
    connect(ui->filterAction,           SIGNAL(triggered()),            this,   SLOT(showFilterDlg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::removeRecords()
{
    QList<int> rows = tableViewWidget->getSelectedRows();

    if (rows.empty())
        return;

    QMessageBox::StandardButton res = QMessageBox::question(this,
                                                            tr("Removing records."),
                                                            tr("Do you realy want delete ") + QString::number(rows.size()) + tr(" records?"));
    if (res != QMessageBox::Yes)
        return;

    BorrowerTableInfo tableInfo;

    foreach (int row, rows)
    {
        QModelIndex index = model->index(row, tableInfo.photoFieldID);
        QString photoFilepath = model->data(index).toString();
        if (!photoFilepath.startsWith(":"))
            QFile::remove(photoFilepath);

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

void MainWindow::showAddRecordDlg()
{
    AddRecordDlg dlg(model, this);
    int res = dlg.exec();
    if (res == QDialog::Accepted)
        model->select();
}

void MainWindow::showEditRecordDlg(int row)
{
    AddRecordDlg dlg(model, row, this);
    int res = dlg.exec();
    if (res == QDialog::Accepted)
        model->select();
}

void MainWindow::showViewRecordDlg(int row)
{
    ViewRecordDlg dlg(model, row, this);
    connect(&dlg, SIGNAL(edit(int)), this, SLOT(showEditRecordDlg(int)));
    dlg.exec();
}

void MainWindow::showFilterDlg()
{
    QStringList shownHeaders = tableViewWidget->getShownHeaders();
    int res = filterDlg->exec();
    if (res == QDialog::Accepted)
        tableViewWidget->showOnlyHeaders(shownHeaders);
}

void MainWindow::showSelectHeaderFieldsDlg()
{
    SelectHeaderFieldsDlg dlg(tableViewWidget->getShownHeaders(), this);
    int res = dlg.exec();
    if (res == QDialog::Accepted)
    {
        QStringList selectedHeaders = dlg.getSelectedHeaderFields();
        tableViewWidget->showOnlyHeaders(selectedHeaders);
    }
}

void MainWindow::showAboutDlg()
{
    AboutDlg dlg(this);
    dlg.exec();
}
