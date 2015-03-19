#include "MainWindow.h"
#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QSplashScreen>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTranslator>
#include "BorrowerTableInfo.h"

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

    {
        if (!db.tables().contains("region"))
        {
            QString createRegionsTableQuery = "CREATE TABLE IF NOT EXISTS region ("
                                              "id INTEGER PRIMARY KEY,"
                                              "name TEXT);";
            QSqlQuery query;
            bool tableCreated = query.exec(createRegionsTableQuery);
            if (!tableCreated)
            {
                QMessageBox::critical(nullptr,
                                      QObject::tr("Database error."),
                                      QObject::tr("Table 'region' is not created. Error: ") + query.lastError().text());
                return false;
            }

            QString insertQuery = "INSERT INTO region (name) VALUES ('%1');";
            query.exec(insertQuery.arg("г. Минск"));
            query.exec(insertQuery.arg("Брестская область"));
            query.exec(insertQuery.arg("Витебская область"));
            query.exec(insertQuery.arg("Гомельская область"));
            query.exec(insertQuery.arg("Гродненская область"));
            query.exec(insertQuery.arg("Минская область"));
            query.exec(insertQuery.arg("Могилёвская область"));
        }

        if (!db.tables().contains("belonging"))
        {
            QString createRegionsTableQuery = "CREATE TABLE IF NOT EXISTS belonging ("
                                              "id INTEGER PRIMARY KEY,"
                                              "description TEXT);";
            QSqlQuery query;
            bool tableCreated = query.exec(createRegionsTableQuery);
            if (!tableCreated)
            {
                QMessageBox::critical(nullptr,
                                      QObject::tr("Database error."),
                                      QObject::tr("Table 'belonging' is not created. Error: ") + query.lastError().text());
                return false;
            }

            QString insertQuery = "INSERT INTO belonging (description) VALUES ('%1');";
            auto inserted = query.exec(insertQuery.arg("Владелец личного подсобного хозяйства"));
            inserted = query.exec(insertQuery.arg("Субъект агроэкотуризма"));
            inserted = query.exec(insertQuery.arg("Ремесленник"));
            inserted = query.exec(insertQuery.arg("Фермер"));
            inserted = query.exec(insertQuery.arg("Учредитель коммерческой организации"));
            inserted = query.exec(insertQuery.arg("Индивидуальный предприниматель"));
        }
    }

    {
        QString createBorrowerTableQuery = "CREATE TABLE IF NOT EXISTS borrower ("
                                           "id INTEGER PRIMARY KEY,"
                                           "name TEXT,"
                                           "surname TEXT,"
                                           "patronymic TEXT, "
                                           "photo TEXT, "
                                           "activity TEXT, "
                                           "loan_guarantee TEXT,"
                                           "belonging_id TEXT,"
                                           "amount INTEGER,"
                                           "region_id INTEGER,"
                                           "place TEXT,"
                                           "contact TEXT,"
                                           "FOREIGN KEY(region_id) REFERENCES region(id),"
                                           "FOREIGN KEY(belonging_id) REFERENCES belonging(id)"
                                           ");";

        QSqlQuery query;
        bool tableCreated = query.exec(createBorrowerTableQuery);
        if (!tableCreated)
        {
            QMessageBox::critical(nullptr,
                                  QObject::tr("Database error."),
                                  QObject::tr("Table 'borrower' is not created. Error: ") + query.lastError().text());
            return false;
        }
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

//    QTranslator programmTranslator;
//    programmTranslator.load(":/translate/Programm_ru.qm");
//    a.installTranslator(&programmTranslator);

//    QTranslator qtTranslator;
//    qtTranslator.load("qt_ru", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    a.installTranslator(&qtTranslator);

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

//    TestDialog dlg;
//    dlg.show();
//    splash.finish(&dlg);

    return a.exec();
}
