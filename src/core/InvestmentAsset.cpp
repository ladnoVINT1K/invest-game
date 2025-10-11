#include "InvestmentAsset.h"
#include "MarketModel.h"
#include <algorithm>
#include <cmath>

double Investment::getProfit() {
    return amount_ * rate_;
}

void Investment::updatePrice(const MarketModel& market) {
    try {
        double marketTrend = market.getTrend(name_);
        double marketVolatility = market.getVolatility(name_);
        double marketPrice = market.getPrice(name_);

        rate_ += (marketTrend - rate_) * 0.1;  // немного приближается к тренду
        rate_ += (marketVolatility * risk_) * ( (rand() % 200 - 100) / 1000.0 );

        rate_ = std::clamp(rate_, -0.5f, 0.5f);

        amount_ *= (1.0 + rate_);
    }
    catch (...) {
        // если MarketModel не знает актив — ничего не делаем
    }
}
