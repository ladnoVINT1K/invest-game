cmake_minimum_required(VERSION 3.16)
project(InvestmentManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Включаем Qt (Widgets + Charts)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

# Пути к подпроектам
add_subdirectory(src/core)
# add_subdirectory(src/utils)
# add_subdirectory(src/ui)
# add_subdirectory(src/tests)

# Главный исполняемый файл
# add_executable(InvestmentManager src/main.cpp)
add_executable(InvestmentManager 
    testGlobal.cpp
    src/ui/MainWindow.cpp 
    src/ui/MarketWindow.cpp
    src/ui/AssetWindow.cpp 
)

# Линкуем с нашими библиотеками
target_link_libraries(InvestmentManager
    PRIVATE
        core
        Qt6::Widgets
        Qt6::Charts
        Qt6::Gui
        Qt6::Core
)

# Пути к заголовочным
target_include_directories(InvestmentManager PRIVATE
    src/core
    src/utils
    src/ui
)
