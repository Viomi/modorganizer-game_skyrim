#-------------------------------------------------
#
# Project created by QtCreator 2014-11-15T15:36:33
#
#-------------------------------------------------


TARGET = gameSkyrimSE
TEMPLATE = lib

CONFIG += plugins
CONFIG += dll
DEFINES += GAMESKYRIMSE_LIBRARY

SOURCES += gameskyrimSE.cpp \
    skyrimSEbsainvalidation.cpp \
    skyrimSEscriptextender.cpp \
    skyrimSEdataarchives.cpp \
    skyrimSEsavegame.cpp \
    skyrimSEsavegameinfo.cpp

HEADERS += gameskyrimSE.h \
    skyrimSEbsainvalidation.h \
    skyrimSEscriptextender.h \
    skyrimSEdataarchives.h \
    skyrimSEsavegame.h \
    skyrimSEsavegameinfo.h

CONFIG(debug, debug|release) {
  LIBS += -L"$${OUT_PWD}/../gameGamebryo/debug"
  PRE_TARGETDEPS += \
    $$OUT_PWD/../gameGamebryo/debug/gameGamebryo.lib
} else {
  LIBS += -L"$${OUT_PWD}/../gameGamebryo/release"
  PRE_TARGETDEPS += \
    $$OUT_PWD/../gameGamebryo/release/gameGamebryo.lib
}

include(../plugin_template.pri)

INCLUDEPATH += "$${BOOSTPATH}" "$${PWD}/../gamefeatures" "$${PWD}/../gamegamebryo"

LIBS += -ladvapi32 -lole32 -lgameGamebryo

OTHER_FILES += \
    gameskyrimSE.json\
    SConscript \
    CMakeLists.txt

