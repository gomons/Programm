#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T13:47:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Programm
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AddRecordDlg.cpp \
    ViewRecordDlg.cpp \
    SortFilterProxyModel.cpp

HEADERS  += MainWindow.h \
    AddRecordDlg.h \
    ViewRecordDlg.h \
    SortFilterProxyModel.h

FORMS    += MainWindow.ui \
    AddRecordDlg.ui \
    ViewRecordDlg.ui

RESOURCES += \
    resources.qrc
