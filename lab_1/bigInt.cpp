#include "bigInt.h"

#include <algorithm>

BigInt::BigInt(const int number) : sign_(number < 0) {
  int tmp_number = number >= 0 ? number : number * (-1);
  if (!tmp_number) {
    big_int_.insert(big_int_.begin(), 0);
  } else {
    for (; tmp_number; tmp_number /= 2) {
      big_int_.insert(big_int_.begin(), tmp_number % 2);
    }
  }
}

BigInt::BigInt(std::string number) : sign_(number[0] == '-') {
  int size = number.size();
  long long bigInt = std::stol(number);
  for (; bigInt; bigInt /= 2) {
    big_int_.insert(big_int_.begin(), bigInt % 2);
  }
}

BigInt::BigInt(const BigInt &other)
    : big_int_(other.big_int_), sign_(other.sign_) {}

BigInt::BigInt(BigInt &&other) : big_int_(other.big_int_), sign_(other.sign_) {}

BigInt &BigInt::operator=(const BigInt &other) {
  if (this == &other) {
    // throw std::invalid_argument("You are trying to assign the same");
  }
  big_int_ = other.big_int_;
  sign_ = other.sign_;
  return *this;
}

BigInt &BigInt::operator=(BigInt &&other) {
  if (this == &other) {
    big_int_.clear();
  } else {
    big_int_ = std::move(other.big_int_);
    sign_ = std::move(other.sign_);
  }
  return *this;
}

bool BigInt::operator[](size_t pos) { return big_int_[pos]; }

const bool BigInt::operator[](size_t pos) const { return big_int_[pos]; }

bool BigInt::empty() { return big_int_.empty(); }

BigInt BigInt::operator~() const {
  BigInt result(*this);
  ++result;
  result.sign_ = !sign_;
  return result;
}

BigInt BigInt::get_from_ones_comp() const {
  BigInt result(*this);
  int size = result.size();
  result.sign_ = positive;
  --result;
  if (size != result.size()) result.big_int_.insert(result.big_int_.begin(), 0);
  for (int i = 0; i < result.size(); ++i) {
    result.big_int_[i] = !result.big_int_[i];
  }
  result.sign_ = negative;
  return result;
}

BigInt BigInt::get_ones_comp() const {
  BigInt result(*this);
  for (int i = 0; i < size(); ++i) {
    result.big_int_[i] = !result.big_int_[i];
  }
  --result;
  return result;
}

BigInt &BigInt::get_bin_var(int size) {
  if (sign_) {
    *this = get_ones_comp();
    for (int i = (*this).size(); i < size; ++i)
      big_int_.insert(big_int_.begin(), 1);
  }
  return *this;
}

