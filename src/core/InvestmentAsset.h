#pragma once
#include "MarketModel.h"
#include <string>

class Investment {
 public:
  virtual double getProfit();
  virtual void updatePrice(const MarketModel& market);
 protected:
  std::string name_;
  double amount_;
  float risk_, rate_;
};