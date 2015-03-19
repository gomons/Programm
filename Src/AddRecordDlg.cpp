#include "AddRecordDlg.h"
#include "ui_AddRecordDlg.h"
#include <QBuffer>
#include <QCryptographicHash>
#include <QDataWidgetMapper>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlRelationalTableModel>
#include "BorrowerTableInfo.h"

AddRecordDlg::AddRecordDlg(QSqlRelationalTableModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecordDlg),
    model(model)
{
    ui->setupUi(this);

    prepareDlg();
    model->insertRow(0);
    mapper->setCurrentIndex(0);

    removePhoto();
}

AddRecordDlg::AddRecordDlg(QSqlRelationalTableModel *model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecordDlg),
    model(model)
{
    ui->setupUi(this);

    prepareDlg();
    mapper->setCurrentIndex(row);

    showPhoto();
    oldPhotoFilepath = ui->photoEdit->text();
}

AddRecordDlg::~AddRecordDlg()
{
}

void AddRecordDlg::accepted()
{
    if (ui->photoEdit->text().startsWith(":"))
        return;

    if (photoPixmap.isNull())
    {
        removePhoto();
        return;
    }

    QByteArray photoData;
    QBuffer photoBuffer(&photoData);
    photoBuffer.open(QIODevice::WriteOnly);
    photoPixmap.save(&photoBuffer, "PNG");

    QCryptographicHash hash(QCryptographicHash::Sha3_256);
    hash.addData(photoData);
    QByteArray hashData = hash.result();
    QString hashString(hashData.toHex());
    QString currentTime = QString::number(QDateTime::currentDateTime().toTime_t());
    QString photoFilepath = "photos/" + hashString + "." + currentTime;
    ui->photoEdit->setText(photoFilepath);

    if (!oldPhotoFilepath.isEmpty() && !oldPhotoFilepath.startsWith(":"))
        QFile::remove(oldPhotoFilepath);

    if (QFile(photoFilepath).exists())
    {
        QFile photoFile(photoFilepath);
        if (!photoFile.open(QFile::ReadOnly))
        {
            QMessageBox::critical(this, tr("Add record"), tr("Can not read file: ") + photoFilepath);
            removePhoto();
            return;
        }
        QByteArray photoData2 = photoFile.readAll();
        if (photoData != photoData2)
        {
            QMessageBox::warning(this, tr("Add record"), tr("Photo already exists: ") + photoFilepath);
            removePhoto();
            return;
        }
        else
        {
            return;
        }
    }

    QFile photoFile(photoFilepath);
    if (!photoFile.open(QFile::WriteOnly))
    {
        QMessageBox::warning(this, tr("Add record"), tr("Can not write photo"));
        removePhoto();
        return;
    }
    photoFile.write(photoData);
}

void AddRecordDlg::removePhoto()
{
    photoPixmap = QPixmap();
    ui->photoEdit->setText(":/img/nophoto.png");
    showPhoto();
}

void AddRecordDlg::loadPhoto()
{
    QString initDir;
    QString caption(tr("Open Image"));
    QString filter(tr("Image Files (*.png *.jpg *.bmp)"));
    QString fileName = QFileDialog::getOpenFileName(this, caption, initDir, filter);

    if (fileName.isEmpty())
        return;

    ui->photoEdit->setText(fileName);
    bool showed = showPhoto();
    if (!showed)
        removePhoto();
}

void AddRecordDlg::prepareDlg()
{
    BorrowerTableInfo tableInfo;

    QSqlTableModel *regionModel = model->relationModel(tableInfo.regionFieldID);
    ui->regionComboBox->setModel(regionModel);
    ui->regionComboBox->setModelColumn(regionModel->fieldIndex("name"));

    QSqlTableModel *belongingModel = model->relationModel(tableInfo.belongingFieldID);
    ui->belonginComboBox->setModel(belongingModel);
    ui->belonginComboBox->setModelColumn(belongingModel->fieldIndex("description"));

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setModel(model);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));

    mapper->addMapping(ui->nameEdit, tableInfo.nameFieldID);
    mapper->addMapping(ui->surnameEdit, tableInfo.surnameFieldID);
    mapper->addMapping(ui->patronymicEdit, tableInfo.patronymicFieldID);
    mapper->addMapping(ui->photoEdit, tableInfo.photoFieldID);
    mapper->addMapping(ui->activityEdit, tableInfo.activityFieldID);
    mapper->addMapping(ui->loanGuaranteeEdit, tableInfo.loanGuaranteeFieldID);
    mapper->addMapping(ui->belonginComboBox, tableInfo.belongingFieldID);
    mapper->addMapping(ui->amountEdit, tableInfo.amountFieldID);
    mapper->addMapping(ui->regionComboBox, tableInfo.regionFieldID);
    mapper->addMapping(ui->placeEdit, tableInfo.placeFieldID);
    mapper->addMapping(ui->contactEdit, tableInfo.contactFieldID);

    ui->photoEdit->setVisible(false);
    ui->amountEdit->setValidator(new QIntValidator(0, 999999999, this));
    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(this, SIGNAL(accepted()), mapper, SLOT(submit()));
    connect(this, SIGNAL(accepted()), model, SLOT(submitAll()));
    connect(this, SIGNAL(rejected()), model, SLOT(revertAll()));

    connect(ui->removePhotoButton, SIGNAL(clicked()), this, SLOT(removePhoto()));
    connect(ui->loadPhotoButton, SIGNAL(clicked()), this, SLOT(loadPhoto()));
}

bool AddRecordDlg::showPhoto()
{
    photoPixmap = QPixmap(ui->photoEdit->text());
    QPixmap pixmap = photoPixmap;

    if (pixmap.isNull())
    {
        QMessageBox::critical(this, tr("Add record"), tr("Invalid photo data"));
        return false;
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

    return true;
}
