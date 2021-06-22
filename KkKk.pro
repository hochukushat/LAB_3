QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Keyboard.cpp \
    dialogaddedit.cpp \
    main.cpp \
    mainwindow.cpp \
    tablewidget.cpp

HEADERS += \
    Keyboard.h \
    dialogaddedit.h \
    mainwindow.h \
    tablewidget.h

FORMS += \
    dialogaddedit.ui \
    mainwindow.ui

TRANSLATIONS += \
    DimaP_ru_RU.ts \
    DimaP_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
