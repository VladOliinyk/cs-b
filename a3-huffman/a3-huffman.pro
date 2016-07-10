QT += core
QT -= gui

TARGET = a3-huffman
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    encode.cpp \
    decode.cpp

HEADERS += \
    encode.h \
    decode.h \
    node.h \
    header.h

