#include "TextFilterWidget.h"
#include "ui_TextFilterWidget.h"
#include "RegExpTextMatcher.h"

TextFilterWidget::TextFilterWidget(QWidget *parent) :
    AbstractFilterWidget(parent),
    ui(new Ui::TextFilterWidget)
{
    ui->setupUi(this);

    ui->serchTypeCombobox->addItem(tr("Regular expression"), QRegExp::RegExp);
    ui->serchTypeCombobox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    ui->serchTypeCombobox->addItem(tr("FixedString"), QRegExp::FixedString);
}

TextFilterWidget::~TextFilterWidget()
{
    emit filterRemoved(getFilterName());
    delete ui;
}

QSharedPointer<AbstractTextMatcher> TextFilterWidget::getTextMatcher()
{
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    if (ui->caseSensitiveCheckBox->isChecked())
        cs = Qt::CaseSensitive;
    QRegExp::PatternSyntax patter = static_cast<QRegExp::PatternSyntax>(ui->serchTypeCombobox->currentData().toInt());
    QRegExp regExp(ui->textEdit->text(), cs, patter);

    return QSharedPointer<RegExpTextMatcher>::create(regExp);
}
