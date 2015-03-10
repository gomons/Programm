#include "ViewRecordDlg.h"
#include "ui_ViewRecordDlg.h"
#include "AddRecordDlg.h"

ViewRecordDlg::ViewRecordDlg(QSqlTableModel *model, int row, QWidget *parent) :
    model(model),
    row(row),
    QDialog(parent),
    ui(new Ui::ViewRecordDlg)
{
    ui->setupUi(this);

    showInfo();

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(edit()));
}

ViewRecordDlg::~ViewRecordDlg()
{
    delete ui;
}

void ViewRecordDlg::edit()
{
    AddRecordDlg dlg(model, row, this);
    dlg.exec();
    showInfo();
}

void ViewRecordDlg::showInfo()
{
    QString templ = tr("<font size='6'>%name %surname %patronymic</font> <br/>"
                       "<img src='%photo' %size> <br/>"
                       "<br/>"
                       "<font size='5'>Region</font> <br/>"
                       "%region<br/>"
                       "<br/>"
                       "<font size='5'>Place</font> <br/>"
                       "%place<br/>"
                       "<br/>"
                       "<font size='5'>Loan guarantee</font> <br/>"
                       "%loanGuarantee<br/>"
                       "<br/>"
                       "<font size='5'>Belonging</font> <br/>"
                       "%belonging<br/>"
                       "<br/>"
                       "<font size='5'>Amount</font> <br/>"
                       "%amount<br/>"
                       "<br/>"
                       "<font size='5'>Contact</font> <br/>"
                       "%contact<br/>"
                       "<br/>"
                       "<font size='5'>Activity</font> <br/>"
                       "%activity<br/>");

    int nameColIndex = 1;
    int surnameColIndex = 2;
    int patronymicColIndex = 3;
    int photoColIndex = 4;
    int activityColIndex = 5;
    int loanGuaranteeColIndex = 6;
    int belongingColIndex = 7;
    int amountColIndex = 8;
    int regionColIndex = 9;
    int placeColIndex = 10;
    int contactColIndex = 11;

    QModelIndex nameIndex = model->index(row, nameColIndex);
    QModelIndex surnameIndex = model->index(row, surnameColIndex);
    QModelIndex patronymicIndex = model->index(row, patronymicColIndex);
    QModelIndex photoIndex = model->index(row, photoColIndex);
    QModelIndex activityIndex = model->index(row, activityColIndex);
    QModelIndex loanGuaranteeIndex = model->index(row, loanGuaranteeColIndex);
    QModelIndex belongingIndex = model->index(row, belongingColIndex);
    QModelIndex amountIndex = model->index(row, amountColIndex);
    QModelIndex regionIndex = model->index(row, regionColIndex);
    QModelIndex placeIndex = model->index(row, placeColIndex);
    QModelIndex contactIndex = model->index(row, contactColIndex);

    QString name = model->data(nameIndex).toString();
    QString surname = model->data(surnameIndex).toString();
    QString patronymic = model->data(patronymicIndex).toString();
    QString photo = model->data(photoIndex).toString();
    QString activity = model->data(activityIndex).toString();
    QString loanGuarantee = model->data(loanGuaranteeIndex).toString();
    QString belonging = model->data(belongingIndex).toString();
    QString amount = model->data(amountIndex).toString();
    QString region = model->data(regionIndex).toString();
    QString place = model->data(placeIndex).toString();
    QString contact = model->data(contactIndex).toString();

    QPixmap pixmap(photo);
    QSize photo_size = pixmap.size();
    QString content;
    if (photo_size.width() > photo_size.height())
        content = templ.replace("%size", "width='150'");
    else
        content = templ.replace("%size", "height='150'");

    content = content.replace("%name", name).
                      replace("%surname", surname).
                      replace("%patronymic", patronymic).
                      replace("%photo", photo).
                      replace("%activity", activity).
                      replace("%loanGuarantee", loanGuarantee).
                      replace("%belonging", belonging).
                      replace("%amount", amount).
                      replace("%region", region).
                      replace("%place", place).
                      replace("%contact", contact);

    ui->textEdit->setText(content);
}
