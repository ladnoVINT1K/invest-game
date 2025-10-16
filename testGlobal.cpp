#include "src/core/core.hpp"
#include <iostream>

signed main(void) {
    GameAPI api;
    api.buy("GOLD", 10000);
    api.buy("SILVER", 1000);
    api.nextStep();
    api.nextStep();
    api.nextStep();
    

    for (auto& c : api.getCandles("GOLD"))
        std::cout << "O:" << c.open << " C:" << c.close << std::endl;
    std::cout << "\n\n\n";
    for (auto& c : api.getCandles("SILVER"))
        std::cout << "O:" << c.open << " C:" << c.close << std::endl;
    
}