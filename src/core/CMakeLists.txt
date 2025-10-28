# Включаем -fPIC ДО объявления библиотеки
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(core STATIC
    InvestmentAsset.cpp
    Portfolio.cpp
    MarketModel.cpp
    Metal.cpp
    Deposit.cpp
    Bond.cpp
    GameAPI.cpp
    Simulation.cpp
    core.hpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(core PUBLIC utils) # если core использует утилиты
