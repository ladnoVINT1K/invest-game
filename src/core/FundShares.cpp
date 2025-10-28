#include "FundShares.h"

FundShares::FundShares(double initialNAV)
{
    totalUnits_ = initialNAV;
    playerUnits_ = initialNAV;
}

double FundShares::getPricePerUnit(double nav) const {
    if (totalUnits_ <= 0.0) return 0.0;
    return nav / totalUnits_;
}

double FundShares::buyUnits(double money, double nav) {
    double price = getPricePerUnit(nav);
    if (price <= 0.0) return 0.0;

    double unitsBought = money / price;
    totalUnits_ += unitsBought;
    playerUnits_ += unitsBought;
    return unitsBought;
}

double FundShares::sellUnits(double units, double nav) {
    if (units <= 0.0 || units > playerUnits_) return 0.0;

    double price = getPricePerUnit(nav);

    double payout = price * units;
    playerUnits_ -= units;
    totalUnits_ -= units;

    return payout;
}
