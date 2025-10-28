#pragma once

class FundShares {
public:
    FundShares(double initialNAV = 10000.0);

    double getTotalUnits() const { return totalUnits_; }
    double getPlayerUnits() const { return playerUnits_; }

    // Цена 1 пая
    double getPricePerUnit(double nav) const;

    // Купить паи на сумму денег
    double buyUnits(double money, double nav);

    // Продать пaи (количество)
    double sellUnits(double units, double nav);

private:
    double totalUnits_;
    double playerUnits_;
};
