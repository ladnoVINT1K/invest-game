#include "GameAPI.h"

GameAPI::GameAPI(double start, double tax)
    : sim_(start, tax)
{}

void GameAPI::nextStep() {
    sim_.nextStep();
}

void GameAPI::reset() {
    sim_.reset();
}

std::vector<Candle> GameAPI::getCandles(const std::string& symbol) const {
    const auto& dq = sim_.getMarket().getCandles(symbol);
    return std::vector<Candle>(dq.begin(), dq.end());
}

std::vector<std::map<std::string, double>> GameAPI::getPortfolio() const {
    std::vector<std::map<std::string, double>> data;
    for (const auto& inv : sim_.getPortfolio().getInvestments()) {
        data.push_back({
            {"amount", inv->getAmount()},
            {"profit", inv->getProfit()},
            {"rate", inv->getRate()}
        });
    }
    return data;
}

std::vector<std::map<std::string, double>> GameAPI::getMarketAssets() const {
    std::vector<std::map<std::string, double>> result;
    for (const auto& [symbol, state] : sim_.getMarket().getAll()) {
        result.push_back({
            {"price", state.price},
            {"trend", state.trend},
            {"volatility", state.volatility}
        });
    }
    return result;
}

std::vector<Simulation::Snapshot> GameAPI::getHistory() const {
    return sim_.getHistory();
}

double GameAPI::getCapital() const {
    return sim_.getPortfolio().getCapital();
}

double GameAPI::getProfit() const {
    return sim_.getPortfolio().computeProfit();
}

void GameAPI::buy(const std::string& symbol, double amount) {
    sim_.buy(symbol, amount);
}

void GameAPI::sell(const std::string& symbol, double amount) {
    sim_.sell(symbol, amount);
}
