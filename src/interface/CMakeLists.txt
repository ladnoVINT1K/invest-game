add_library(interface
    interface.cpp
    interface.hpp
)

target_link_libraries(interface PUBLIC core)
target_include_directories(interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
