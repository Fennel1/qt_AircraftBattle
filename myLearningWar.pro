QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bomb.cpp \
    bullet.cpp \
    data.cpp \
    enemyplane.cpp \
    main.cpp \
    mainscene.cpp \
    map.cpp \
    myplane.cpp \
    skill.cpp

HEADERS += \
    bomb.h \
    bullet.h \
    config.h \
    data.h \
    enemyplane.h \
    mainscene.h \
    map.h \
    myplane.h \
    skill.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
