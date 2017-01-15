cmake_minimum_required (VERSION 2.8.12)
project (SysMed)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_PREFIX_PATH "/opt/Qt/5.7/gcc_64")
set (CMAKE_PREFIX_PATH "/usr/include")
set (CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")

find_package (Qt5Widgets)
add_definitions(${Qt5Widgets_DEFINITIONS} -ldl)

set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})
link_directories (${PROJECT_SOURCE_DIR})

include_directories( ${PROJECT_SOURCE_DIR}/Logic/UIDataModel )
include_directories( ${PROJECT_SOURCE_DIR}/UICode/AdminWindow)
include_directories( ${PROJECT_SOURCE_DIR}/UICode/DoctorsWindow )
include_directories( ${PROJECT_SOURCE_DIR}/UICode/LoginWindow )
include_directories( ${PROJECT_SOURCE_DIR}/UICode/PatientRegistrationWindow )
include_directories( ${PROJECT_SOURCE_DIR}/UIController/Controller )
include_directories( ${PROJECT_SOURCE_DIR}/UIController/VirtualController )

link_directories( ${PROJECT_SOURCE_DIR}/Logic/UIDataModel )
link_directories( ${PROJECT_SOURCE_DIR}/UICode/AdminWindow)
link_directories( ${PROJECT_SOURCE_DIR}/UICode/DoctorsWindow )
link_directories( ${PROJECT_SOURCE_DIR}/UICode/LoginWindow )
link_directories( ${PROJECT_SOURCE_DIR}/UICode/PatientRegistrationWindow )
link_directories( ${PROJECT_SOURCE_DIR}/UIController/Controller )
link_directories( ${PROJECT_SOURCE_DIR}/UIController/VirtualController )


set (${PROJECT_NAME}_res
        ${PROJECT_SOURCE_DIR}/Resources/projectresources.qrc)

set (main_dir ${PROJECT_SOURCE_DIR}/main.cpp)


add_subdirectory (${PROJECT_SOURCE_DIR}/UIController)
add_subdirectory (${PROJECT_SOURCE_DIR}/Logic)
add_subdirectory (${PROJECT_SOURCE_DIR}/UICode)

add_executable(${PROJECT_NAME} ${main_dir})

target_link_libraries (${PROJECT_NAME}
        Controller
        Qt5::Widgets)
