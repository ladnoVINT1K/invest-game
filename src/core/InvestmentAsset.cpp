#include "InvestmentAsset.h"

double Investment::getProfit() {
    return amount_ * rate_;
}

void Investment::updatePrice(const MarketModel& market) {
    
}