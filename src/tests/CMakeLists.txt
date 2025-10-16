enable_testing()

add_executable(tests
    TestPortfolio.cpp
    TestMarket.cpp
    TestSimulation.cpp
)

target_link_libraries(tests
    PRIVATE
        core
        Qt6::Widgets
)

add_test(NAME PortfolioTests COMMAND tests)
