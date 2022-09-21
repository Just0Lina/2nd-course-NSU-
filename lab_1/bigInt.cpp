#include "bigInt.h"

#include <algorithm>

BigInt::BigInt(const int number) : sign_(number >= 0) {
  int tmp_number = number >= 0 ? number : number * (-1);
  for (; tmp_number; tmp_number /= 2) {
    big_int_.insert(big_int_.begin(), tmp_number % 2);
  }
}

BigInt::BigInt(std::string number) : sign_(number[0] != '-') {
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

BigInt::BigInt(const BigInt &other)
    : big_int_(other.big_int_), sign_(other.sign_) {}

BigInt::BigInt(BigInt &&other) : big_int_(other.big_int_), sign_(other.sign_) {}

BigInt &BigInt::operator=(const BigInt &other) {
  if (this == &other) {
    throw std::invalid_argument("You are trying to assign the same");
  }
  if (big_int_.size() != other.big_int_.size())  // resource cannot be
  {
    big_int_.resize(other.big_int_.size());
  }
  big_int_ = std::move(other.big_int_);
  sign_ = std::move(other.sign_);

  return *this;
}

BigInt &BigInt::operator=(BigInt &&other) {
  if (this == &other)
    big_int_.clear();
  else
    big_int_ = std::move(other.big_int_);
  return *this;
}

bool BigInt::operator[](size_t pos) { return big_int_[pos]; }

const bool BigInt::operator[](size_t pos) const { return big_int_[pos]; }

bool BigInt::empty() { return big_int_.empty(); }

BigInt BigInt::operator~() const {
  BigInt result(*this);
  for (int i = 0; i < big_int_.size(); ++i) {
    result.big_int_[i] = result.big_int_[i] ? 0 : 1;
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

void BigInt::mini_dec(std::vector<bool> &big_int_) {
  for (int i = big_int_.size() - 1; i >= 0; --i) {
    if (!big_int_[i]) {
      big_int_[i] = 1;
      if (!i) big_int_.insert(big_int_.begin(), 1);
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
}

void BigInt::mini_inc(std::vector<bool> &big_int_) {
  for (int i = big_int_.size() - 1; i >= 0; --i) {
    if (big_int_[i] == 1) {
      big_int_[i] = 0;
      if (!i) big_int_.insert(big_int_.begin(), 1);
    } else {
      big_int_[i] = 1;
      break;
    }
  }
}

const BigInt BigInt::operator++(int) {
  BigInt old(*this);
  ++*this;
  return old;
}

BigInt &BigInt::operator++() {
  if (sign_) {
    mini_inc(big_int_);
  } else {
    mini_dec(big_int_);
  }
  return *this;
}
BigInt &BigInt::operator--() {
  if (sign_) {
    mini_dec(big_int_);
  } else {
    mini_inc(big_int_);
  }
  return *this;
}

const BigInt BigInt::operator--(int) {
  BigInt old(*this);
  --*this;
  return old;
}

bool BigInt::operator<(const BigInt &other) const {
  if (sign_ < other.sign_) return 1;
  if (sign_ > other.sign_) return 0;
  if (sign_) return is_less(other);
  return other.is_less(*this);
  return 0;
}

bool BigInt::operator!=(const BigInt &other) const {
  if (big_int_.size() != other.big_int_.size() || sign_ != other.sign_) {
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

void BigInt::minisum(const BigInt &other) {
  bool res = 0, buf = 0;
  for (int i = big_int_.size() - 1, j = other.big_int_.size() - 1;
       j >= 0 || i >= 0 || buf; --i, --j) {
    if (i >= 0 && j >= 0) {
      bool bit1 = big_int_[i], bit2 = other.big_int_[j];
      big_int_[i] = (bit1 + bit2 + buf) % 2;
      buf = (bit1 + bit2 + buf) / 2;
    } else if (j >= 0) {
      bool bit2 = other.big_int_[j];
      res = bit2;
      if (buf) {
        res = (bit2 + buf) % 2;
        buf = (bit2 + buf) / 2;
      }
      big_int_.insert(big_int_.begin(), res);
    } else if (i >= 0) {
      bool bit1 = big_int_[i];
      if (buf) {
        big_int_[i] = (bit1 + buf) % 2;
        buf = (bit1 + buf) / 2;
      }
    } else {
      big_int_.insert(big_int_.begin(), buf);
      buf = 0;
    }
  }
}

void BigInt::minisub(const BigInt &other) {
  BigInt tmp(other);
  while (tmp.big_int_.size() < big_int_.size()) {
    tmp.big_int_.insert(big_int_.begin(), 0);
  }
  tmp = ~tmp;
  ++tmp;
  minisum(tmp);
}

bool BigInt::is_less(const BigInt &other) const {
  int size1 = big_int_.size(), size2 = other.big_int_.size();
  if (size1 < size2) return 1;
  if (size1 > size2) return 0;
  for (int i = 0; i < size1; ++i) {
    if (big_int_[i] < other.big_int_[i])
      return 1;
    else if (big_int_[i] > other.big_int_[i])
      return 0;
  }
  return 0;
}

BigInt &BigInt::operator+=(const BigInt &other) {
  if (sign_ == other.sign_) {
    // std::cout << "HEEERE" << std::endl;
    minisum(other);
  } else {
    // bool tmp_sign = is_less(other) ? other.sign_ : sign_;
    // std::cout << "HEEERE" << sign_ << std::endl;
    // if (sign_) {
    //   BigInt tmp(~other);

    //   minisum(tmp);
    // } else {
    //   for (int i = 0; i < big_int_.size(); ++i) {
    //     std::cout << (*this)[i] << " ";
    //   }
    //   std::cout << std::endl;
    //   // *this ~ = *this;
    //   BigInt tmp(*this);
    //   tmp = ~tmp;

    //   for (int i = 0; i < tmp.big_int_.size(); ++i) {
    //     std::cout << tmp.big_int_[i] << " ";
    //   }
    //   minisum(other);
    // }
    // sign_ = tmp_sign;

    if (is_less(other)) {
      std::cout << "HERE" << std::endl;
      BigInt tmp(other);
      tmp.minisub(*this);
    } else {
      minisub(other);
    }
  }
  return *this;
}

BigInt &BigInt::operator-=(const BigInt &other) {
  if (sign_ && !other.sign_)
    minisum(other);
  else if (sign_ == other.sign_) {
    sign_ = is_less(other) ? !sign_ : sign_;
    BigInt tmp(~other);
    minisum(tmp);
  } else {
    ~*this;
    minisum(other);
  }
  return *this;
}
