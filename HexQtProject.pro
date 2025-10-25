QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = HexQtProject
TEMPLATE = app

SOURCES += src/main.cpp \
           src/core/Core.cpp

HEADERS += src/core/Core.h
