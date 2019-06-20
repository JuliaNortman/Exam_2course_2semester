QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_hashtest.cpp

HEADERS += \
    base.h \
    linearhash.h \
    singlelinkedlist.h \
    tst_hashtest.h
