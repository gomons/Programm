#ifndef INTEGERFILTERWIDGET_H
#define INTEGERFILTERWIDGET_H

#include <QWidget>
#include "AbstractFilterWidget.h"

namespace Ui {
class IntFilterWidget;
}

class IntegerFilterWidget : public AbstractFilterWidget
{
    Q_OBJECT

public:
    explicit IntegerFilterWidget(QWidget *parent = 0);
    ~IntegerFilterWidget();

    QSharedPointer<AbstractTextMatcher> getTextMatcher() override;

private:
    Ui::IntFilterWidget *ui;
};

#endif // INTEGERFILTERWIDGET_H
