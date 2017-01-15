project(LoginWindowLib)

set (LoginWindowHPP
        LoginWindow.h)

set (LoginWindowSRC
        LoginWindow.cpp)

include_directories( . )

qt5_wrap_cpp(LoginWindowHPPwrapped ${LoginWindowHPP})

add_library(LoginWindowLib SHARED
        ${LoginWindowHPPwrapped}
        ${LoginWindowSRC})

target_link_libraries (LoginWindowLib VirtualController Qt5::Widgets)
