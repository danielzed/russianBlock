TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    object.cpp \
    main1.cpp

LIBS+=D:\libs\pdcurses\wincon\pdcurses.a
INCLUDEPATH+=D:\libs\pdcurses

HEADERS += \
    object.h
