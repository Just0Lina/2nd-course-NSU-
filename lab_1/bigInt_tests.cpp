#include <gtest/gtest.h>

#include "bigInt.h"
std::string to_binary_string(long long int n);

TEST(Constructor, def_cons) {
  BigInt bInt_a;
  ASSERT_EQ(bInt_a.empty(), true);
}

TEST(Constructor, int_cons) {
  BigInt bInt_a(100);
  ASSERT_EQ(bInt_a.empty(), false);
  std::string bin_val = to_binary_string(100);
  for (int i = 0; bin_val.size() < 7; ++i) {
    ASSERT_EQ(bInt_a[i], bool(bin_val[i] - '0'));
  }
}

TEST(Constructor, string_cons1) {
  ASSERT_THROW({ BigInt bInt_a("sdff"); }, std::invalid_argument);
}

TEST(Constructor, string_cons2) {
  long int number = 1222;
  std::string num_s = std::to_string(number);
  BigInt bInt_a(num_s);
  std::string bin_val = to_binary_string(number);
  for (int i = 0; i < bin_val.size(); ++i) {
    ASSERT_EQ(bInt_a[i], bool(bin_val[i] - '0'));
  }
}

TEST(Constructor, copy_cons) {
  long int number = 34546596096;
  std::string num_s = std::to_string(number);
  BigInt bInt_a(num_s);
  BigInt bInt_b(bInt_a);
  std::string bin_val = to_binary_string(number);

  for (int i = 0; i < bin_val.size(); ++i) {
    ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
  }
}

TEST(Constructor, move_cons) {
  long int number = 34546596096;
  std::string num_s = std::to_string(number);
  BigInt bInt_a(num_s);
  BigInt bInt_b(std::move(bInt_a));
  std::string bin_val = to_binary_string(number);

  for (int i = 0; i < bin_val.size(); ++i) {
    ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
  }
}

TEST(Copy_assignment, assign1) {
  std::string num = "3454659609566";
  BigInt bInt_a(num);
  BigInt bInt_b = bInt_a;
  for (int i = 0; i < num.size(); ++i) {
    ASSERT_EQ(bInt_a[i], bInt_b[i]);
  }
}

TEST(Copy_assignment, assign_same) {
  long int number = 3454659609566;
  std::string num_s = std::to_string(number);
  BigInt bInt_a(num_s);
  bInt_a = bInt_a;
  std::string bin_val = to_binary_string(number);
  for (int i = 0; i < bin_val.size(); ++i) {
    ASSERT_EQ(bInt_a[i], bool(bin_val[i] - '0'));
  }
}

TEST(Operators, oper_negation) {
  long int number = 3454659609566;
  std::string num_s = std::to_string(number);
  BigInt bInt_a(num_s);
  BigInt bInt_b = ~bInt_a;
  std::string bin_val = to_binary_string(~number);
  for (int i = 0; i < bin_val.size(); ++i) {
    ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
  }
}

TEST(Move_assignment, assign1) {
  long int number = 3454659609566;
  std::string num_s = std::to_string(number);
  BigInt bInt_a(num_s);
  BigInt bInt_b = std::move(bInt_a);
  std::string bin_val = to_binary_string(number);
  for (int i = 0; i < bin_val.size(); ++i) {
    ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
  }
}

TEST(Move_assignment, assign_same) {
  std::string num = "3454659609566";
  BigInt bInt_a(num);
  bInt_a = std::move(bInt_a);
  ASSERT_EQ(bInt_a.empty(), true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string to_binary_string(long long int n) {
  std::string buffer;  // символы ответа в обратном порядке
  // выделим память заранее по максимуму
  buffer.reserve(std::numeric_limits<unsigned int>::digits);
  do {
    buffer += char('0' + n % 2);  // добавляем в конец
    n = n / 2;
  } while (n > 0);
  return std::string(buffer.crbegin(),
                     buffer.crend());  // разворачиваем результат
}