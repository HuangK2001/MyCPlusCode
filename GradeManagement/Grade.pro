#-------------------------------------------------
#
# Project created by QtCreator 2022-03-07T09:36:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Grade
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    usersql.cpp \
    addmin.cpp \
    addgrade.cpp \
    stu.cpp \
    changeadmin.cpp \
    showgrade.cpp \
    stu_findgrade.cpp \
    stu_modpassword.cpp

HEADERS += \
        mainwindow.h \
    usersql.h \
    addmin.h \
    addgrade.h \
    stu.h \
    changeadmin.h \
    showgrade.h \
    stu_findgrade.h \
    stu_modpassword.h

FORMS += \
        mainwindow.ui \
    addmin.ui \
    addgrade.ui \
    stu.ui \
    changeadmin.ui \
    showgrade.ui \
    stu_findgrade.ui \
    stu_modpassword.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc
