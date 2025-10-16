#pragma once
#include "InvestmentAsset.h"

class MarketModel; // forward

class Deposit : public Investment {
public:
    // principal - начальная сумма, annualRate - в долях (0.05 = 5%), termMonths - срок вклада
    Deposit(const std::string& name, double principal, double annualRate, int termMonths, bool autoRenew = true);

    double getProfit() override;
    void updatePrice(const MarketModel& /*market*/) override; // не зависит от рынка

    int monthsPassed() const { return monthsPassed_; }
    int term() const { return termMonths_; }

private:
    double principal_;
    double annualRate_;
    int termMonths_;
    int monthsPassed_;
    bool autoRenew_;
    double lastAmount_;
};
