#pragma once
#include "InvestmentAsset.h"
#include "MarketModel.h"

class Stock : public Investment {
public:
    Stock(const std::string& name, double amount, float risk = 0.2)
    {
        name_ = name;
        amount_ = amount;
        risk_ = risk;
        rate_ = 0.0;
    }

    double getProfit() override {
        return amount_ * rate_;
    }

    void updatePrice(const MarketModel& market) override {
        double trend = market.getTrend(name_);
        double volatility = market.getVolatility(name_);
        double change = trend + volatility * ((rand() % 200 - 100) / 1000.0);
        rate_ = change;
        amount_ *= (1.0 + rate_);
    }
};
