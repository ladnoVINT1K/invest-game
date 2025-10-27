#pragma once
#include "Simulation.h"
#include <string>
#include <vector>
#include <map>

struct MarketAsset {
    std::string symbol;
    double price;
    double trend;
    double volatility;
};


class GameAPI {
public:
    GameAPI(double start = 10000, double tax = 0.17);

    // === Управление симуляцией ===
    void nextStep();
    void reset();

    // === Получение данных ===
    std::vector<Candle> getCandles(const std::string& symbol) const;
    std::vector<std::pair<std::string, std::map<std::string, double>>> getPortfolio() const;
    std::vector<MarketAsset> getMarketAssets() const;
    std::vector<Simulation::Snapshot> getHistory() const;

    double getCapital() const;
    double getProfit() const;

    // === Игровые действия ===
    void buy(const std::string& symbol, double amount);
    void sell(const std::string& symbol, double amount);

    // === Прогнозы ===
    struct Forecast {
        std::string symbol;
        double expected;
        double min;
        double max;
    };

    Forecast predictPrice(const std::string& symbol, int steps = 1) const;

    // === Динамика ===
    double getCurrentPrice(const std::string& symbol) const;
    bool isGrowing(const std::string& symbol) const;

private:
    Simulation sim_;
};
