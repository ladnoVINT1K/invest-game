#pragma once
#include "InvestmentAsset.h"

class MarketModel; // forward

class Bond : public Investment {
public:
    // faceValue = номинал одной облигации, count = число облигаций,
    // couponRate - годовой купон в долях (0.08 = 8%)
    Bond(const std::string& name, double faceValue, int count, double couponRate, int monthsToMaturity);

    double getProfit() override;
    void updatePrice(const MarketModel& market) override;

    int monthsRemaining() const { return monthsToMaturity_; }

private:
    double faceValue_;
    int count_;
    double couponRate_;
    int monthsToMaturity_;
    double lastAmount_;
};
