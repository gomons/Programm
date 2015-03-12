#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T13:47:43
#
#-------------------------------------------------

QT += core gui sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Programm
TEMPLATE = app

SOURCES += \
    AddRecordDlg.cpp \
    main.cpp \
    MainWindow.cpp \
    FiltersContainerWidget.cpp \
    SortFilterProxyModel.cpp \
    TableInfo.cpp \
    TextFilterWidget.cpp \
    ViewRecordDlg.cpp \
    IntegerFilterWidget.cpp \
    RegExpTextMatcher.cpp \
    IntRangeTextMatcher.cpp \
    TableViewWidget.cpp \
    SelectHeaderFieldsDlg.cpp \
    FilterDlg.cpp

HEADERS += \
    AbstractFilterWidget.h \
    AddRecordDlg.h \
    FiltersContainerWidget.h \
    MainWindow.h \
    SortFilterProxyModel.h \
    TableInfo.h \
    TextFilterWidget.h \
    ViewRecordDlg.h \
    IntegerFilterWidget.h \
    AbstractTextMatcher.h \
    RegExpTextMatcher.h \
    IntRangeTextMatcher.h \
    TableViewWidget.h \
    SelectHeaderFieldsDlg.h \
    FilterDlg.h

FORMS += \
    AddRecordDlg.ui \
    FiltersContainerWidget.ui \
    MainWindow.ui \
    TextFilterWidget.ui \
    ViewRecordDlg.ui \
    IntegerFilterWidget.ui \
    TableViewWidget.ui \
    SelectHeaderFieldsDlg.ui \
    FilterDlg.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    settings.conf
