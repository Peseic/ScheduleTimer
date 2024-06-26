QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_dll.cpp \
    buttonstyles.cpp \
    choosetime.cpp \
    log_page.cpp \
    main.cpp \
    mainwindow.cpp \
    register_page.cpp \
    set_class.cpp \
    start_use.cpp \
    timer.cpp \
    timer_popup.cpp

HEADERS += \
    add_dll.h \
    buttonstyles.h \
    choosetime.h \
    log_page.h \
    mainwindow.h \
    register_page.h \
    set_class.h \
    start_use.h \
    timer.h \
    timer_popup.h \
    window_titles.h

FORMS += \
    add_dll.ui \
    choosetime.ui \
    log_page.ui \
    mainwindow.ui \
    register_page.ui \
    set_class.ui \
    start_use.ui \
    timer.ui \
    timer_popup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
