#include "GameAPI.h"
#include "Metal.h"
#include "Bond.h"
#include "Deposit.h"
#include <iostream>

GameAPI::GameAPI(double startCapital, double taxRate)
    : portfolio_(startCapital, taxRate), monthCounter_(0)
{
    // можно проинициализировать несколько активов на старте
    market_ = MarketModel();
}

std::vector<std::map<std::string, double>> GameAPI::getMarketAssets() const {
    std::vector<std::map<std::string, double>> result;
    for (const auto& [symbol, state] : market_.getAll()) {
        result.push_back({
            {"price", state.price},
            {"trend", state.trend},
            {"volatility", state.volatility}
        });
    }
    return result;
}

std::vector<Candle> GameAPI::getCandles(const std::string& symbol) const {
    std::vector<Candle> out;
    try {
        const auto& dq = market_.getCandles(symbol);
        out.assign(dq.begin(), dq.end());
    } catch (...) {}
    return out;
}

std::vector<std::map<std::string, double>> GameAPI::getPortfolio() const {
    std::vector<std::map<std::string, double>> data;
    for (const auto& inv : portfolio_.getInvestments()) {
        data.push_back({
            {"amount", inv->getAmount()},
            {"profit", inv->getProfit()},
            {"rate", inv->getRate()}
        });
    }
    return data;
}

double GameAPI::getCapital() const {
    return portfolio_.getCapital();
}

double GameAPI::getProfit() const {
    return portfolio_.computeProfit();
}

void GameAPI::buy(const std::string& symbol, double amount) {
    // Простейшая логика: добавляем Metal, если золото или акция
    if (symbol == "GOLD" || symbol == "SILVER") {
        double price = market_.getPrice(symbol);
        double quantity = amount / price;
        portfolio_.addInvestment(std::make_shared<Metal>(symbol, quantity, price));
        portfolio_.withdrawCapital(amount);
    } else if (symbol.find("BOND") != std::string::npos) {
        portfolio_.addInvestment(std::make_shared<Bond>(symbol, 1000.0, (int)(amount / 1000.0), 0.08, 12));
        portfolio_.withdrawCapital(amount);
    } else if (symbol.find("DEP") != std::string::npos) {
        portfolio_.addInvestment(std::make_shared<Deposit>(symbol, amount, 0.05, 12));
        portfolio_.withdrawCapital(amount);
    }
}

void GameAPI::sell(const std::string& symbol, double amount) {
    // Простая реализация: ищем актив по имени и вычитаем часть
    auto& invs = const_cast<std::vector<std::shared_ptr<Investment>>&>(portfolio_.getInvestments());
    for (auto it = invs.begin(); it != invs.end();) {
        if ((*it)->getName() == symbol) {
            double cur = (*it)->getAmount();
            if (amount >= cur) {
                portfolio_.addCapital(cur);
                it = invs.erase(it);
            } else {
                portfolio_.addCapital(amount);
                (*it)->reduceAmount(amount);
                ++it;
            }
        } else ++it;
    }
}

void GameAPI::nextStep() {
    monthCounter_++;
    market_.update();
    portfolio_.updateAll(market_);
}

void GameAPI::reset() {
    monthCounter_ = 0;
    portfolio_.clear();
    market_ = MarketModel();
}
