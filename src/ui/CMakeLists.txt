# qt_wrap_ui(UI_HEADERS
#     MainWindow.ui
#     PortfolioView.ui
#     MarketView.ui
#     SettingsDialog.ui
#     StatsWindow.ui
# )

add_library(ui STATIC
    MainWindow.cpp
    MainWindow.h
    AssetWindow.h
    AssetWindow.cpp
    MarketWindow.h
    MarketWindow.cpp
    # ${UI_HEADERS}
)

target_link_libraries(ui
    PUBLIC
        core
        Qt6::Widgets
        Qt6::Charts
        Qt6::Gui
        Qt6::Core
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
