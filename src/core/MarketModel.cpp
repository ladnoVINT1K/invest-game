#include "MarketModel.h"
#include <random>
#include <cmath>
#include <algorithm>

MarketModel::MarketModel() {
    assets["gold"] = {4037.0, 0.0005, 0.02}; // цена, тренд, волатильность
}

void MarketModel::update() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<> normalDist(0, 1);
    static std::uniform_real_distribution<> jumpDist(0.0, 1.0);

    double dt = 1.0; // шаг

    for (auto& [symbol, state] : assets) {
        Candle newCandle;
        newCandle.open = state.price;

        // 1. GBM: drift + stochastic + seasonal
        double Z = normalDist(gen);
        double drift = state.trend;
        double diffusion = state.volatility * Z;
        double seasonal = 0.01 * sin(2 * 3.14159 * dt / 365.0);

        // 2. Случайный скачок (2% шанс, ±5%)
        double jump = 0.0;
        if (jumpDist(gen) < 0.02) {
            jump = state.price * ((jumpDist(gen) - 0.5) * 0.1);
        }

        // 3. Обновление цены
        state.price = state.price * exp(drift * dt - 0.5 * state.volatility * state.volatility + diffusion + seasonal) + jump;
        newCandle.close = state.price;

        // 4. High / Low за день
        newCandle.high = std::max(newCandle.open, newCandle.close) + 5 * state.volatility;
        newCandle.low  = std::min(newCandle.open, newCandle.close) - 5 * state.volatility;

        // 5. Добавляем свечу в очередь
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
