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

bool initPhotosDir(QMainWindow *w)
{
    if (!QDir(photoDirname).exists())
    {
        bool created = QDir().mkdir(photoDirname);
        if (!created)
        {
            QMessageBox::critical(w,
                                  QObject::tr("Filesystem error."),
                                  QObject::tr("Photos directory can not be created."));
            return false;
        }
    }

    return true;
}

bool initBackupsDir(QMainWindow  *w)
{
    if (!QDir(backupDirname).exists())
    {
        bool created = QDir().mkdir(backupDirname);
        if (!created)
        {
            QMessageBox::critical(w,
                                  QObject::tr("Filesystem error."),
                                  QObject::tr("Backups directory can not be created."));
            return false;
        }
    }

    return true;
}

bool backupDatabase(QMainWindow *w)
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
            QMessageBox::critical(w,
                                  QObject::tr("Filesystem error."),
                                  QObject::tr("Can not copy backup. Error: ") + dbFile.errorString());
            return false;
        }
    }

    return true;
}

bool openDatabase(QMainWindow *w)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    bool valid = db.isValid();
    if (!valid)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Database is not loaded. Error: ") + db.lastError().text());
        return false;
    }

    db.setDatabaseName(dbFileName);
    bool opened = db.open();
    if (!opened)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Database is not opened. Error: ") + db.lastError().text());
        return false;
    }

    return true;
}

bool createRegionTable(QMainWindow *w)
{
    QSqlDatabase db;

    if (db.tables().contains("region"))
        return true;

    QString createRegionsTableQuery = "CREATE TABLE IF NOT EXISTS region ("
                                      "id INTEGER PRIMARY KEY,"
                                      "name TEXT UNIQUE"
                                      ");";
    QSqlQuery query;
    bool tableCreated = query.exec(createRegionsTableQuery);
    if (!tableCreated)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'region' is not created. Error: ") + query.lastError().text());
        return false;
    }

    bool inserted = true;

    QString insertQuery = "INSERT INTO region (name) VALUES ('%1');";
    inserted |= query.exec(insertQuery.arg("г. Минск"));
    inserted |= query.exec(insertQuery.arg("Брестская область"));
    inserted |= query.exec(insertQuery.arg("Витебская область"));
    inserted |= query.exec(insertQuery.arg("Гомельская область"));
    inserted |= query.exec(insertQuery.arg("Гродненская область"));
    inserted |= query.exec(insertQuery.arg("Минская область"));
    inserted |= query.exec(insertQuery.arg("Могилёвская область"));

    if (!inserted)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'region' not populated.") + query.lastError().text());
        return false;
    }

    return true;
}

bool createColorTable(QMainWindow *w)
{
    QSqlDatabase db;

    if (db.tables().contains("region"))
        return true;

    QString createTableQuery = "CREATE TABLE IF NOT EXISTS color ("
                               "id INTEGER PRIMARY KEY,"
                               "name TEXT UNIQUE"
                               ");";
    QSqlQuery query;
    bool tableCreated = query.exec(createTableQuery);
    if (!tableCreated)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'color' is not created. Error: ") + query.lastError().text());
        return false;
    }

    bool inserted = true;

    QString insertQuery = "INSERT INTO color (name) VALUES ('%1');";
    inserted |= query.exec(insertQuery.arg("Белый"));
    inserted |= query.exec(insertQuery.arg("Красный"));
    inserted |= query.exec(insertQuery.arg("Желтый"));
    inserted |= query.exec(insertQuery.arg("Зеленый"));
    inserted |= query.exec(insertQuery.arg("Синий"));

    if (!inserted)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'color' not populated.") + query.lastError().text());
        return false;
    }

    return true;
}

bool createBelongingTable(QMainWindow *w)
{
    QSqlDatabase db;

    if (db.tables().contains("belonging"))
        return true;

    QString createRegionsTableQuery = "CREATE TABLE IF NOT EXISTS belonging ("
                                      "id INTEGER PRIMARY KEY,"
                                      "description TEXT UNIQUE);";
    QSqlQuery query;
    bool tableCreated = query.exec(createRegionsTableQuery);
    if (!tableCreated)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'belonging' is not created. Error: ") + query.lastError().text());
        return false;
    }

    bool inserted = true;

    QString insertQuery = "INSERT INTO belonging (description) VALUES ('%1');";
    inserted |= query.exec(insertQuery.arg("Владелец личного подсобного хозяйства"));
    inserted |= query.exec(insertQuery.arg("Субъект агроэкотуризма"));
    inserted |= query.exec(insertQuery.arg("Ремесленник"));
    inserted |= query.exec(insertQuery.arg("Фермер"));
    inserted |= query.exec(insertQuery.arg("Учредитель коммерческой организации"));
    inserted |= query.exec(insertQuery.arg("Индивидуальный предприниматель"));

    if (!inserted)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'belonging' not populated.") + query.lastError().text());
        return false;
    }

    return true;
}

bool createBorrowerTable(QMainWindow *w)
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
                                       "color_id INTEGER,"
                                       "comment TEXT,"
                                       "FOREIGN KEY(region_id) REFERENCES region(id),"
                                       "FOREIGN KEY(belonging_id) REFERENCES belonging(id),"
                                       "FOREIGN KEY(color_id) REFERENCES color(id)"
                                       ");";

    QSqlQuery query;
    bool tableCreated = query.exec(createBorrowerTableQuery);
    if (!tableCreated)
    {
        QMessageBox::critical(w,
                              QObject::tr("Database error."),
                              QObject::tr("Table 'borrower' is not created. Error: ") + query.lastError().text());
        return false;
    }

    return true;
}

bool initDatabase(QMainWindow *w)
{
    bool opened = openDatabase(w);
    if (!opened)
        return false;

    bool created = createRegionTable(w);
    if (!created)
        return false;

    created = createBelongingTable(w);
    if (!created)
        return false;

    created = createColorTable(w);
    if (!created)
        return false;

    created = createBorrowerTable(w);
    if (!created)
        return false;

    return true;
}

} // namespace


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPixmap pixmap(":/img/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    if (!initPhotosDir(&w))
        return 1;

    if (!initBackupsDir(&w))
        return 1;

    if (!backupDatabase(&w))
        return 1;

    if (!initDatabase(&w))
        return 1;

    if (!w.init())
        return 1;

    w.show();
    splash.finish(&w);

    return a.exec();
}
