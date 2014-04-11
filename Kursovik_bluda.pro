#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T13:55:59
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kursovik_bluda
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    detaileddialog.cpp \
    filter.cpp

HEADERS  += mainwindow.h \
    defines.h \
    detaileddialog.h \
    filter.h

FORMS    += mainwindow.ui \
    detaileddialog.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    README.md
