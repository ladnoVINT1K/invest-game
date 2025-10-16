#pragma once
#include <string>
#include <vector>
#include <map>
#include "MarketModel.h"
#include "Portfolio.h"
#include "InvestmentAsset.h"

class GameAPI {
public:
    GameAPI(double startCapital = 100000.0, double taxRate = 0.17);

    // ====== РЫНОК ======
    // Получить список всех активов и их параметры
    std::vector<std::map<std::string, double>> getMarketAssets() const;

    // Получить свечи по символу
    std::vector<Candle> getCandles(const std::string& symbol) const;

    // ====== ПОРТФЕЛЬ ======
    std::vector<std::map<std::string, double>> getPortfolio() const;
    double getCapital() const;
    double getProfit() const;

    // ====== ИГРОВЫЕ ДЕЙСТВИЯ ======
    void buy(const std::string& symbol, double amount);
    void sell(const std::string& symbol, double amount);

    // Один шаг симуляции (1 месяц)
    void nextStep();

    // Сбросить всё
    void reset();

private:
    MarketModel market_;
    Portfolio portfolio_;
    int monthCounter_;
};
