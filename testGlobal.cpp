#include "src/core/core.hpp"
#include <iostream>

signed main(void) {
    GameAPI api;
    api.buy("GOLD", 10000);
    api.buy("SILVER", 1000);
    auto Predict = api.predictPrice("GOLD", 3);
    api.nextStep();
    api.nextStep();
    api.nextStep();
    
    std::cout << "Symb:" << Predict.symbol << " | " 
              << Predict.min << " | " 
              << Predict.max << " | " 
              << Predict.expected << std::endl;
    std::cout << api.getCurrentPrice("GOLD"); 
    
}