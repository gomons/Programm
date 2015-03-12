#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QSplashScreen>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include "TableInfo.h"

namespace {

QString dbFileName = "programm.sqlite";
QString photoDirname = "photos";
QString backupDirname = "backups";

bool initPhotosDir()
{
    if (!QDir(photoDirname).exists())
    {
        bool created = QDir().mkdir(photoDirname);
        if (!created)
        {
            QMessageBox::critical(nullptr,
                                  QObject::tr("Filesystem error."),
                                  QObject::tr("Photos directory can not be created."));
            return false;
        }
    }

    return true;
}

bool initBackupsDir()
{
    if (!QDir(backupDirname).exists())
    {
        bool created = QDir().mkdir(backupDirname);
        if (!created)
        {
            QMessageBox::critical(nullptr,
                                  QObject::tr("Filesystem error."),
                                  QObject::tr("Backups directory can not be created."));
            return false;
        }
    }

    return true;
}

bool backupDatabase()
{
    QFile dbFile(dbFileName);

    if (dbFile.exists())
    {
        QString dateTime = QDateTime::currentDateTime().toString("dd-MM-yyyy_hh-mm-ss-zzz");
        QString backupFileName = "backup_" + dateTime + "_sqlite";
        QString backupFilePath = backupDirname + "/" + backupFileName;
        bool copyed = dbFile.copy(backupFilePath);
        if (!copyed)
        {
            QMessageBox::critical(nullptr,
                                  QObject::tr("Filesystem error."),
                                  QObject::tr("Can not copy backup. Error: ") + dbFile.errorString());
            return false;
        }
    }
    return true;
}

bool initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    bool valid = db.isValid();
    if (!valid)
    {
        QMessageBox::critical(nullptr,
                              QObject::tr("Database error."),
                              QObject::tr("Database is not loaded. Error: ") + db.lastError().text());
        return false;
    }

    db.setDatabaseName(dbFileName);
    bool opened = db.open();
    if (!opened)
    {
        QMessageBox::critical(nullptr,
                              QObject::tr("Database error."),
                              QObject::tr("Database is not opened. Error: ") + db.lastError().text());
        return false;
    }


    QSqlQuery query;
    bool tableCreated = query.exec(TableInfo().getCreateTableQuery());
    if (!tableCreated)
    {
        QMessageBox::critical(nullptr,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'borrower' is not created. Error: ") + query.lastError().text());
        return false;
    }

    return true;
}

} // namespace

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/img/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    if (!initPhotosDir())
        return 1;

    if (!initBackupsDir())
        return 1;

    if (!backupDatabase())
        return 1;

    if (!initDatabase())
        return 1;

    MainWindow w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
