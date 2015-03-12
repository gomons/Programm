#include "FilterDlg.h"
#include "ui_FilterDlg.h"
#include <QVBoxLayout>
#include "FiltersContainerWidget.h"

FilterDlg::FilterDlg(SortFilterProxyModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDlg)
{
    ui->setupUi(this);

    filtersContainerWidget = new FiltersContainerWidget(model, this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(filtersContainerWidget);
    layout->setSpacing(0);
    layout->setMargin(0);

    setLayout(layout);

    connect(filtersContainerWidget, SIGNAL(beforeFilter()), this, SIGNAL(beforeFilter()));
    connect(filtersContainerWidget, SIGNAL(afterFilter()), this, SIGNAL(afterFilter()));
}

FilterDlg::~FilterDlg()
{
    delete ui;
}
