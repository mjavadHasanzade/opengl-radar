QT       += core gui opengl openglwidgets
LIBS += -lopengl32 -lglu32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    sources/jetcore.cpp \
    sources/mainwindow.cpp \
    sources/openglcore.cpp \
    sources/pythoncore.cpp

HEADERS += \
    headers/mainwindow.h \
    headers/openglcore.h \
    headers/pythoncore.h \
    headers/jetcore.h

FORMS += \
    forms/mainwindow.ui

RESOURCES += \
    extract-vol.py


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += "C:/Program Files/Python312/include"
LIBS += -L"C:/Program Files/Python312/libs" -L"C:/Program Files/Python312" -lpython312
