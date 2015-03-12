#ifndef TEXTFILTERWIDGET_H
#define TEXTFILTERWIDGET_H

#include <QRegExp>
#include "AbstractFilterWidget.h"

namespace Ui {
class TextFilterWidget;
}

class TextFilterWidget : public AbstractFilterWidget
{
    Q_OBJECT

public:
    explicit TextFilterWidget(QWidget *parent = 0);
    ~TextFilterWidget();

    QSharedPointer<AbstractTextMatcher> getTextMatcher() override;

private:
    Ui::TextFilterWidget *ui;
};

#endif // TEXTFILTERWIDGET_H
