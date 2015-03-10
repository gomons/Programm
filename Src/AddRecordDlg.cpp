#include "AddRecordDlg.h"
#include "ui_AddRecordDlg.h"
#include <QCryptographicHash>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QSqlError>
#include <QSqlTableModel>

AddRecordDlg::AddRecordDlg(QSqlTableModel *model, QWidget *parent) :
    model(model),
    QDialog(parent),
    ui(new Ui::AddRecordDlg),
    row(0)
{
    ui->setupUi(this);

    noPhotoFilename = tr(":/photos/nophoto.png");
    showPhoto(noPhotoFilename);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(add()));
    connect(ui->loadPhotoButton, SIGNAL(clicked()), this, SLOT(loadPhoto()));
}

AddRecordDlg::AddRecordDlg(QSqlTableModel *model, int row, QWidget *parent) :
    model(model),
    QDialog(parent),
    ui(new Ui::AddRecordDlg),
    row(row)
{
    ui->setupUi(this);

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

    ui->nameEdit->setText(name);
    ui->surnameEdit->setText(surname);
    ui->patronymicEdit->setText(patronymic);
    showPhoto(photo);
    ui->activityEdit->setText(activity);
    ui->loanGuaranteeEdit->setText(loanGuarantee);
    ui->belongingEdit->setText(belonging);
    ui->amountEdit->setText(amount);
    ui->regionEdit->setText(region);
    ui->placeEdit->setText(place);
    ui->contactEdit->setText(contact);

    if (!photo.startsWith(":"))
        photoData = readFile(photo);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(edit()));
    connect(ui->loadPhotoButton, SIGNAL(clicked()), this, SLOT(loadPhoto()));
}

AddRecordDlg::~AddRecordDlg()
{
    delete ui;
}

void AddRecordDlg::add()
{
    row = 0;
    bool inserted = model->insertRow(row);
    if (!inserted)
    {
        QMessageBox::critical(this,
                              tr("Add record"),
                              tr("Can not insert new row. Error: ") + model->lastError().text());
        return;
    }
    edit();
}

void AddRecordDlg::edit()
{
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

    model->setData(nameIndex, ui->nameEdit->text());
    model->setData(surnameIndex, ui->surnameEdit->text());
    model->setData(patronymicIndex, ui->patronymicEdit->text());
    model->setData(photoIndex, writePhotoAndGetName());
    model->setData(activityIndex, ui->activityEdit->text());
    model->setData(loanGuaranteeIndex, ui->loanGuaranteeEdit->text());
    model->setData(belongingIndex, ui->belongingEdit->text());
    model->setData(amountIndex, ui->amountEdit->text());
    model->setData(regionIndex, ui->regionEdit->text());
    model->setData(placeIndex, ui->placeEdit->text());
    model->setData(contactIndex, ui->contactEdit->text());

    bool submitted = model->submitAll();
    if (!submitted)
    {
        QMessageBox::critical(this,
                              tr("Add record"),
                              tr("Can not submit changes. Error: ") + model->lastError().text());
        return;
    }
}

void AddRecordDlg::loadPhoto()
{
    QString initDir;
    QString caption(tr("Open Image"));
    QString filter(tr("Image Files (*.png *.jpg *.bmp)"));
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    caption,
                                                    initDir,
                                                    filter);

    photoData = readFile(fileName);

    if (photoData.isNull())
    {
        QMessageBox::critical(this,
                              tr("Add record"),
                              tr("Can not read photo"));
        showPhoto(noPhotoFilename);
    }
    else
    {
        showPhoto(photoData);
    }
}

QString AddRecordDlg::writePhotoAndGetName()
{
    if (photoData.isNull())
    {
        return noPhotoFilename;
    }
    else
    {
        QString photoName = getHash(photoData);
        QString photoFilename = tr("photos/") + photoName;

        if (QFile(photoFilename).exists())
        {
            QByteArray photoData2 = readFile(photoFilename);
            if (photoData != photoData2)
            {
                QMessageBox::warning(this,
                                     tr("Add record"),
                                     tr("Photo already exists: ") + photoFilename);
            }
            return photoFilename;
        }

        QFile photoFile(photoFilename);
        if (!photoFile.open(QFile::WriteOnly))
        {
            QMessageBox::warning(this,
                                 tr("Add record"),
                                 tr("Can not write photo"));
            return noPhotoFilename;
        }

        photoFile.write(photoData);
        return photoFilename;
    }
}

void AddRecordDlg::showPhoto(const QString &fileName)
{
    QPixmap pixmap(fileName);
    showPhoto(pixmap);
}

void AddRecordDlg::showPhoto(const QByteArray &data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data);
    showPhoto(pixmap);
}

void AddRecordDlg::showPhoto(const QPixmap &pixmap)
{
    if (pixmap.isNull())
    {
        QMessageBox::critical(this,
                              tr("Add record"),
                              tr("Invalid photo data"));
        return;
    }

    QSize pixmapSize = pixmap.size();
    QSize labelSize = ui->photoLabel->size();
    if (pixmapSize.height() > pixmapSize.width())
    {
        QPixmap newPixmap = pixmap.scaledToHeight(labelSize.height());
        ui->photoLabel->setPixmap(newPixmap);
    }
    else
    {
        QPixmap newPixmap = pixmap.scaledToWidth(labelSize.width());
        ui->photoLabel->setPixmap(newPixmap);
    }
    ui->photoLabel->adjustSize();
}

QByteArray AddRecordDlg::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this,
                              tr("Add record"),
                              tr("Can not read file ") + fileName);
        return "";
    }
    return file.readAll();
}

QString AddRecordDlg::getHash(const QByteArray &data)
{
    QCryptographicHash hash(QCryptographicHash::Sha3_256);
    hash.addData(data);
    QByteArray hashData = hash.result();
    return QString(hashData.toHex());
}
