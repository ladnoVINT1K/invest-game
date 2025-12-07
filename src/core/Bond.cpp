#include "Bond.h"
#include "MarketModel.h"
#include <algorithm>

Bond::Bond(const std::string& name, double faceValue, int count, double couponRate, int monthsToMaturity)
{
    name_ = name;
    faceValue_ = faceValue;
    count_ = count;
    couponRate_ = couponRate;
    monthsToMaturity_ = monthsToMaturity;
    lastAmount_ = 0.0;

    // Изначальная стоимость (если нет рыночной цены, примем номинал)
    amount_ = faceValue_ * count_;
    lastAmount_ = amount_;

    risk_ = 0.05f; // облигации обычно менее рискованны
    rate_ = couponRate_ / 12.0;
}

double Bond::getProfit() {
    return amount_ - lastAmount_; // включает купон и изменение цены
}

void Bond::updatePrice(const MarketModel& market) {
    lastAmount_ = amount_;

    double marketPrice = market.getPrice(name_);
    double positionValueBefore = amount_;  // стоимость до апдейта

    // купон за месяц
    double couponPayment = faceValue_ * (couponRate_ / 12.0) * static_cast<double>(count_);

    // новая рыночная стоимость
    if (marketPrice > 0.0) {
        amount_ = marketPrice * static_cast<double>(count_);
    } else {
        amount_ = faceValue_ * static_cast<double>(count_);
    }
    amount_ += couponPayment;

    if (positionValueBefore > 0.0) {
        rate_ = (amount_ - positionValueBefore) / positionValueBefore;
    } else {
        rate_ = 0.0;
    }

    if (monthsToMaturity_ > 0) {
        monthsToMaturity_ -= 1;
        if (monthsToMaturity_ == 0) {
            amount_ = faceValue_ * static_cast<double>(count_);
            couponRate_ = 0.0;
            rate_ = 0.0;
        }
    }
}
