#include "Bond.h"
#include "MarketModel.h"
#include <algorithm>

Bond::Bond(const std::string& name, double faceValue, int count, double couponRate, int monthsToMaturity)
{
    name_ = name;
    faceValue_ = faceValue;
    count_ = count;
    couponRate_ = couponRate;
    monthsToMaturity_ = monthsToMaturity;
    lastAmount_ = 0.0;

    // Изначальная стоимость (если нет рыночной цены, примем номинал)
    amount_ = faceValue_ * count_;
    lastAmount_ = amount_;

    risk_ = 0.05f; // облигации обычно менее рискованны
    rate_ = couponRate_ / 12.0;
}

double Bond::getProfit() {
    return amount_ - lastAmount_; // включает купон и изменение цены
}

void Bond::updatePrice(const MarketModel& market) {
    lastAmount_ = amount_;

    // купон за месяц
    double couponPayment = faceValue_ * (couponRate_ / 12.0) * static_cast<double>(count_);

    // рыночная цена за единицу (если модель даёт цену) — используем для переоценки позиции
    double marketPrice = market.getPrice(name_);
    if (marketPrice > 0.0) {
        amount_ = marketPrice * static_cast<double>(count_);
    } else {
        // если рынка нет — оставим номинал как оценку
        amount_ = faceValue_ * static_cast<double>(count_);
    }

    // прибавляем купон (как денежный приток) — в упрощённой модели купон добавляется к cash,
    // но, чтобы profit показывался, можно временно увеличить amount_ на сумму купона,
    // либо хранить купон отдельно. Здесь добавим купон в amount_ (чтобы getProfit учитывал).
    amount_ += couponPayment;

    rate_ = couponRate_ / 12.0;

    // уменьшение срока
    if (monthsToMaturity_ > 0) {
        monthsToMaturity_ -= 1;
        if (monthsToMaturity_ == 0) {
            // погашение — выплата номинала владельцу
            // В реальной системе нужно переместить сумму в cash портфеля и удалить облигацию.
            // Здесь оставим amount_ равным номиналу * count_ (после погашения можно пометить объект как мёртвый)
            amount_ = faceValue_ * static_cast<double>(count_);
            couponRate_ = 0.0;
            rate_ = 0.0;
        }
    }
}
