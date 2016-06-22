#-------------------------------------------------
#
# Project created by QtCreator 2016-06-22T22:23:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ituprefix
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp \
    cli.cpp \
    lookup.cpp

HEADERS  += \
    cli.h \
    lookup.h

CONFIG += c++11
