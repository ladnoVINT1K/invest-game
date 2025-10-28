#pragma once
#include "MarketModel.h"
#include "Portfolio.h"
#include <vector>
#include <string>
#include <functional>

class Simulation {
public:
    struct Snapshot {
        int month;
        double capital;
        double profit;
    };

    Simulation(double initialCapital = 100000.0, double taxRate = 0.17);

    // === Управление временем ===
    void nextStep();             // следующий месяц
    void runSteps(int count);    // несколько месяцев
    void reset();                // сброс симуляции

    // === Доступ к данным ===
    const MarketModel& getMarket() const { return market_; }
    const Portfolio& getPortfolio() const { return portfolio_; }
    Portfolio& getPortfolio() { return portfolio_; } // cursed 
    const std::vector<Snapshot>& getHistory() const { return history_; }

    int getCurrentMonth() const { return month_; }
    bool isPaused() const { return paused_; }

    // === Игровые действия ===
    void buy(const std::string& symbol, double amount);
    void sell(const std::string& symbol, double amount);

    // === Контроль ===
    void togglePause(bool p) { paused_ = p; }

    // === События (UI-обратные вызовы) ===
    void onUpdate(std::function<void(const Snapshot&)> callback);

private:
    MarketModel market_;
    Portfolio portfolio_;

    int month_ = 0;
    bool paused_ = false;

    std::vector<Snapshot> history_;
    std::function<void(const Snapshot&)> updateCallback_;
};
