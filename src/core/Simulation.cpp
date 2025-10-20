#include "Simulation.h"
#include "Metal.h"
#include "Bond.h"
#include "Deposit.h"
#include <iostream>

Simulation::Simulation(double initialCapital, double taxRate)
    : portfolio_(initialCapital, taxRate)
{
    int prewarmMonths = 12; // 12 месяцев "до игрока"
    for (int i = 0; i < prewarmMonths; ++i) {
        market_.update();
    }
}

void Simulation::nextStep() {
    if (paused_) return;

    ++month_;
    market_.update();
    portfolio_.updateAll(market_);

    double profit = portfolio_.computeProfit();
    double capital = portfolio_.getCapital();

    history_.push_back({month_, capital, profit});

    if (updateCallback_)
        updateCallback_(history_.back());

    std::cout << "[Simulation] Month " << month_ 
              << " | capital=" << capital 
              << " | profit=" << profit << std::endl;
}

void Simulation::runSteps(int count) {
    for (int i = 0; i < count; ++i)
        nextStep();
}

void Simulation::reset() {
    month_ = 0;
    history_.clear();
    market_ = MarketModel();
    portfolio_.clear();
}

void Simulation::buy(const std::string& symbol, double amount) {
    if (amount <= 0.0 || amount > portfolio_.getCapital()) return;

    if (symbol == "GOLD" || symbol == "SILVER") {
        double price = market_.getPrice(symbol);
        double qty = amount / price;
        portfolio_.addInvestment(std::make_shared<Metal>(symbol, qty, price));
        portfolio_.withdrawCapital(amount);
    } else if (symbol.find("BOND") != std::string::npos) {
        portfolio_.addInvestment(std::make_shared<Bond>(symbol, 1000.0, int(amount / 1000.0), 0.08, 12));
        portfolio_.withdrawCapital(amount);
    } else if (symbol.find("DEP") != std::string::npos) {
        portfolio_.addInvestment(std::make_shared<Deposit>(symbol, amount, 0.05, 12));
        portfolio_.withdrawCapital(amount);
    }
}

void Simulation::sell(const std::string& symbol, double amount) {
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

void Simulation::onUpdate(std::function<void(const Snapshot&)> callback) {
    updateCallback_ = std::move(callback);
}
