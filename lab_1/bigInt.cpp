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
  for (int i = 0; i < big_int_.size(); ++i) {
    result.big_int_[i] = ~result.big_int_[i];
  }
  return result;
}

BigInt &BigInt::operator^=(const BigInt &other) {
  for (int i = big_int_.size() - 1, j = other.big_int_.size() - 1; i >= 0;
       --i, --j) {
    if (j >= 0) {
      big_int_[i] = big_int_[i] ^ other.big_int_[j];
    } else {
      break;
    }
  }

  return *this;
}

// BigInt &BigInt::operator%=(const BigInt &);

BigInt &BigInt::operator&=(const BigInt &other) {
  for (int i = big_int_.size() - 1, j = other.big_int_.size() - 1; i >= 0;
       --i, --j) {
    if (j >= 0) {
      big_int_[i] = big_int_[i] & other.big_int_[j];
    } else {
      big_int_[i] = 0;
    }
  }
  return *this;
}

BigInt &BigInt::operator|=(const BigInt &other) {
  for (int i = big_int_.size() - 1, j = other.big_int_.size() - 1; i >= 0;
       --i, --j) {
    if (j >= 0) {
      big_int_[i] = big_int_[i] | other.big_int_[j];
    } else {
      break;
    }
  }
  return *this;
}

BigInt &BigInt::operator++() {
  for (int i = big_int_.size() - 1; i >= 0; --i) {
    if (big_int_[i] == 1) {
      big_int_[i] = 0;
      if (!i) big_int_.insert(big_int_.begin(), 1);
    } else {
      big_int_[i] = 1;
      break;
    }
  }
  return *this;
}

const BigInt BigInt::operator++(int) const {
  BigInt old(*this);
  std::cout << "HERE" << old[0] << " " << old[1] << std::endl;
  ++old;
  return old;
}

BigInt &BigInt::operator--() {
  for (int i = big_int_.size() - 1; i >= 0; --i) {
    if (!big_int_[i]) {
      big_int_[i] = 1;
      // if (!i) big_int_.insert(big_int_.begin(), 1);
    } else {
      big_int_[i] = 0;
      if (!i) {
        while (!big_int_[i]) {
          big_int_.erase(big_int_.begin());
          ++i;
        }
      }
      break;
    }
  }
  return *this;
}

const BigInt BigInt::operator--(int) const {
  BigInt old(*this);
  std::cout << "HERE" << old[0] << " " << old[1] << std::endl;
  --old;
  return old;
}

bool BigInt::operator<(const BigInt &other) const {
  if (big_int_.size() < other.big_int_.size()) {
    return 1;
  } else if (big_int_.size() > other.big_int_.size()) {
    return 0;
  } else {
    for (int i = big_int_.size() - 1; i >= 0; --i) {
      if (big_int_[i] > other.big_int_[i])
        return 1;
      else if (big_int_[i] < other.big_int_[i])
        return 0;
    }
  }
  return 0;
}

bool BigInt::operator!=(const BigInt &other) const {
  if (big_int_.size() != other.big_int_.size()) {
    return 1;
  } else {
    for (int i = big_int_.size() - 1; i >= 0; --i) {
      if (big_int_[i] != other.big_int_[i]) return 1;
    }
  }
  return 0;
}

bool BigInt::operator==(const BigInt &other) const { return !(*this != other); }

bool BigInt::operator>(const BigInt &other) const { return other < *this; }

bool BigInt::operator<=(const BigInt &other) const { return !(other < *this); }

bool BigInt::operator>=(const BigInt &other) const { return !(*this < other); }

BigInt &BigInt::operator+=(const BigInt &other) {
  bool res, buf;
  for (int i = big_int_.size() - 1, j = other.big_int_.size() - 1; j >= 0;
       --i, --j) {
    std::cout << j << " ";
    bool bit1 = big_int_[i], bit2 = other.big_int_[j];
    if (!i) {
      res = bit2;
      if (buf) {
        res = (bit1 + bit2 + buf) % 2;
        buf = (bit1 + bit2 + buf) / 2;
      }
      big_int_.insert(big_int_.begin(), res);
    } else {
      res = (bit1 + bit2 + buf) % 2;
      buf = (bit1 + bit2 + buf) / 2;
    }
  }
  return *this;
}
