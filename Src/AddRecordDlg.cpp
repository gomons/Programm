#include "AddRecordDlg.h"
#include "ui_AddRecordDlg.h"
#include <limits>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include "TableInfo.h"

AddRecordDlg::AddRecordDlg(QSqlTableModel *model, QWidget *parent) :
    model(model),
    QDialog(parent),
    ui(new Ui::AddRecordDlg),
    row(-1),
    noPhotoFilename(":/photos/nophoto.png")
{
    ui->setupUi(this);
    showPhoto(noPhotoFilename);
    prepare();
}

AddRecordDlg::AddRecordDlg(QSqlTableModel *model, int row, QWidget *parent) :
    model(model),
    QDialog(parent),
    ui(new Ui::AddRecordDlg),
    row(row),
    noPhotoFilename(":/photos/nophoto.png")
{
    ui->setupUi(this);

    TableInfo tableInfo;

    ui->nameEdit->setText(getTableData(row, tableInfo.nameFieldID));
    ui->surnameEdit->setText(getTableData(row, tableInfo.surnameFieldID));
    ui->patronymicEdit->setText(getTableData(row, tableInfo.patronymicFieldID));
    ui->activityEdit->setText(getTableData(row, tableInfo.activityFieldID));
    ui->loanGuaranteeEdit->setText(getTableData(row, tableInfo.loanGuaranteeFieldID));
    ui->belongingEdit->setText(getTableData(row, tableInfo.belongingFieldID));
    ui->amountEdit->setText(getTableData(row, tableInfo.amountFieldID));
    ui->regionEdit->setText(getTableData(row, tableInfo.regionFieldID));
    ui->placeEdit->setText(getTableData(row, tableInfo.placeFieldID));
    ui->contactEdit->setText(getTableData(row, tableInfo.contactFieldID));

    QString photoPath = getTableData(row, tableInfo.photoFieldID);
    showPhoto(photoPath);
    if (!photoPath.startsWith(":"))
        photoData = readFile(photoPath);

    prepare();
}

AddRecordDlg::~AddRecordDlg()
{
    delete ui;
}

void AddRecordDlg::edit()
{
    if (row < 0)
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
    }

    TableInfo tableInfo;

    setTableData(row, tableInfo.nameFieldID, ui->nameEdit->text());
    setTableData(row, tableInfo.surnameFieldID, ui->surnameEdit->text());
    setTableData(row, tableInfo.patronymicFieldID, ui->patronymicEdit->text());
    setTableData(row, tableInfo.photoFieldID, writePhotoAndGetName());
    setTableData(row, tableInfo.activityFieldID, ui->activityEdit->text());
    setTableData(row, tableInfo.loanGuaranteeFieldID, ui->loanGuaranteeEdit->text());
    setTableData(row, tableInfo.belongingFieldID, ui->belongingEdit->text());
    setTableData(row, tableInfo.amountFieldID, ui->amountEdit->text());
    setTableData(row, tableInfo.regionFieldID, ui->regionEdit->text());
    setTableData(row, tableInfo.placeFieldID, ui->placeEdit->text());
    setTableData(row, tableInfo.contactFieldID, ui->contactEdit->text());

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
    QString fileName = QFileDialog::getOpenFileName(this, caption, initDir, filter);

    if (fileName.isEmpty())
        return;

    photoData = readFile(fileName);
    if (photoData.isNull())
    {
        QMessageBox::critical(this, tr("Add record"), tr("Can not read photo"));
        showPhoto(noPhotoFilename);
        return;
    }

    showPhoto(photoData);
}

void AddRecordDlg::removePhoto()
{
    photoData.clear();
    showPhoto(noPhotoFilename);
}

void AddRecordDlg::prepare()
{
    int maxInt = std::numeric_limits<int>::max();
    ui->amountEdit->setValidator(new QIntValidator(0, maxInt, this));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(edit()));
    connect(ui->loadPhotoButton, SIGNAL(clicked()), this, SLOT(loadPhoto()));
    connect(ui->removePhotoButton, SIGNAL(clicked()), this, SLOT(removePhoto()));
}

QString AddRecordDlg::getTableData(int row, int id)
{
    QModelIndex index = model->index(row, id);
    return model->data(index).toString();
}

void AddRecordDlg::setTableData(int row, int id, const QString &data)
{
    QModelIndex index = model->index(row, id);
    model->setData(index, data.trimmed());
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
                QMessageBox::warning(this, tr("Add record"), tr("Photo already exists: ") + photoFilename);
            }
            return photoFilename;
        }

        QFile photoFile(photoFilename);
        if (!photoFile.open(QFile::WriteOnly))
        {
            QMessageBox::warning(this, tr("Add record"), tr("Can not write photo"));
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
        QMessageBox::critical(this, tr("Add record"), tr("Invalid photo data"));
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
        QMessageBox::critical(this, tr("Add record"), tr("Can not read file ") + fileName);
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
