#include "Metal.h"
#include "MarketModel.h"
#include <algorithm>

Metal::Metal(const std::string& name, double quantity, double initPrice, float risk)
{
    name_ = name;
    quantity_ = quantity;
    lastPrice_ = initPrice;
    amount_ = quantity_ * initPrice;
    risk_ = risk;
    rate_ = 0.0;
    lastAmount_ = amount_;
}

double Metal::getProfit() {
    return amount_ - lastAmount_;
}

void Metal::updatePrice(const MarketModel& market) {
    double marketPrice = market.getPrice(name_);

    if (marketPrice <= 0.0) return;

    lastAmount_ = amount_;
    amount_ = quantity_ * marketPrice;

    rate_ = (marketPrice - lastPrice_) / std::max(lastPrice_, 1e-12);

    lastPrice_ = marketPrice;
}
