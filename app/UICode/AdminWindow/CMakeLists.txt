project(AdminWindowLib)

set (AdminWindowHPP
        AdminWindow.h)

set (AdminWindowSRC
        AdminWindow.cpp)

include_directories( . )

qt5_wrap_cpp(AdminWindowLibHPPwrapped ${AdminWindowHPP})

add_library(AdminWindowLib SHARED
        ${AdminWindowLibHPPwrapped}
        ${AdminWindowSRC})

target_link_libraries(AdminWindowLib
        VirtualController
        Qt5::Widgets)