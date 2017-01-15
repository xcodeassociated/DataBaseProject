project(Controller)

set (ControllerLibHPP
        Controller.h)

set (ControllerLibSRC
        Controller.cpp)

qt5_wrap_cpp(ControllerLibHPPwrapped ${ControllerLibHPP})

add_library(Controller SHARED
        ${ControllerLibHPPwrapped}
        ${ControllerLibSRC})

target_link_libraries(Controller
        VirtualController
        DataModelLib
        AdminWindowLib
        DoctorsWindowLib
        LoginWindowLib
        PRegWindowLib
        Qt5::Widgets)