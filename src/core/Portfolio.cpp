#include "Portfolio.h"
#include <algorithm>
#include <iostream>

Portfolio::Portfolio(double initialCapital, double taxRate)
    : capital_(initialCapital), taxRate_(taxRate), lastProfit_(0.0)
{}

void Portfolio::addInvestment(std::shared_ptr<Investment> inv) {
    investments_.push_back(std::move(inv));
}

void Portfolio::updateAll(const MarketModel& market) {
    // обновляем все активы
    for (auto& inv : investments_) {
        inv->updatePrice(market);
    }

    // считаем общую прибыль
    lastProfit_ = computeProfit();
    // применяем налог
    double taxPaid = applyTax();

    // обновляем капитал
    capital_ = totalValue();

    std::cout << "[Portfolio] Monthly profit: " << lastProfit_
              << " (tax paid: " << taxPaid << "), total: " << capital_ << "\n";
}

double Portfolio::computeProfit() const {
    double profit = 0.0;
    for (const auto& inv : investments_) {
        profit += inv->getProfit();
    }
    return profit;
}

double Portfolio::applyTax() {
    if (lastProfit_ <= 0.0)
        return 0.0; // убыток — налог не взимается

    double tax = lastProfit_ * taxRate_;
    capital_ -= tax; // налог уменьшает общий капитал фонда
    return tax;
}

double Portfolio::totalValue() const {
    double total = 0.0;
    for (const auto& inv : investments_) {
        total += inv->getAmount(); 
    }
    return total;
}

void Portfolio::addCapital(double amount) {
    capital_ += amount;
}

void Portfolio::withdrawCapital(double amount) {
    capital_ = std::max(0.0, capital_ - amount);
}

void Portfolio::clear() {
    investments_.clear();
}
