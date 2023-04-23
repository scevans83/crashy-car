QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG+=sdk_no_version_check

SOURCES += \
    Game.cpp \
    Health.cpp \
    Obstacle.cpp \
    leftSide.cpp \
    RoadLines.cpp \
    Score.cpp \
    buttons.cpp \
    main.cpp \
    player.cpp \
    accel.cpp \
    accelthread.cpp

HEADERS += \
    Game.h \
    Health.h \
    Obstacle.h \
    leftSide.h \
    RoadLines.h \
    Score.h \
    buttons.h \
    player.h \
    accel.h \
    accelthread.h

# Uncomment this if building for the BeagleBone
#LIBS += -L/usr/lib -lc

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
