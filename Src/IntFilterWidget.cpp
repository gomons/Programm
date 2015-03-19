#include "IntFilterWidget.h"
#include "ui_IntFilterWidget.h"
#include <limits>
#include <QIntValidator>
#include "IntRangeTextMatcher.h"

IntegerFilterWidget::IntegerFilterWidget(QWidget *parent) :
    AbstractFilterWidget(parent),
    ui(new Ui::IntFilterWidget)
{
    ui->setupUi(this);

    int maxInt = std::numeric_limits<int>::max();

    ui->fromEdit->setValidator(new QIntValidator(0, maxInt, this));
    ui->toEdit->setValidator(new QIntValidator(0, maxInt, this));
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
