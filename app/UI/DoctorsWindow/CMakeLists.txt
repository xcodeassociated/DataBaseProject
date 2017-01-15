project(DoctorsWindowLib)

set (DoctorsWindowHPP
        DoctorsWindow.hpp)

set (DoctorsWindowSRC
        DoctorsWindow.cpp)

include_directories( . )

qt5_wrap_cpp(DoctorsWindowHPPwrapped ${DoctorsWindowHPP})

add_library(DoctorsWindowLib SHARED
        ${DoctorsWindowHPPwrapped}
        ${DoctorsWindowSRC})

target_link_libraries (DoctorsWindowLib
        VirtualController
        Qt5::Widgets)
