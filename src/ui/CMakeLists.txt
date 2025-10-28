# src/ui/CMakeLists.txt
# CMake rules for the UI component of InvestmentManager.
# Intended to be added with add_subdirectory(src/ui) from the top-level CMakeLists.

option(BUILD_UI_SHARED "Build UI as shared library" ON)

# Collect sources (adjust patterns or replace with an explicit list if preferred)
file(GLOB_RECURSE UI_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
)
file(GLOB_RECURSE UI_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

if(BUILD_UI_SHARED)
    add_library(ui SHARED ${UI_SOURCES} ${UI_HEADERS})
else()
    add_library(ui STATIC ${UI_SOURCES} ${UI_HEADERS})
endif()

target_include_directories(ui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

# Require a modern C++ standard
target_compile_features(ui PUBLIC cxx_std_17)

# Link to other project targets if they exist (adjust as needed)
if(TARGET core)
    target_link_libraries(ui PUBLIC core)
endif()

# Platform-specific links (example)
if(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(ui PRIVATE Threads::Threads)
endif()

# Optional install rules
install(TARGETS ui
    EXPORT InvestmentManagerTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/InvestmentManager/ui
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

target_link_libraries(ui
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
)
