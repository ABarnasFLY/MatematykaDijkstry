TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vertex.cpp \
    roadmap.cpp

HEADERS += \
    vertex.h \
    edge.h \
    roadmap.h
