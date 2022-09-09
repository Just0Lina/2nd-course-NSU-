#include "bigInt.h"

#include <algorithm>

BigInt::BigInt(const int number) {
  int tmp_number = number;
  for (; tmp_number; tmp_number /= 2) {
    big_int_.insert(big_int_.begin(), tmp_number % 2);
  }
}

BigInt::BigInt(std::string number) {
  long long bigInt = 0;
  int size = number.size();
  for (int i = 0; i < size; ++i) {
    int value = number[i];
    if (!isdigit(value))
      throw std::invalid_argument("Error: found character is not a digit");
    bigInt = bigInt * 10 + value - '0';
  }
  for (; bigInt; bigInt /= 2) {
    big_int_.push_back(bigInt % 2);
  }
  std::reverse(big_int_.begin(), big_int_.end());
  for (int i = 0; i < big_int_.size(); ++i) {
  }
}

BigInt::BigInt(const BigInt &other) : big_int_(other.big_int_) {}

BigInt::BigInt(BigInt &&other) : big_int_(other.big_int_) {}

BigInt &BigInt::operator=(const BigInt &other) {
  if (this != &other) {
    if (big_int_.size() != other.big_int_.size())  // resource cannot be
    {
      big_int_.resize(other.big_int_.size());
    }
    std::move(other.big_int_);
  }
  return *this;
}

BigInt &BigInt::operator=(BigInt &&other) {
  if (this != &other)
    std::move(other.big_int_);
  else
    big_int_.clear();
  return *this;
}

bool BigInt::operator[](size_t pos) { return big_int_[pos]; }

const bool BigInt::operator[](size_t pos) const { return big_int_[pos]; }
bool BigInt::empty() { return big_int_.empty(); }

BigInt BigInt::operator~() const {
  BigInt result(*this);
  for (size_t i = 0; i < big_int_.size(); ++i) {
    result.big_int_[i] = ~result.big_int_[i];
  }
  return result;
}

BigInt &BigInt::operator^=(const BigInt &other) {
  for (size_t i = 0; i < big_int_.size(); ++i) {
    big_int_[i] = big_int_[i] ^ other.big_int_[i];
  }
  return *this;
}

// BigInt &BigInt::operator%=(const BigInt &);

BigInt &BigInt::operator&=(const BigInt &other) {
  for (size_t i = 0; i < big_int_.size(); ++i) {
    big_int_[i] = big_int_[i] & other.big_int_[i];
  }
  return *this;
}

BigInt &BigInt::operator|=(const BigInt &other) {
  for (size_t i = 0; i < big_int_.size(); ++i) {
    big_int_[i] = big_int_[i] | other.big_int_[i];
  }
  return *this;
}
