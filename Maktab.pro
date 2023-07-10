#-------------------------------------------------
#
# Project created by QtCreator 2021-05-05T17:26:34
#
#-------------------------------------------------

QT       += core gui
QT       +=sql
QT      +=  webkitwidgets network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Maktab
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user_ui.cpp

HEADERS  += mainwindow.h \
    user_ui.h

FORMS    += \
    user_ui.ui \
    mainwindow.ui

RESOURCES += \
    img.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/webkitwidgets/previewer
INSTALLS += target
