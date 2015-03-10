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

    sortFilterModel = new SortFilterProxyModel(this);
    sortFilterModel->setSourceModel(model);

    ui->tableView->setModel(sortFilterModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showOnlyColumns(QStringList() << "name" << "surname" << "patronymic" << "region" << "place" << "belonging" << "contact");

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeSelectedRecords()));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(viewRecord(QModelIndex)));
    connect(ui->filterButton, SIGNAL(clicked()), this, SLOT(Filter()));
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

void MainWindow::Filter()
{
    sortFilterModel->resetRegExps();

    sortFilterModel->setNameRegExp(QRegExp(ui->nameEdit->text(), Qt::CaseSensitive, QRegExp::Wildcard));
    sortFilterModel->setSurnameRegExp(QRegExp(ui->surnameEdit->text(), Qt::CaseSensitive, QRegExp::Wildcard));
    sortFilterModel->setPatronymicRegExp(QRegExp(ui->patronymicEdit->text(), Qt::CaseSensitive, QRegExp::Wildcard));

    sortFilterModel->invalidate();
}

void MainWindow::showOnlyColumns(const QStringList &columns)
{
    int columnCount = sortFilterModel->columnCount();

    for (int columnID = 0; columnID < columnCount; ++columnID)
    {
        QString columnName = model->headerData(columnID, Qt::Horizontal).toString();
        if (columns.contains(columnName))
            ui->tableView->setColumnHidden(columnID, false);
        else
            ui->tableView->setColumnHidden(columnID, true);
    }
}
