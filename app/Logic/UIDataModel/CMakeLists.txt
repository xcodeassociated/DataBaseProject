project(DataModelLib)

set (DataModelLibHPP
        Model/Model.hpp
        AdminModel/AdminModel.hpp
        DoctorsModel/DoctorsModel.hpp
        RegistrationModel/RegistrationModel.hpp
        LoginModel/LoginModel.hpp)

set (DataModelLibSRC
        Model/Model.cpp
        AdminModel/AdminModel.cpp
        DoctorsModel/DoctorsModel.cpp
        RegistrationModel/RegistrationModel.cpp
        LoginModel/LoginModel.cpp)

qt5_wrap_cpp(DataModelLibHPPwrapped ${DataModelLibHPP})

add_library(DataModelLib SHARED
        ${DataModelLibHPPwrapped}
        ${DataModelLibSRC})

target_link_libraries(DataModelLib
        VirtualController
        Qt5::Widgets)