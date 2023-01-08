#-------------------------------------------------
#
# Project created by QtCreator 2022-06-01T15:34:49
#
#-------------------------------------------------

QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DCPictureEditor1_3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        ActionsWidgets/ActionNewWidget/actionnewwidget.cpp \
        Color/colormanager.cpp \
        Color/colorslider.cpp \
        Color/hsvcolordialog.cpp \
        Color/hwidget.cpp \
        Color/svwidget.cpp \
        History/historymanager.cpp \
        Layer/backgroundlayer.cpp \
        Layer/layer.cpp \
        Layer/layerattrmanager.cpp \
        Layer/layermanager.cpp \
        Layer/picturelayer.cpp \
        Layer/textlayer.cpp \
        SetToolsWidgets/SetBrushWidget/setbrushwidget.cpp \
        SetToolsWidgets/SetSealWidget/setsealwidget.cpp \
        SetToolsWidgets/SetTextEditorWidget/fontsetting.cpp \
        SetToolsWidgets/SetTextEditorWidget/textlayereditor.cpp \
        SetToolsWidgets/SetTextEditorWidget/wkwidgetfortle.cpp \
        main.cpp \
        mainwindow.cpp \
        myalgorithm.cpp \
        workspace.cpp

HEADERS += \
        ActionsWidgets/ActionNewWidget/actionnewwidget.h \
        Color/colormanager.h \
        Color/colorslider.h \
        Color/hsvcolordialog.h \
        Color/hwidget.h \
        Color/svwidget.h \
        History/historymanager.h \
        Layer/backgroundlayer.h \
        Layer/layer.h \
        Layer/layerattrmanager.h \
        Layer/layermanager.h \
        Layer/picturelayer.h \
        Layer/textlayer.h \
        SetToolsWidgets/SetBrushWidget/setbrushwidget.h \
        SetToolsWidgets/SetSealWidget/setsealwidget.h \
        SetToolsWidgets/SetTextEditorWidget/fontsetting.h \
        SetToolsWidgets/SetTextEditorWidget/textlayereditor.h \
        SetToolsWidgets/SetTextEditorWidget/wkwidgetfortle.h \
        mainwindow.h \
        myalgorithm.h \
        workspace.h

FORMS += \
        ActionsWidgets/ActionNewWidget/actionnewwidget.ui \
        Color/colormanager.ui \
        Layer/layerattrmanager.ui \
        SetToolsWidgets/SetBrushWidget/setbrushwidget.ui \
        SetToolsWidgets/SetSealWidget/setsealwidget.ui \
        SetToolsWidgets/SetTextEditorWidget/fontsetting.ui \
        SetToolsWidgets/SetTextEditorWidget/textlayereditor.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource/rc.qrc

RC_ICONS = Resource/AppIcon.ico
