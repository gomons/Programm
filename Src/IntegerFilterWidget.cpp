#include "IntegerFilterWidget.h"
#include "ui_IntegerFilterWidget.h"
#include "IntRangeTextMatcher.h"

IntegerFilterWidget::IntegerFilterWidget(QWidget *parent) :
    AbstractFilterWidget(parent),
    ui(new Ui::IntegerFilterWidget)
{
    ui->setupUi(this);
}

IntegerFilterWidget::~IntegerFilterWidget()
{
    delete ui;
}

QSharedPointer<AbstractTextMatcher> IntegerFilterWidget::getTextMatcher()
{
    int from = ui->fromEdit->text().toInt();
    int to = ui->toEdit->text().toInt();

    return QSharedPointer<IntRangeTextMatcher>::create(from, to);
}
