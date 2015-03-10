#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "AddRecordDlg.h"
#include "ViewRecordDlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("borrower");
    model->select();

    sortFilterModel = new QSortFilterProxyModel(this);
    sortFilterModel->setSourceModel(model);

    ui->tableView->setModel(sortFilterModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showOnlyColumns(QStringList() << "name" << "surname" << "patronymic" << "region" << "place" << "belonging" << "contact");

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeSelectedRecords()));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(viewRecord(QModelIndex)));
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

void MainWindow::viewRecord(const QModelIndex &modelIndex)
{
    QModelIndex sourceIndex = sortFilterModel->mapToSource(modelIndex);
    ViewRecordDlg dlg(model, sourceIndex.row(), this);
    dlg.exec();
}

void MainWindow::removeSelectedRecords()
{
    QItemSelection itemSelection = ui->tableView->selectionModel()->selection();
    QItemSelection sourceItemSelection = sortFilterModel->mapSelectionToSource(itemSelection);
    QModelIndexList selectedIndexes = sourceItemSelection.indexes();


    QModelIndex index;
    foreach(index, selectedIndexes)
    {
        bool removed = model->removeRow(index.row());
        if (!removed)
        {
            QMessageBox::critical(this,
                                  tr("Database error."),
                                  tr("Can not remove record. Error: ") + model->lastError().text());
            emit select();
            return;
        }
    }

    model->submitAll();
    model->select();
}

void MainWindow::showOnlyColumns(const QStringList &columns)
{
    QAbstractItemModel *model = ui->tableView->model();
    int columnCount = model->columnCount();

    for (int columnID = 0; columnID < columnCount; ++columnID)
    {
        QString columnName = model->headerData(columnID, Qt::Horizontal).toString();
        if (columns.contains(columnName))
            ui->tableView->setColumnHidden(columnID, false);
        else
            ui->tableView->setColumnHidden(columnID, true);
    }
}
