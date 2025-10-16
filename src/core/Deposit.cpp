#include "Deposit.h"
#include <algorithm>

Deposit::Deposit(const std::string& name, double principal, double annualRate, int termMonths, bool autoRenew)
{
    name_ = name;
    principal_ = principal;
    annualRate_ = annualRate;
    termMonths_ = termMonths;
    monthsPassed_ = 0;
    autoRenew_ = autoRenew;

    amount_ = principal_; 
    lastAmount_ = amount_;
    risk_ = 0.01f; 
    rate_ = annualRate_ / 12.0; 
}

double Deposit::getProfit() {
    return amount_ - lastAmount_;
}

void Deposit::updatePrice(const MarketModel& /*market*/) {
    lastAmount_ = amount_;
    double monthlyRate = annualRate_ / 12.0;
    amount_ = amount_ * (1.0 + monthlyRate);
    rate_ = monthlyRate;

    monthsPassed_ += 1;
    if (monthsPassed_ >= termMonths_) {
        if (autoRenew_) {
            monthsPassed_ = 0; 
        } else {
            // тут можно пометить депозит как "выплаченный" / закрыть / перевести в cash
            // Для простоты — оставим сумму на месте, дальнейшие начисления прекращаются
            // Чтобы прекратить начисления, можно установить annualRate_ = 0.0;
            annualRate_ = 0.0;
            rate_ = 0.0;
        }
    }
}
