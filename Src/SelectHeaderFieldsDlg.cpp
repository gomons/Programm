#include "SelectHeaderFieldsDlg.h"
#include "ui_SelectHeaderFieldsDlg.h"
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "BorrowerTableInfo.h"

SelectHeaderFieldsDlg::SelectHeaderFieldsDlg(const QStringList &selected, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectHeaderFieldsDlg)
{
    ui->setupUi(this);

    auto *layout = new QVBoxLayout(this);
    setLayout(layout);

    auto checkboxLayout = new QVBoxLayout();
    layout->addLayout(checkboxLayout);

    BorrowerTableInfo tableInfo;
    QStringList aliases = tableInfo.getAliases();

    foreach (QString alias, aliases)
    {
        auto checkbox = new QCheckBox();
        checkbox->setText(alias);

        if (selected.contains(alias))
            checkbox->setChecked(true);
        else
            checkbox->setChecked(false);

        checkboxLayout->addWidget(checkbox);
        checkboxes.append(checkbox);
    }

    auto buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

SelectHeaderFieldsDlg::~SelectHeaderFieldsDlg()
{
    delete ui;
}

QStringList SelectHeaderFieldsDlg::getSelectedHeaderFields()
{
    QStringList headers;

    foreach (QCheckBox *checkbox, checkboxes)
        if (checkbox->isChecked())
            headers << checkbox->text();

    return headers;
}
