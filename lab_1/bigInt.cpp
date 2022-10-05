#include "bigInt.h"

#include <algorithm>

BigInt::BigInt(const int number) : sign_(number < 0) {
  int tmp_number = number >= 0 ? number : number * (-1);
  for (; tmp_number; tmp_number /= 2) {
    big_int_.insert(big_int_.begin(), tmp_number % 2);
  }
}

BigInt::BigInt(std::string number) : sign_(number[0] == '-') {
  long long bigInt = 0;
  int size = number.size();
  for (int i = sign_; i < size; ++i) {
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
    // throw std::invalid_argument("You are trying to assign the same");
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
bool BigInt::sign() { return sign_; }

BigInt BigInt::operator~() const {
  BigInt result(*this);
  ++result;
  // if (!result.sign_) result.big_int_.erase(result.big_int_.begin());
  result.sign_ = !sign_;
  return result;
}

BigInt BigInt::get_from_ones_comp() const {
  BigInt result(*this);
  std::cout << "FROM" << result.get_number() << std::endl;
  int size = result.size();
  result.sign_ = 0;
  --result;
  if (size != result.size()) result.big_int_.insert(result.big_int_.begin(), 0);
  for (int i = 0; i < result.size(); ++i) {
    result.big_int_[i] = !result.big_int_[i];
  }  // if (!result.sign_)
     // result.big_int_.erase(result.big_int_.begin());
  result.sign_ = 1;
  std::cout << "RES" << result.get_number() << std::endl;
  return result;
}

BigInt BigInt::get_ones_comp() const {
  BigInt result(*this);
  for (int i = 0; i < size(); ++i) {
    result.big_int_[i] = !result.big_int_[i];
  }
  result.sign_ = 0;
  ++result;
  std::cout << "RES" << result.get_number() << std::endl;

  return result;
}

BigInt &BigInt::operator^=(const BigInt &other) {
  BigInt tmp1 = *this, tmp2 = other;
  int size1 = size();
  int size2 = other.size();
  bool all_zero = 1;
  if (sign_) {
    tmp1 = get_ones_comp();
    for (int i = size1; i < size2; ++i)
      tmp1.big_int_.insert(tmp1.big_int_.begin(), 1);
  }
  if (other.sign_) {
    tmp2 = other.get_ones_comp();
    for (int i = size2; i < size1; ++i)
      tmp2.big_int_.insert(tmp2.big_int_.begin(), 1);
  }
  for (int i = tmp1.big_int_.size() - 1, j = tmp2.big_int_.size() - 1;
       i >= 0 || j >= 0; --i, --j) {
    if (j >= 0) {
      if (i >= 0) {
        tmp1.big_int_[i] = tmp1.big_int_[i] ^ tmp2.big_int_[j];
        if (tmp1.big_int_[i]) all_zero = 0;
      } else {
        std::cout << "GGG ";
        tmp1.big_int_.insert(tmp1.big_int_.begin(), tmp2.big_int_[j]);
        if (tmp2.big_int_[j]) all_zero = 0;
      }
    } else {
      if (tmp1.big_int_[i]) {
        all_zero = 0;
        break;
      }
    }
  }
  *this = tmp1;
  sign_ = sign_ ^ other.sign_;
  std::cout << sign_ << "( " << all_zero << " )" << other.sign_ << std::endl;
  if (sign_ && !all_zero)
    *this = get_from_ones_comp();
  else if (sign_)
    big_int_.insert(big_int_.begin(), 1);
  while (!big_int_[0]) {
    big_int_.erase(big_int_.begin());
  }
  return *this;
}

// BigInt &BigInt::operator%=(const BigInt &);

BigInt &BigInt::operator&=(const BigInt &other) {
  bool all_zero = 1, sign1 = sign_, sign2 = other.sign_;
  BigInt tmp1 = *this, tmp2 = other;
  int size1 = size();
  int size2 = other.size();
  std::cout << "HUY " << tmp1.get_number() << " " << tmp2.get_number() << " "
            << std::endl;
  if (sign_) {
    tmp1 = get_ones_comp();
    for (int i = size1; i < size2; ++i)
      tmp1.big_int_.insert(tmp1.big_int_.begin(), 1);
  }
  if (other.sign_) {
    tmp2 = other.get_ones_comp();
    for (int i = size2; i < size1; ++i)
      tmp2.big_int_.insert(tmp2.big_int_.begin(), 1);
  }
  std::cout << "HUY " << tmp1.get_number() << " " << tmp2.get_number() << " "
            << std::endl;
  for (int i = tmp1.big_int_.size() - 1, j = tmp2.big_int_.size() - 1;
       i >= 0 || j >= 0; --i, --j) {
    if (j >= 0) {
      if (i >= 0) {
        tmp1.big_int_[i] = tmp1.big_int_[i] & tmp2.big_int_[j];
        if (tmp1.big_int_[i]) all_zero = 0;

      } else {
        break;
        // tmp1.big_int_.insert(tmp1.big_int_.begin(), tmp2.big_int_[j]);
      }
    } else {
      tmp1.big_int_[i] = 0;
    }
  }

  *this = tmp1;
  std::cout << " !!HUY " << get_number();

  std::cout << sign_ << "( " << all_zero << " )" << other.sign_ << std::endl;
  if ((sign_ && other.sign_) && !all_zero) {
    std::cout << "EEF ";
    *this = get_from_ones_comp();
  } else if (sign_ && other.sign_ && all_zero)
    big_int_.insert(big_int_.begin(), 1);
  // else if (sign_) big_int_.insert(big_int_.begin(), 1);
  std::cout << "HUY " << get_number();
  while (!big_int_[0] && !(big_int_.size() == 1)) {
    big_int_.erase(big_int_.begin());
  }
  sign_ = sign_ & other.sign_;

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
  // bool buf = 0;
  for (int i = big_int_.size() - 1; i >= 0; --i) {
    if (!big_int_[i]) {
      big_int_[i] = 1;
      // buf = 1;
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
  if (!sign_) {
    mini_inc(big_int_);
  } else {
    mini_dec(big_int_);
  }
  return *this;
}
BigInt &BigInt::operator--() {
  if (!sign_) {
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
  if (sign_ > other.sign_) return 1;
  if (sign_ < other.sign_) return 0;
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
  bool res = 0;
  int buf = 0;
  for (int i = big_int_.size() - 1, j = other.big_int_.size() - 1;
       j >= 0 || i >= 0 || buf; --i, --j) {
    if (i >= 0 && j >= 0) {
      bool bit1 = big_int_[i], bit2 = other.big_int_[j];
      bool buf2;
      if (buf && !bit1 && bit2)
        buf2 = 1;
      else
        buf2 = 0;
      if (buf) bit1 = !bit1;
      if (!bit1) buf = bit1 < bit2 ? 1 : 0;
      big_int_[i] = ((buf || (bit1 && !bit2)) && !buf2) ? 1 : 0;
      // std::cout << buf << " " << big_int_[i] << std::endl;
      // buf = (bit1 - bit2 - buf) / 2;
      if (!i) {
        while (!big_int_[i]) {
          big_int_.erase(big_int_.begin());
        }
      }
    } else if (i >= 0) {
      if (big_int_[i]) {
        if (buf) big_int_[i] = 0;
        if (!i) {
          while (!big_int_[i]) {
            big_int_.erase(big_int_.begin());
          }
        }
        break;
      } else {
        if (!buf) break;
        big_int_[i] = 1;
      }
    }
  }
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

std::string BigInt::get_number() const {
  std::stringstream ss;
  for (auto it = big_int_.begin(); it != big_int_.end(); ++it) {
    ss << *it;
  }
  std::string str = ss.str();
  if (sign_) str.insert(str.begin(), '-');
  return str;
}

BigInt &BigInt::operator+=(const BigInt &other) {
  if (sign_ == other.sign_) {
    // std::cout << "HEEERE" << std::endl;
    minisum(other);
  } else {
    if (is_less(other)) {
      BigInt tmp(other);
      tmp.minisub(*this);
      *this = tmp;
    } else {
      minisub(other);
    }
  }
  return *this;
}

BigInt &BigInt::operator-=(const BigInt &other) {
  if (!sign_ && other.sign_)
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

size_t BigInt::size() const { return big_int_.size(); }