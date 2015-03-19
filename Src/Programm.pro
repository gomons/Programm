#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T13:47:43
#
#-------------------------------------------------

QT += core gui sql printsupport
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
    TextFilterWidget.cpp \
    ViewRecordDlg.cpp \
    RegExpTextMatcher.cpp \
    IntRangeTextMatcher.cpp \
    TableViewWidget.cpp \
    SelectHeaderFieldsDlg.cpp \
    FilterDlg.cpp \
    AboutDlg.cpp \
    IntFilterWidget.cpp \
    BorrowerTableInfo.cpp

HEADERS += \
    AbstractFilterWidget.h \
    AddRecordDlg.h \
    FiltersContainerWidget.h \
    MainWindow.h \
    SortFilterProxyModel.h \
    TextFilterWidget.h \
    ViewRecordDlg.h \
    AbstractTextMatcher.h \
    RegExpTextMatcher.h \
    IntRangeTextMatcher.h \
    TableViewWidget.h \
    SelectHeaderFieldsDlg.h \
    FilterDlg.h \
    AboutDlg.h \
    IntFilterWidget.h \
    BorrowerTableInfo.h

FORMS += \
    AddRecordDlg.ui \
    FiltersContainerWidget.ui \
    MainWindow.ui \
    TextFilterWidget.ui \
    ViewRecordDlg.ui \
    TableViewWidget.ui \
    SelectHeaderFieldsDlg.ui \
    FilterDlg.ui \
    AboutDlg.ui \
    IntFilterWidget.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    settings.conf

TRANSLATIONS += \
    Programm_ru.ts
