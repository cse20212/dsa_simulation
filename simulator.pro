#-------------------------------------------------
#
# Project created by QtCreator 2015-02-17T22:55:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    algorithm.cpp \
    dataset.cpp \
    dataitem.cpp \
    genealgorithm.cpp \
    insertionsort.cpp \
    selectionsort.cpp \
    mergesort.cpp

HEADERS  += mainwindow.h \
    algorithm.h \
    dataset.h \
    dataitem.h \
    genealgorithm.h \
    insertionsort.h \
    selectionsort.h \
    mergesort.h

FORMS    += mainwindow.ui

RESOURCES += \
    pseudocode.qrc
