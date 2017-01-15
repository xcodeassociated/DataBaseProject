project(DataModelLib)

set (DataModelLibHPP
        Model.h)

set (DataModelLibSRC
        Model.cpp)

qt5_wrap_cpp(DataModelLibHPPwrapped ${DataModelLibHPP})

add_library(DataModelLib SHARED
        ${DataModelLibHPPwrapped}
        ${DataModelLibSRC})

target_link_libraries(DataModelLib
        VirtualController
        Qt5::Widgets)