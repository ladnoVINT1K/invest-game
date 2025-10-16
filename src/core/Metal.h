#pragma once
#include "InvestmentAsset.h"
#include <string>

class MarketModel; 

class Metal : public Investment {
public:
    Metal(const std::string& name, double quantity, double initPrice, float risk = 0.2f);

    double getProfit() override;
    void updatePrice(const MarketModel& market) override;

    double quantity() const { return quantity_; }
    double lastPrice() const { return lastPrice_; }

private:
    double quantity_;    // количество слитков/единиц
    double lastPrice_;   // цена за единицу на предыдущем шаге
    double lastAmount_;  // для вычисления getProfit()
};
