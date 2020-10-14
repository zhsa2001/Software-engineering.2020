#-------------------------------------------------
#
# Project created by QtCreator 2020-08-18T14:41:21
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KR-SoftwareEngineering
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        act.cpp \
        actmodel.cpp \
        book.cpp \
        bookdialog.cpp \
        hero.cpp \
        heromodel.cpp \
        herowindow.cpp \
        main.cpp \
        mainwindow.cpp \
        place.cpp \
        placemodel.cpp \
        placewindow.cpp

HEADERS += \
        act.h \
        actmodel.h \
        book.h \
        bookdialog.h \
        hero.h \
        heromodel.h \
        herowindow.h \
        mainwindow.h \
        place.h \
        placemodel.h \
        placewindow.h

FORMS += \
        bookdialog.ui \
        herowindow.ui \
        mainwindow.ui \
        placewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
