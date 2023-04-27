QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG+=sdk_no_version_check

SOURCES += \
    source/Game.cpp \
    source/Obstacle.cpp \
    source/leftSide.cpp \
    source/rightSide.cpp \
    source/RoadLines.cpp \
    source/startbtn.cpp \
    source/restartbtn.cpp \
    source/Score.cpp \
    source/finalscore.cpp \
    source/main.cpp \
    source/player.cpp \
    source/accel.cpp \
    source/accelthread.cpp

HEADERS += \
    source/Game.h \
    source/Obstacle.h \
    source/leftSide.h \
    source/rightSide.h \
    source/RoadLines.h \
    source/startbtn.h \
    source/restartbtn.h \
    source/Score.h \
    source/finalscore.h \
    source/player.h \
    source/accel.h \
    source/accelthread.h

# Uncomment this if building for the BeagleBone
#LIBS += -L/usr/lib -lc

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
