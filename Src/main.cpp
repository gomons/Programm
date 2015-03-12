#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "TableInfo.h"

bool initPhotosDir()
{
    QString photoDirname("photos");

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

    db.setDatabaseName("programm");
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!initPhotosDir())
        return 1;

    if (!initDatabase())
        return 1;

    MainWindow w;
    w.show();

    return a.exec();
}
