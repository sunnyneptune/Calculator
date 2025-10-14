QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    ../c_exercises/cpp/cpp lesson/calculator.c \
    calculator.c \
    chart.cpp \
    credit.c \
    creditwindow.cpp \
    deposit.c \
    depositwindow.cpp \
    qcustomplot.cpp \
    stack.c \
    main.cpp \
    mainwindow.cpp

HEADERS += \
#    ../c_exercises/cpp/cpp lesson/calculator.h \
    calculator.h \
    chart.h \
    credit.h \
    creditwindow.h \
    deposit.h \
    depositwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    chart.ui \
    creditwindow.ui \
    depositwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Makefile
