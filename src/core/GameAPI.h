#pragma once
#include "Simulation.h"
#include <string>
#include <vector>
#include <map>

class GameAPI {
public:
    GameAPI(double start = 10000, double tax = 0.17);

    // === Управление симуляцией ===
    void nextStep();
    void reset();

    // === Получение данных ===
    std::vector<Candle> getCandles(const std::string& symbol) const;
    std::vector<std::map<std::string, double>> getPortfolio() const;
    std::vector<std::map<std::string, double>> getMarketAssets() const;
    std::vector<Simulation::Snapshot> getHistory() const;

    double getCapital() const;
    double getProfit() const;

    // === Игровые действия ===
    void buy(const std::string& symbol, double amount);
    void sell(const std::string& symbol, double amount);

private:
    Simulation sim_;
};
