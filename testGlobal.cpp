#include "src/core/core.hpp"
#include <iostream>

signed main(void) {
    GameAPI api;
    api.buy("GOLD", 10000);
    api.nextStep();

    for (auto& c : api.getCandles("GOLD"))
        std::cout << "O:" << c.open << " C:" << c.close << std::endl;

}