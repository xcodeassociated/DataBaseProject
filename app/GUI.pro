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
    _BOOST_PATH = /usr/local/boost

    INCLUDEPATH += "$${_BOOST_PATH}/include"
    LIBS += -I "$${_BOOST_PATH}/lib"
    #LIBS += $${_BOOST_PATH}/lib/libboost_system.a
    #LIBS += $${_BOOST_PATH}/lib/libboost_random.a
    #LIBS += $${_BOOST_PATH}/lib/libboost_date_time.a
    #LIBS += $${_BOOST_PATH}/lib/libboost_filesystem.a
    #LIBS += $${_BOOST_PATH}/lib/libboost_signals.a
    #LIBS += $${_BOOST_PATH}/lib/libboost_serialization.a

    LIBS += -L"/usr/local/Cellar/mysql-connector-c++/1.1.8/lib" -lmysqlcppconn

    INCLUDEPATH += "/usr/local/Cellar/mysql-connector-c++/1.1.8/include/" \
                    "/usr/local/Cellar/mysql-connector-c++/1.1.8/include/cppconn"

}

INCLUDEPATH += "Logic/UIDataModel/AdminModel/" \
 "Logic/UIDataModel/DoctorsModel/" \
 "Logic/UIDataModel/LoginModel/" \
 "Logic/UIDataModel/Model" \
 "Logic/UIDataModel/Model/DataStructures/" \
 "Logic/UIDataModel/RegistrationModel/" \
 "UI/AdminWindow/" \
 "UI/DoctorsWindow/" \
 "UI/LoginWindow/" \
 "UI/PatientRegistrationWindow/" \
 "UIController/Controller/" \
 "UIController/VirtualController/"

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
 UIController/Controller/Controller.cpp \
 UIController/VirtualController/VirtualController.cpp

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
 UIController/Controller/Controller.hpp \
 UIController/VirtualController/VirtualController.hpp

FORMS    += UI/AdminWindow/AdminWindow.ui \
 UI/DoctorsWindow/DoctorsWindow.ui \
 UI/LoginWindow/LoginWindow.ui \
 UI/PatientRegistrationWindow/PatientRegistrationWindow.ui \

RESOURCES += Resources/projectresources.qrc

#DISTFILES +=
