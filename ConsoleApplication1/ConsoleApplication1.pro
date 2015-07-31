#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T18:33:05
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ConsoleApplication1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    LinkedListManipulation.cpp \
    PlayingWithTemplate1.cpp \
    PlayWithFunctorsLambdasFunctions.cpp \
    Stack.cpp \
    stdafx.cpp \
    Tree.cpp

HEADERS += \
    LinkedListManipulation.h \
    PlayingWithTemplate1.h \
    PlayWithFunctorsLambdasFunctions.h \
    Stack.h \
    stdafx.h \
    targetver.h \
    Tree.h


CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.10
QMAKE_LFLAGS += -std=c++11 -stdlib=libstdc++ -mmacosx-version-min=10.10
