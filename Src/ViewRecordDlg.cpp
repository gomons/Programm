#include "ViewRecordDlg.h"
#include "ui_ViewRecordDlg.h"
#include <QFile>
#include <QPrintDialog>
#include <QPrinter>
#include <QSqlRelationalTableModel>
#include <QTextStream>
#include <QDebug>
#include "BorrowerTableInfo.h"
#include "ColorMap.h"

ViewRecordDlg::ViewRecordDlg(QSqlRelationalTableModel *model, int row, QWidget *parent) :
    model(model),
    row(row),
    QDialog(parent),
    ui(new Ui::ViewRecordDlg)
{
    ui->setupUi(this);

    showInfo();

    connect(ui->okButton,       SIGNAL(clicked()),  this,   SLOT(accept()));
    connect(ui->editButton,     SIGNAL(clicked()),  this,   SLOT(edit()));
    connect(ui->printButton,    SIGNAL(clicked()),  this,   SLOT(print()));
}

ViewRecordDlg::~ViewRecordDlg()
{
    delete ui;
}

void ViewRecordDlg::edit()
{
    emit edit(row);
    showInfo();
}

void ViewRecordDlg::print()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    int res = dialog.exec();
    if (res == QDialog::Accepted)
        ui->textEdit->document()->print(&printer);
}

void ViewRecordDlg::showInfo()
{
    QString reportTempl;

    if (QFile::exists("report"))
    {
        QFile file("report");
        file.open(QFile::ReadOnly);
        QTextStream in(&file);
        in.setCodec("UTF-8");
        reportTempl = in.readAll();
    }
    else
    {
        reportTempl = tr("<font size='6' color=%color>%name %surname %patronymic</font> <br/>"
                         "<img src='%photo' %size> <br/>"
                         "<br/>"
                         "<font size='5'>Comment</font> <br/>"
                         "%comment<br/>"
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
    }

    BorrowerTableInfo tableInfo;

    QModelIndex nameIndex = model->index(row, tableInfo.nameFieldID);
    QModelIndex surnameIndex = model->index(row, tableInfo.surnameFieldID);
    QModelIndex patronymicIndex = model->index(row, tableInfo.patronymicFieldID);
    QModelIndex photoIndex = model->index(row, tableInfo.photoFieldID);
    QModelIndex activityIndex = model->index(row, tableInfo.activityFieldID);
    QModelIndex loanGuaranteeIndex = model->index(row, tableInfo.loanGuaranteeFieldID);
    QModelIndex belongingIndex = model->index(row, tableInfo.belongingFieldID);
    QModelIndex amountIndex = model->index(row, tableInfo.amountFieldID);
    QModelIndex regionIndex = model->index(row, tableInfo.regionFieldID);
    QModelIndex placeIndex = model->index(row, tableInfo.placeFieldID);
    QModelIndex contactIndex = model->index(row, tableInfo.contactFieldID);
    QModelIndex colorIndex = model->index(row, tableInfo.colorIdFieldID);
    QModelIndex commentIndex = model->index(row, tableInfo.commentFieldID);

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
    QString comment = model->data(commentIndex).toString();

    QString colorName = model->data(colorIndex).toString();
    ColorMap colorMap;
    QString color = colorMap.getColor(colorName).name();
    if (color.toLower() == "#ffffff")
    {
        color = "#000000";
    }
    qDebug() << colorName << " "<<  color;

    QPixmap pixmap(photo);
    QSize photo_size = pixmap.size();
    QString content;
    if (photo_size.width() > photo_size.height())
        content = reportTempl.replace("%size", "width='150'");
    else
        content = reportTempl.replace("%size", "height='150'");

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
                      replace("%contact", contact).
                      replace("%color", color).
                      replace("%comment", comment);

    ui->textEdit->setText(content);
}
