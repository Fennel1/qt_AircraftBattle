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
    dropobjects.cpp \
    enemyplane.cpp \
    gameover.cpp \
    loginwindow.cpp \
    main.cpp \
    mainscene.cpp \
    mainwindow.cpp \
    map.cpp \
    myplane.cpp \
    props.cpp \
    skill.cpp \
    thehome.cpp

HEADERS += \
    bomb.h \
    bullet.h \
    config.h \
    data.h \
    dropobjects.h \
    enemyplane.h \
    gameover.h \
    loginwindow.h \
    mainscene.h \
    mainwindow.h \
    map.h \
    myplane.h \
    props.h \
    skill.h \
    thehome.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

FORMS += \
    gameover.ui \
    mainwindow.ui
