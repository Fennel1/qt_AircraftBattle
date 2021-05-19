QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamerecord.cpp \
    player.cpp \
    main.cpp \
    sources_game/bomb.cpp \
    sources_game/boss.cpp \
    sources_game/bullet.cpp \
    sources_game/data.cpp \
    sources_game/dropobjects.cpp \
    sources_game/enemyplane.cpp \
    sources_window/forgetpw.cpp \
    sources_window/gamehelp.cpp \
    sources_window/gameover.cpp \
    sources_window/loginwindow.cpp \
    sources_game/mainscene.cpp \
    sources_window/mainwindow.cpp \
    sources_game/map.cpp \
    sources_game/myplane.cpp \
    sources_window/props.cpp \
    sources_game/skill.cpp \
    sources_window/regwindow.cpp \
    sources_window/thehome.cpp

HEADERS += \
    gamerecord.h \
    headers_game/bomb.h \
    headers_game/boss.h \
    headers_game/bullet.h \
    headers_game/config.h \
    headers_game/data.h \
    headers_game/dropobjects.h \
    headers_game/enemyplane.h \
    headers_window/gamehelp.h \
    headers_window/gameover.h \
    headers_window/loginwindow.h \
    headers_game/mainscene.h \
    headers_window/mainwindow.h \
    headers_game/map.h \
    headers_game/myplane.h \
    headers_window/props.h \
    headers_game/skill.h \
    headers_window/thehome.h \
    player.h \
    headers_window/forgetpw.h \
    headers_window/regwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc\
    playerFile.dat\
    commonrecord.dat\
    endlessrecord.dat\

FORMS += \
    gameover.ui \
    mainwindow.ui
