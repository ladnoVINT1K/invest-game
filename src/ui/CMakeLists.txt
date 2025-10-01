find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(gui
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
)

target_link_libraries(gui
    PRIVATE Qt6::Widgets interface
)

target_include_directories(gui
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
