#include "src/core/core.hpp"
#include <iostream>

signed main(void) {
    GameAPI api;
    api.buy("BOND", 1000);
    auto Predict = api.predictPrice("BOND", 3);
    for (int i = 0; i < 12; ++i) api.nextStep();
    api.sell("BOND", 20000);
    std::cout << "Symb:" << Predict.symbol << " | " 
              << Predict.min << " | " 
              << Predict.max << " | " 
              << Predict.expected << std::endl;
    std::cout << api.getCurrentPrice("BOND"); 
}