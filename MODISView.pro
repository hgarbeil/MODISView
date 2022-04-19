#-------------------------------------------------
#
# Project created by QtCreator 2022-03-02T10:48:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MODISView
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
    mod11_hdf.cpp \
    imwidget.cpp \
    qcustomplot.cpp \
    myprofileplot.cpp \
    plotscaledialog.cpp \
    mod13_hdf.cpp \
    globalcoords.cpp

HEADERS += \
        mainwindow.h \
    mod11_hdf.h \
    imwidget.h \
    qcustomplot.h \
    myprofileplot.h \
    plotscaledialog.h \
    mod13_hdf.h \
    globalcoords.h

FORMS += \
        mainwindow.ui \
    plotscaledialog.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -lmfhdf -ldf
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc
