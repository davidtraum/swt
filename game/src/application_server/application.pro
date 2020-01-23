QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animationentity.cpp \
    animationmovement.cpp \
    city.cpp \
    client.cpp \
    datamodel.cpp \
    gameloop.cpp \
    goodselector.cpp \
    graphicsmanager.cpp \
    highlighter.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    maprenderer.cpp \
    maptile.cpp \
    menubar.cpp \
    minimap.cpp \
    mousedecor.cpp \
    player.cpp \
    point.cpp \
    renderthread.cpp \
    river.cpp \
    routeinterface.cpp \
    routelistinterface.cpp \
    scene.cpp \
    sidepanel.cpp \
    sprite.cpp \
    tooltipmenu.cpp \
    trainrenderer.cpp \
    view.cpp

HEADERS += \
    animationentity.h \
    animationmovement.h \
    city.h \
    client.h \
    datamodel.h \
    gameloop.h \
    goodselector.h \
    graphicsmanager.h \
    highlighter.h \
    main.h \
    mainmenu.h \
    mainwindow.h \
    maprenderer.h \
    maptile.h \
    menubar.h \
    minimap.h \
    mousedecor.h \
    player.h \
    point.h \
    renderthread.h \
    river.h \
    routeListInterface.h \
    routeinterface.h \
    scene.h \
    sidepanel.h \
    sprite.h \
    tooltipmenu.h \
    tooltipmenu.h \
    trainrenderer.h \
    view.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data.qrc \
    Graphics.qrc
