QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    dialog.cpp \
    dialog2.cpp \
    dialog3.cpp \
    dialog4.cpp \
    dialog5.cpp \
    dialog6.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    admin.h \
    dialog.h \
    dialog2.h \
    dialog3.h \
    dialog4.h \
    dialog5.h \
    dialog6.h \
    mainwindow.h \
    voce.h

FORMS += \
    admin.ui \
    dialog.ui \
    dialog2.ui \
    dialog3.ui \
    dialog4.ui \
    dialog5.ui \
    dialog6.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
