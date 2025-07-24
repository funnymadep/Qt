CONFIG      += plugin debug_and_release designer
TARGET      = $$qtLibraryTarget(circleprogressplugin)
TEMPLATE    = lib

HEADERS     = CircleProgressplugin.h
SOURCES     = CircleProgressplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(CircleProgress.pri)
