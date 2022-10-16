#ifndef BIGINT_H_
#define BIGINT_H_
#include <sstream>
#include <vector>

// #include <fstream>
#include <iostream>
#define positive 0
#define negative 1

class BigInt {
 public:
  BigInt() = default;
  BigInt(const int);
  BigInt(std::string);
  BigInt(const BigInt&);
  BigInt(BigInt&&);
  ~BigInt() = default;

  bool empty();
  BigInt& operator=(const BigInt&);
  BigInt& operator=(BigInt&&);
  bool operator[](size_t pos);
  const bool operator[](size_t pos) const;

  BigInt& operator++();
  const BigInt operator++(int);
  BigInt& operator--();
  const BigInt operator--(int);

  BigInt operator~() const;
  BigInt& operator+=(const BigInt&);
  BigInt& operator-=(const BigInt&);
  BigInt& operator*=(const BigInt&);
  BigInt& operator/=(const BigInt&);
  BigInt& operator%=(const BigInt&);
  BigInt& operator^=(const BigInt&);
  BigInt& operator&=(const BigInt&);
  BigInt& operator|=(const BigInt&);

  BigInt operator+() const;
  BigInt operator-() const;

  bool operator==(const BigInt& other) const;
  bool operator!=(const BigInt& other) const;
  bool operator<(const BigInt& other) const;
  bool operator>(const BigInt& other) const;
  bool operator<=(const BigInt& other) const;
  bool operator>=(const BigInt& other) const;

  operator int() const;
  operator std::string() const;
  size_t size() const;

 private:
  bool sign_;
  std::vector<bool> big_int_;

  void mini_sum(const BigInt& other);
  void mini_sub(const BigInt& other);
  bool is_less(const BigInt& other) const;
  void rem_leading_zeroes();
  int shift_divider(const BigInt& tmp1, BigInt& tmp2);
  BigInt get_ones_comp() const;
  BigInt get_from_ones_comp() const;
  BigInt& get_bin_var(int size);
  void fix_variable_look(bool all_zero);
  std::pair<BigInt, BigInt> get_quotient_reminder(const BigInt& other);
  BigInt& dividing_proccess(BigInt& tmp1, BigInt& tmp2, BigInt& tmp);
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& o, const BigInt& i);
std::istream& operator>>(std::istream& in, BigInt& num);

#endif
