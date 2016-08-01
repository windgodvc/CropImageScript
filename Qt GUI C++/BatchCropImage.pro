#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T23:42:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BatchCropImage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    form.h

FORMS    += mainwindow.ui \
    form.ui

CONFIG += C++11 \

RESOURCES += \
    uires.qrc

