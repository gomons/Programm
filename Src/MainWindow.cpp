#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include "AboutDlg.h"
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
    connect(ui->filterAction, SIGNAL(triggered()), this, SLOT(showFilters()));
    connect(ui->exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addRecord()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeRecord()));

    connect(filterDlg, SIGNAL(beforeFilter()), tableViewWidget, SLOT(saveShownHeaders()));
    connect(filterDlg, SIGNAL(afterFilter()), tableViewWidget, SLOT(restoreShownHeaders()));

//    {
//        QActionGroup* group = new QActionGroup(this);
//        group->addAction(ui->englishAction);
//        group->addAction(ui->russianAction);

//        if (ui->englishAction->isChecked())
//            translateToEnglish();
//        else if (ui->russianAction->isChecked())
//            transletToRussion();

//        connect(ui->englishAction, SIGNAL(triggered()), this, SLOT(translateToEnglish()));
//        connect(ui->russianAction, SIGNAL(triggered()), this, SLOT(transletToRussion()));
//    }
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

void MainWindow::showAbout()
{
    AboutDlg dlg(this);
    dlg.exec();
}

//void MainWindow::transletToRussion()
//{
//    QTranslator qtTranslator;
//    qtTranslator.load("qt_" + QLocale::system().name(),
//            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    app.installTranslator(&qtTranslator);

//    QTranslator myappTranslator;
//    myappTranslator.load("myapp_" + QLocale::system().name());
//    app.installTranslator(&myappTranslator);
//}

//#include <QLibraryInfo>
//#include <QTranslator>
//#include <QFile>
//void MainWindow::translateToEnglish()
//{
//    QTranslator qtTranslator;

//    QFile file(":/translate/qt_ru.qm");
//    QByteArray translateData = file.readAll();

//    bool loaded = qtTranslator.load("qt_ru", "c:\\Users\\Sergey\\Projects\\Home\\Programm\\Src\\");
//    //qtTranslator
//    QApplication::instance()->installTranslator(&qtTranslator);

//    auto t = tr("c:\\Users\\Sergey\\Projects\\Home\\Programm\\Src\\");
//    auto tt = QLibraryInfo::location(QLibraryInfo::TranslationsPath);

//    QTranslator qtTranslator;
//    auto res = qtTranslator.load("qt_ru", tt);
//    QApplication::instance()->installTranslator(&qtTranslator);
    //this->tr

//    QTranslator myappTranslator;
//    myappTranslator.load("myapp_" + QLocale::system().name());
//    app.installTranslator(&myappTranslator);
//}
