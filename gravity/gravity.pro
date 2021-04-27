TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -LC:\\SFML\\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:\\SFML\\include
DEPENDPATH += C:\\include

SOURCES += \
        bodymanager.cpp \
        circleshape.cpp \
        ibody.cpp \
        ishape.cpp \
        main.cpp \
        polygonshape.cpp \
        simplebody.cpp \
        space.cpp \
        spacesprites.cpp \
        vector2d.cpp

HEADERS += \
    bodymanager.h \
    circleshape.h \
    ibody.h \
    ishape.h \
    polygonshape.h \
    simplebody.h \
    space.h \
    spacesprites.h \
    vector2d.h
