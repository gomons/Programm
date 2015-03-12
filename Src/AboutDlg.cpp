#include "AboutDlg.h"
#include "ui_AboutDlg.h"
#include <QPixmap>

AboutDlg::AboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDlg)
{
    ui->setupUi(this);

//    QPixmap pixmap(":/img/splash.png");
//    QPixmap newPixmap = pixmap.scaledToWidth(size().width());
//    ui->logoLabel->setPixmap(newPixmap);
}

AboutDlg::~AboutDlg()
{
    delete ui;
}
