project(VirtualController)

set (VirtualControllerLibSRC
        VirtualController.cpp)

set (VirtualControllerLibHPP
        VirtualController.hpp)

qt5_wrap_cpp(VirtualControllerLibHPPwrapped ${VirtualControllerLibHPP})

add_library(VirtualController SHARED
        ${VirtualControllerLibHPPwrapped}
        ${VirtualControllerLibSRC})

target_link_libraries(VirtualController Qt5::Widgets)