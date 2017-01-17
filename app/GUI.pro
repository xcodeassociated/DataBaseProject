QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app
RC_FILE = GUI.rc

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -stdlib=libc++

CONFIG += no_keywords #static

linux64 {
    LIBS += -L"/usr/lib" -lmysqlcppconn

    INCLUDEPATH += "/usr/include/" \
                    "/usr/include/cppconn"
}

mac {

}

SOURCES += Logic/UIDataModel/AdminModel/AdminModel.cpp \
 Logic/UIDataModel/DoctorsModel/DoctorsModel.cpp \
 Logic/UIDataModel/LoginModel/LoginModel.cpp \
 Logic/UIDataModel/Model/Model.cpp \
 Logic/UIDataModel/RegistrationModel/RegistrationModel.cpp \
 main.cpp \
 UI/AdminWindow/AdminWindow.cpp \
 UI/DoctorsWindow/DoctorsWindow.cpp \
 UI/LoginWindow/LoginWindow.cpp \
 UI/PatientRegistrationWindow/PatientRegistrationWindow.cpp \
 UI/UIController/Controller/Controller.cpp \
 UI/UIController/VirtualController/VirtualController.cpp

HEADERS  += Logic/UIDataModel/AdminModel/AdminModel.hpp \
 Logic/UIDataModel/DoctorsModel/DoctorsModel.hpp \
 Logic/UIDataModel/LoginModel/LoginModel.hpp \
 Logic/UIDataModel/Model/Model.hpp \
 Logic/UIDataModel/Model/DataStructures/Doctor.hpp \
 Logic/UIDataModel/Model/DataStructures/Patient.hpp \
 Logic/UIDataModel/Model/DataStructures/Personel.hpp \
 Logic/UIDataModel/Model/DataStructures/Person.hpp \
 Logic/UIDataModel/Model/DataStructures/Staff.hpp \
 Logic/UIDataModel/RegistrationModel/RegistrationModel.hpp \
 UI/AdminWindow/AdminWindow.hpp \
 UI/DoctorsWindow/DoctorsWindow.hpp \
 UI/LoginWindow/LoginWindow.hpp \
 UI/PatientRegistrationWindow/PatientRegistrationWindow.hpp \
 UI/UIController/Controller/Controller.hpp \
 UI/UIController/VirtualController/VirtualController.hpp

FORMS    += UI/AdminWindow/AdminWindow.ui \
 UI/DoctorsWindow/DoctorsWindow.ui \
 UI/LoginWindow/LoginWindow.ui \
 UI/PatientRegistrationWindow/PatientRegistrationWindow.ui \

RESOURCES += Resources/projectresources.qrc \
    UI/Resources/projectresources.qrc

#DISTFILES +=
