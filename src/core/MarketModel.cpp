#include "MarketModel.h"
#include <random>
#include <cmath>
#include <algorithm>
MarketModel::MarketModel() {
    // Металлы (3)
    assets["GOLD"] = {4037.0, 0.0005, 0.02};
    assets["SILVER"] = {28.5, 0.0008, 0.035};
    assets["PLATINUM"] = {1025.0, 0.0006, 0.028};    
    // Облигации BOND (18)
    assets["US10YBOND"] = {1000.0, 0.0003, 0.025};
    assets["BOND_EUR"] = {950.0, 0.00025, 0.022};
    assets["CORPBOND"] = {1025.0, 0.00035, 0.028};
    assets["RUSGBOND"] = {980.0, 0.00028, 0.026};
    assets["EMERGINGBOND"] = {975.0, 0.0004, 0.032};
    assets["TREASURYBOND"] = {1010.0, 0.00022, 0.020};
    assets["MUNIBOND"] = {990.0, 0.00032, 0.024};
    assets["HIGHYIELDBOND"] = {960.0, 0.00045, 0.038};
    assets["GOVBOND"] = {995.0, 0.00027, 0.023};
    assets["CORPBOND2"] = {1015.0, 0.00033, 0.027};
    assets["EUROBOND"] = {970.0, 0.00029, 0.021};
    assets["JUNK BOND"] = {920.0, 0.00055, 0.045};
    assets["SHORTBOND"] = {1005.0, 0.00020, 0.018};
    assets["LONGBOND"] = {985.0, 0.00038, 0.030};
    assets["INFLBOND"] = {1020.0, 0.00026, 0.019};
    assets["GREENBOND"] = {1002.0, 0.00031, 0.023};
    assets["CORPBOND3"] = {998.0, 0.00036, 0.029};
    assets["SOVBOND"] = {992.0, 0.00024, 0.022};
    
    // депозиты
    assets["GOOGLE DEP"] = {30.0, 0.0002, 0.022};
    assets["SAVINGS_DEP"] = {4.5, 0.0001, 0.008};
    assets["ONCALL_DEP"] = {3.5, 0.00015, 0.012};
    assets["FIXED_DEP_3M"] = {5.2, 0.00012, 0.010};
    assets["CORP_DEP"] = {4.8, 0.00018, 0.015};
    assets["TERM_DEP_6M"] = {5.8, 0.00011, 0.009};
    assets["LIQUID_DEP"] = {3.2, 0.00016, 0.013};
    assets["MONTHLY_DEP"] = {5.5, 0.00013, 0.011};
    assets["YEAR_DEP"] = {6.5, 0.00009, 0.007};
    assets["SHORT_DEP"] = {4.2, 0.00014, 0.011};
    assets["BUSINESS_DEP"] = {5.0, 0.00017, 0.014};
    assets["PRIORITY_DEP"] = {7.0, 0.00010, 0.008};
    assets["SPECIAL_DEP"] = {6.2, 0.00012, 0.010};
    assets["FIXED_DEP_1M"] = {3.8, 0.00019, 0.016};
    assets["TERM_DEP_12M"] = {7.2, 0.00008, 0.006};
    assets["PREMIUM_DEP"] = {7.5, 0.00007, 0.005};
    assets["DAILY_DEP"] = {2.8, 0.00020, 0.017};
    assets["QUARTER_DEP"] = {6.0, 0.00010, 0.009};
    assets["ELITE_DEP"] = {8.0, 0.00006, 0.004};
    assets["CORP_DEP2"] = {5.5, 0.00016, 0.013};
    assets["FLEX_DEP"] = {4.0, 0.00013, 0.010};
    assets["STANDARD_DEP"] = {3.5, 0.00011, 0.009};
    assets["PRO_DEP"] = {6.8, 0.00009, 0.007};
    assets["RAPID_DEP"] = {4.6, 0.00015, 0.012};
    assets["SECURE_DEP"] = {6.4, 0.00010, 0.008};
}


// void MarketModel::update() {
//     static std::random_device rd;
//     static std::mt19937 gen(rd());
//     static std::normal_distribution<> normalDist(0, 1);
//     static std::uniform_real_distribution<> jumpDist(0.0, 1.0);

//     double dt = 15.0; // шаг

//     for (auto& [symbol, state] : assets) {
//         Candle newCandle;
//         newCandle.open = state.price;

//         // 1. GBM: drift + stochastic + seasonal
//         double Z = normalDist(gen);
//         double drift = state.trend;
//         double diffusion = state.volatility * Z;
//         double seasonal = 0.01 * sin(2 * 3.14159 * dt / 365.0);

