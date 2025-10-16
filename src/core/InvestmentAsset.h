#pragma once
#include "MarketModel.h"
#include <string>

class Investment {
 public:
  virtual double getProfit();
  virtual void updatePrice(const MarketModel& market);  
  virtual void reduceAmount(double value);

  double getAmount() const { return amount_; }
  double getRate() const { return rate_; }
  const std::string& getName() const { return name_; }

 protected:
  std::string name_;
  double amount_;
  float risk_, rate_;
};