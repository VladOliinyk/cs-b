QT += core
QT -= gui

TARGET = a1-calculator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    calculation.cpp \

HEADERS += \
    calculation.h \
    prepear.h \
    configuration.h \

