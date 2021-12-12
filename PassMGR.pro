QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/sources/keygendialog.cpp \
    src/sources/mainwindow.cpp \
    src/sources/passworddialog.cpp \
    src/sources/typemaster.cpp

HEADERS += \
    src/headers/deselectabletreeview.h \
    src/headers/globals.h \
    src/headers/keygendialog.h \
    src/headers/mainwindow.h \
    src/headers/passworddialog.h \
    src/headers/typemaster.h

FORMS += \
    src/forms/keygendialog.ui \
    src/forms/mainwindow.ui \
    src/forms/passworddialog.ui \
    src/forms/typemaster.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resouces/resource.qrc
