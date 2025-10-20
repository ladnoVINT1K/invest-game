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

std::vector<MarketAsset> GameAPI::getMarketAssets() const {
    std::vector<MarketAsset> result;
    for (const auto& [symbol, state] : sim_.getMarket().getAll()) {
        result.push_back({symbol, state.price, state.trend, state.volatility});
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

GameAPI::Forecast GameAPI::predictPrice(const std::string& symbol, int steps) const {
    auto prediction = sim_.getMarket().predictPrice(symbol, steps);
    Forecast f;
    f.symbol = symbol;
    f.expected = prediction.expected;
    f.min = prediction.min;
    f.max = prediction.max;
    return f;
}

double GameAPI::getCurrentPrice(const std::string& symbol) const {
    try {
        return sim_.getMarket().getPrice(symbol);
    } catch (...) {
        return 0.0;
    }
}

bool GameAPI::isGrowing(const std::string& symbol) const {
    const auto& dq = sim_.getMarket().getCandles(symbol);
    if (dq.size() < 2)
        return false; // недостаточно данных

    const auto& last = dq.back();
    const auto& prev = dq[dq.size() - 2];

    return last.close > prev.close;
}
