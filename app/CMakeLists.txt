cmake_minimum_required (VERSION 2.8.12)
project (SysMed)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_PREFIX_PATH "/opt/Qt/5.7/gcc_64")
set (CMAKE_PREFIX_PATH "/usr/include")
set (CMAKE_PREFIX_PATH "/usr/lib/")
set (CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")

find_package (Qt5Widgets)
add_definitions(${Qt5Widgets_DEFINITIONS} -ldl)

set(MYSQLCONNECTORCPP_ROOT_DIR
        "${MYSQLCONNECTORCPP_ROOT_DIR}"
        CACHE
        PATH
        "/usr/include"
        "/usr/lib")

find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
        mysql_connection.h
        HINTS
        ${MYSQLCONNECTORCPP_ROOT_DIR}
        PATH_SUFFIXES
        include)

find_library(MYSQLCONNECTORCPP_LIBRARY
        NAMES
        mysqlcppconn
        mysqlcppconn-static
        HINTS
        ${MYSQLCONNECTORCPP_ROOT_DIR}
        PATH_SUFFIXES
        lib64
        lib)

mark_as_advanced(MYSQLCONNECTORCPP_INCLUDE_DIR MYSQLCONNECTORCPP_LIBRARY)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MysqlConnectorCpp
        DEFAULT_MSG
        MYSQLCONNECTORCPP_INCLUDE_DIR
        MYSQLCONNECTORCPP_LIBRARY)

if(MYSQLCONNECTORCPP_FOUND)
    set(MYSQLCONNECTORCPP_INCLUDE_DIRS "${MYSQLCONNECTORCPP_INCLUDE_DIR}") # Add any dependencies here
    set(MYSQLCONNECTORCPP_LIBRARIES "${MYSQLCONNECTORCPP_LIBRARY}") # Add any dependencies here
    mark_as_advanced(MYSQLCONNECTORCPP_ROOT_DIR)
    message("mysqlconnector found!")
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})
link_directories (${PROJECT_SOURCE_DIR})

include_directories( ${PROJECT_SOURCE_DIR}/Logic/UIDataModel )
include_directories( ${PROJECT_SOURCE_DIR}/Logic/UIDataModel/Model )
include_directories( ${PROJECT_SOURCE_DIR}/Logic/UIDataModel/Model/DataStructures )

include_directories(${PROJECT_SOURCE_DIR}/Logic/UIDataModel/AdminModel)
include_directories(${PROJECT_SOURCE_DIR}/Logic/UIDataModel/DoctorsModel)
include_directories(${PROJECT_SOURCE_DIR}/Logic/UIDataModel/LoginModel)
include_directories(${PROJECT_SOURCE_DIR}/Logic/UIDataModel/RegistrationModel)

include_directories(${PROJECT_SOURCE_DIR}/UI/AdminWindow)
include_directories(${PROJECT_SOURCE_DIR}/UI/DoctorsWindow)
include_directories(${PROJECT_SOURCE_DIR}/UI/LoginWindow)
include_directories(${PROJECT_SOURCE_DIR}/UI/PatientRegistrationWindow)
include_directories( ${PROJECT_SOURCE_DIR}/UIController/Controller )
include_directories( ${PROJECT_SOURCE_DIR}/UIController/VirtualController )

link_directories( ${PROJECT_SOURCE_DIR}/Logic/UIDataModel )
link_directories(${PROJECT_SOURCE_DIR}/UI/AdminWindow)
link_directories(${PROJECT_SOURCE_DIR}/UI/DoctorsWindow)
link_directories(${PROJECT_SOURCE_DIR}/UI/LoginWindow)
link_directories(${PROJECT_SOURCE_DIR}/UI/PatientRegistrationWindow)
link_directories( ${PROJECT_SOURCE_DIR}/UIController/Controller )
link_directories( ${PROJECT_SOURCE_DIR}/UIController/VirtualController )


set (${PROJECT_NAME}_res
        ${PROJECT_SOURCE_DIR}/Resources/projectresources.qrc)

set (main_dir ${PROJECT_SOURCE_DIR}/main.cpp)


add_subdirectory (${PROJECT_SOURCE_DIR}/UIController)
add_subdirectory (${PROJECT_SOURCE_DIR}/Logic)
add_subdirectory (${PROJECT_SOURCE_DIR}/UI)

add_executable(${PROJECT_NAME} ${main_dir})

target_link_libraries (${PROJECT_NAME}
        Controller
        Qt5::Widgets)
