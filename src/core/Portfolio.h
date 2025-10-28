#pragma once
#include <memory>
#include <vector>
#include <string>
#include <numeric>
#include "InvestmentAsset.h"
#include "MarketModel.h"
#include "FundShares.h"

class Portfolio {
public:
    Portfolio(double initialCapital = 0.0, double taxRate = 0.0);

    // Добавить актив
    void addInvestment(std::shared_ptr<Investment> inv);

    // Обновить все активы с учётом рынка
    void updateAll(const MarketModel& market);

    // Посчитать суммарную прибыль (до налогообложения)
    double computeProfit() const;

    // Уплатить налог с прибыли (возвращает удержанную сумму)
    double applyTax();

    // Общая стоимость портфеля (капитал)
    double totalValue() const;

    // Доступ к отдельным активам
    const std::vector<std::shared_ptr<Investment>>& getInvestments() const { return investments_; }

    // Добавление/снятие капитала (приток/отток паёв)
    void addCapital(double amount);
    void withdrawCapital(double amount);

    // Информационные методы
    double getCapital() const { return capital_; }
    double getTaxRate() const { return taxRate_; }

    // Очистка (например, перед реструктуризацией)
    void clear();



    // === exp === DONT USE THIS STUFF ===
    double getFundPricePerUnit() const;
    double getFundUnits() const;
    double getFundTotalUnits() const;
    double buyFundUnits(double money);
    double sellFundUnits(double units);


private:
    std::vector<std::shared_ptr<Investment>> investments_;
    double capital_;     // текущий капитал фонда
    double taxRate_;     // налог на прибыль
    double lastProfit_;  // прибыль за предыдущий шаг
    FundShares fundShares_; // паи фонда
};
