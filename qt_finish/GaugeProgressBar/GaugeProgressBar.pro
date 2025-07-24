CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(gaugeprogressbarplugin)
TEMPLATE    = lib

HEADERS     = gaugeprogressbarplugin.h
SOURCES     = gaugeprogressbarplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(gaugeprogressbar.pri)
