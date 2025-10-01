#include <iostream>
#include <string>

class Investment {
 public:
  Investment(std::string name, double amount);
  virtual ~Investment() = default;

  /* getters */
  std::string getName(void) const;
  double getAmount(void) const;

  /* setters */
  void addSome(double a);
  void takeSome(double t);

  /* main logic */
  virtual double calculateMonthlyReturn() const = 0;
  virtual void updatePrice(double newPrice) = 0; 

 protected:
  std::string name_;
  double amount_;
};