BigInt &BigInt::operator^=(const BigInt &other) {
  BigInt tmp1(*this);
  tmp1.get_bin_var(other.size());
  BigInt tmp2(other);
  tmp2.get_bin_var(size());
  bool all_zero = 1;
  for (int i = tmp1.size() - 1, j = tmp2.size() - 1; i >= 0 || j >= 0;
       --i, --j) {
    if (j >= 0) {
      if (i >= 0) {
        tmp1.big_int_[i] = tmp1.big_int_[i] ^ tmp2.big_int_[j];
        if (tmp1.big_int_[i]) all_zero = 0;
      } else {
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
  fix_variable_look(all_zero);
  return *this;
}

void BigInt::fix_variable_look(bool all_zero) {
  if (sign_ && !all_zero)
    *this = get_from_ones_comp();
  else if (sign_)
    big_int_.insert(big_int_.begin(), 1);
  rem_leading_zeroes();
}

BigInt &BigInt::operator&=(const BigInt &other) {
  BigInt tmp1(*this);
  tmp1.get_bin_var(other.size());
  BigInt tmp2(other);
  tmp2.get_bin_var(size());
  bool all_zero = 1;
  for (int i = tmp1.size() - 1, j = tmp2.size() - 1; i >= 0 || j >= 0;
       --i, --j) {
    if (j >= 0) {
      if (i >= 0) {
        tmp1.big_int_[i] = tmp1.big_int_[i] & tmp2.big_int_[j];
        if (tmp1.big_int_[i]) all_zero = 0;
      } else {
        break;
      }
    } else {
      tmp1.big_int_[i] = 0;
    }
  }
  *this = tmp1;
  sign_ = sign_ & other.sign_;
  fix_variable_look(all_zero);
  return *this;
}

BigInt &BigInt::operator|=(const BigInt &other) {
  BigInt tmp1(*this);
  tmp1.get_bin_var(other.size());
  BigInt tmp2(other);
  tmp2.get_bin_var(size());
  bool all_zero = 1;
  for (int i = tmp1.size() - 1, j = tmp2.size() - 1; i >= 0 || j >= 0;
       --i, --j) {
    if (j >= 0) {
      if (i >= 0) {
        tmp1.big_int_[i] = tmp1.big_int_[i] | tmp2.big_int_[j];
        if (tmp1.big_int_[i]) all_zero = 0;
      } else {
        tmp1.big_int_.insert(tmp1.big_int_.begin(), tmp2.big_int_[j]);
        if (tmp2.big_int_[j]) all_zero = 0;
      }
    } else {
      all_zero = 0;
      break;
    }
  }
  *this = tmp1;
  sign_ = sign_ | other.sign_;
  fix_variable_look(all_zero);
  return *this;
}

const BigInt BigInt::operator++(int) {
  BigInt old(*this);
  ++*this;
  return old;
}

BigInt &BigInt::operator++() {
  *this += 1;
  return *this;
}
BigInt &BigInt::operator--() {
  *this -= 1;
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
  if (sign_) return other.is_less(*this);
  return is_less(other);
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

void BigInt::mini_sum(const BigInt &other) {
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

void BigInt::mini_sub(const BigInt &other) {
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
      if (!i) {
        rem_leading_zeroes();
      }
    } else if (i >= 0) {
      if (big_int_[i]) {
        if (buf) big_int_[i] = 0;
        if (!i) {
          rem_leading_zeroes();
        }
        break;
      } else {
        if (!buf) break;
        big_int_[i] = 1;
      }
    }
  }
}

void BigInt::rem_leading_zeroes() {
  while (!big_int_[0] && big_int_.size() > 1) {
    big_int_.erase(big_int_.begin());
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

BigInt BigInt::operator+() const {
  BigInt tmp(*this);
  return tmp;
}

BigInt BigInt::operator-() const {
  BigInt tmp(*this);
  if (tmp.size() != 1 || tmp.big_int_[0]) tmp.sign_ = !tmp.sign_;
  return tmp;
}

BigInt &BigInt::operator+=(const BigInt &other) {
  if (sign_ == other.sign_) {
    mini_sum(other);
  } else {
    if (is_less(other)) {
      BigInt tmp(other);
      tmp.mini_sub(*this);
      *this = tmp;
    } else {
      mini_sub(other);
    }
    if (!big_int_[0]) sign_ = positive;
  }
  return *this;
}

BigInt &BigInt::operator-=(const BigInt &other) {
  BigInt tmp(other);
  tmp.sign_ = !tmp.sign_;
  *this += tmp;
  return *this;
}

size_t BigInt::size() const { return big_int_.size(); }

BigInt &BigInt::operator*=(const BigInt &other) {
  BigInt tmp(*this), answer(0);
  answer.sign_ = sign_ ^ other.sign_;
  for (auto pos = other.big_int_.rbegin(); pos != other.big_int_.rend();
       ++pos) {
    if (*pos) {
      answer.mini_sum(tmp);
    }
    tmp.big_int_.push_back(0);
  }
  *this = answer;
  rem_leading_zeroes();

  if (!big_int_[0]) sign_ = positive;
  return *this;
}

BigInt &BigInt::operator/=(const BigInt &other) {
  bool sign = sign_;
  *this = get_quotient_reminder(other).first;
  sign_ = (*this)[0] ? sign ^ other.sign_ : positive;

  return *this;
}

BigInt &BigInt::operator%=(const BigInt &other) {
  bool sign = sign_;
  *this = get_quotient_reminder(other).second;
  sign_ = (*this)[0] ? sign : positive;

  return *this;
}

std::pair<BigInt, BigInt> BigInt::get_quotient_reminder(const BigInt &other) {
  if (other == (BigInt)0) throw std::out_of_range("Floating point exception");
  BigInt ans, reminder(0);
  if (is_less(other)) {
    ans.big_int_.push_back(0);
    reminder = *this;
    return std::pair<BigInt, BigInt>(ans, reminder);
  }
  BigInt tmp1(*this), tmp2(other);
  bool sign1 = sign_, sign2 = other.sign_;
  int counter = shift_divider(tmp1, tmp2);
  tmp1.sign_ = tmp2.sign_ = positive;
  BigInt tmp;
  for (int i = 0; i <= counter; ++i) {
    tmp = tmp1;
    tmp1 -= tmp2;
    if (tmp1.sign_) {
      ans.big_int_.push_back(0);
      tmp1 = tmp;
      if (i == counter) reminder = tmp;
    } else {
      ans.big_int_.push_back(1);
      if (i == counter) reminder = tmp1;
    }
    tmp2.big_int_.pop_back();
  }

  return std::pair<BigInt, BigInt>(ans, reminder);
}

int BigInt::shift_divider(const BigInt &tmp1, BigInt &tmp2) {
  int counter = 0;
  for (int i = tmp2.size(); i < tmp1.size(); ++i, ++counter) {
    tmp2.big_int_.push_back(0);
  }
  if (tmp1.is_less(tmp2)) {
    tmp2.big_int_.pop_back();
    --counter;
  }
  return counter;
}

BigInt operator+(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp += b;
  return temp;
}

BigInt operator-(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp -= b;
  return temp;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp *= b;
  return temp;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp /= b;
  return temp;
}

BigInt operator^(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp ^= b;
  return temp;
}

BigInt operator%(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp %= b;
  return temp;
}

BigInt operator&(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp &= b;
  return temp;
}

BigInt operator|(const BigInt &a, const BigInt &b) {
  BigInt temp(a);
  temp |= b;
  return temp;
}

BigInt::operator int() const {
  if ((*this) == (BigInt)0) return 0;
  int number = 0, powerOf2 = 1;
  for (auto pos = big_int_.rbegin(); pos != big_int_.rend(); ++pos) {
    number += *pos * powerOf2;
    powerOf2 *= 2;
  }
  if (sign_) number *= -1;
  return number;
}

BigInt::operator std::string() const { return std::to_string((*this)); }

std::ostream &operator<<(std::ostream &out, const BigInt &num) {
  out << std::string(num);
  return out;
}

std::istream &operator>>(std::istream &in, BigInt &num) {
  std::string str;
  in >> str;
  num = BigInt(str);
  return in;
}