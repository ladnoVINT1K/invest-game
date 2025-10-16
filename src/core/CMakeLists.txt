add_library(core STATIC
    InvestmentAsset.cpp
    Portfolio.cpp
    MarketModel.cpp
    Metal.cpp
    Deposit.cpp
    Bond.cpp
    GameAPI.cpp
    core.hpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(core PUBLIC utils) # если core использует утилиты
