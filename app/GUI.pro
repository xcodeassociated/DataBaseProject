QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app
RC_FILE = GUI.rc

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
#QMAKE_CXXFLAGS += -stdlib=libc++

CONFIG += no_keywords #static

SOURCES += main.cpp\
    Sources/Controller.cpp \
    Sources/Model.cpp \
    Sources/VirtualController.cpp \
    Sources/LoginWindow.cpp \
    Sources/PatientRegistrationWindow.cpp \
    Sources/DoctorsWindow.cpp \
    Sources/AdminWindow.cpp

HEADERS  += \
    Headers/Controller.h \
    Headers/Model.h \
    Headers/VirtualController.h \
    Headers/LoginWindow.h \
    Headers/PatientRegistrationWindow.h \
    Headers/DoctorsWindow.h \
    Headers/AdminWindow.h

FORMS    += \
    UI/LoginWindow.ui \
    UI/PatientRegistrationWindow.ui \
    UI/DoctorsWindow.ui \
    UI/AdminWindow.ui

RESOURCES += \
    Resources/projectresources.qrc

DISTFILES +=
