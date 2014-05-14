#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T13:55:59
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCookBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    detaileddialog.cpp \
    filter.cpp \
    userfavorites.cpp \
    registrationform.cpp

HEADERS  += mainwindow.h \
    defines.h \
    detaileddialog.h \
    filter.h \
    userfavorites.h \
    registrationform.h

FORMS    += mainwindow.ui \
    detaileddialog.ui \
    registrationform.ui

TRANSLATIONS += qtcookbook_ru.ts

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    README.md