//         // 2. Случайный скачок (1% шанс, ±5%)
//         double jump = 0.0;
//         if (jumpDist(gen) < 0.01) {
//             jump = state.price * ((jumpDist(gen) - 0.5) * 0.1);
//         }

//         // 3. Обновление цены
//         state.price = state.price * exp(drift * dt - 0.5 * state.volatility * state.volatility + diffusion + seasonal) + jump;
//         state.price = std::max(state.price, 0.01);
//         newCandle.close = state.price;

//         // 4. High / Low за день
//         newCandle.high = std::max(newCandle.open, newCandle.close) + 5 * state.volatility;
//         newCandle.low  = std::min(newCandle.open, newCandle.close) - 5 * state.volatility;

//         // 5. Добавляем свечу в очередь
//         auto& dequeC = candles[symbol];
//         dequeC.push_back(newCandle);
//         if (dequeC.size() > maxCandles) dequeC.pop_front();
//     }
// }

void MarketModel::update() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<> normalDist(0, 1);
    static std::uniform_real_distribution<> jumpDist(0.0, 1.0);

    double dt = 30.0;  // ✅ МЕСЯЦ вместо дня! Вот твоя ошибка!

    for (auto& [symbol, state] : assets) {
        Candle newCandle;
        newCandle.open = state.price;

        // 1. GBM для МЕСЯЦА
        double Z = normalDist(gen);
        double drift = state.trend * dt;
        double diffusion = state.volatility * sqrt(dt) * Z;  // √dt для волатильности!
        double seasonal = 0.05 * sin(2 * 3.14159 * dt / 365.0);  // Больше сезонность

        // 2. Скачок (2% шанс, ±10% для месяца)
        double jump = 0.0;
        if (jumpDist(gen) < 0.02) {
            jump = state.price * ((jumpDist(gen) - 0.5) * 0.2);
        }

        // 3. Обновление цены
        state.price = state.price * exp(drift - 0.5 * state.volatility * state.volatility * dt + diffusion + seasonal) + jump;
        state.price = std::max(state.price, 0.01);
        newCandle.close = state.price;

        // 4. High/Low (20-60% от тела, НЕСИММЕТРИЧНЫЕ)
        double bodyRange = fabs(newCandle.close - newCandle.open);
        double wickFactorHigh = 0.2 + 0.3 * fabs(normalDist(gen));   // 20-50% от тела ВВЕРХ
        double wickFactorLow  = 0.1 + 0.4 * fabs(normalDist(gen));   // 10-50% от тела ВНИЗ

        newCandle.high = std::max(newCandle.open, newCandle.close) + 
                        bodyRange * wickFactorHigh;

        newCandle.low = std::min(newCandle.open, newCandle.close) - 
                        bodyRange * wickFactorLow;

        newCandle.high = std::max(newCandle.high, std::max(newCandle.open, newCandle.close) * 1.001);
        newCandle.low  = std::min(newCandle.low,  std::min(newCandle.open, newCandle.close) * 0.999);

        // 5. Добавляем свечу
        auto& dequeC = candles[symbol];
        dequeC.push_back(newCandle);
        if (dequeC.size() > maxCandles) dequeC.pop_front();
    }
}


double MarketModel::getPrice(const std::string& symbol) const {
    auto it = assets.find(symbol);
    if(it != assets.end()) return it->second.price;
    return 0.0;
}

double MarketModel::getTrend(const std::string& symbol) const {
    auto it = assets.find(symbol);
    if(it != assets.end()) return it->second.trend;
    return 0.0;
}

double MarketModel::getVolatility(const std::string& symbol) const {
    auto it = assets.find(symbol);
    if(it != assets.end()) return it->second.volatility;
    return 0.0;
}

const std::deque<Candle>& MarketModel::getCandles(const std::string& symbol) const {
    static std::deque<Candle> empty;
    auto it = candles.find(symbol);
    if(it != candles.end()) return it->second;
    return empty;
}

MarketModel::PriceForecast MarketModel::predictPrice(const std::string& symbol, int n) const {
    PriceForecast result{};

    auto it = assets.find(symbol);
    if (it == assets.end() || n <= 0)
        return result;

    const auto& state = it->second;
    double S0 = state.price;
    double mu = state.trend;
    double sigma = state.volatility;

    // Математическое ожидание цены через n шагов
    double expected = S0 * std::exp(mu * n);

    // Стандартное отклонение (разброс)
    double variance = std::exp(sigma * sigma * n) - 1.0;
    double deviation = expected * std::sqrt(variance);

    result.expected = expected;
    result.min = std::max(0.0, expected - deviation);
    result.max = expected + deviation;

    return result;
}
