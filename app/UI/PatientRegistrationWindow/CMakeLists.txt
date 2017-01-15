project(PRegWindowLib)

set (PRegWindowHPP
        PatientRegistrationWindow.h)

set (PRegWindowSRC
        PatientRegistrationWindow.cpp)

set (CMAKE_PREFIX_PATH "/opt/Qt/5.7/gcc_64")
find_package(Qt5Widgets)

qt5_wrap_cpp(PRegWindowHPPwrapped ${PRegWindowHPP})

set (${PROJECT_NAME}_ui
        PatientRegistrationWindow.ui)

add_library(PRegWindowLib SHARED
        ${PRegWindowHPPwrapped}
        ${PRegWindowSRC})

target_link_libraries (PRegWindowLib VirtualController Qt5::Widgets)
