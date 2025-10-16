#pragma once
#include <map>
#include <string>
#include <deque>

struct AssetState {
    double price;      // текущая цена
    double trend;      // средний рост/падение
    double volatility; // «нервность» актива
};

struct Candle {
    double open;
    double close;
    double high;
    double low;
};

class MarketModel {
public:
    MarketModel();

    void update();

    double getPrice(const std::string& symbol) const;
    double getTrend(const std::string& symbol) const;
    double getVolatility(const std::string& symbol) const;

    const std::deque<Candle>& getCandles(const std::string& symbol) const;

    const std::map<std::string, AssetState>& getAll() const { return assets; }
    struct PriceForecast {
        double expected; // ожидаемая цена
        double min;      // нижняя граница (примерно -1σ)
        double max;      // верхняя граница (+1σ)
    };

    PriceForecast predictPrice(const std::string& symbol, int n = 1) const;

private:
    std::map<std::string, AssetState> assets;
    std::map<std::string, std::deque<Candle>> candles;

    short maxCandles = 100;
};
