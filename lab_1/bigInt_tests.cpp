#include <gtest/gtest.h>

#include <cmath>

#include "bigInt.h"
std::string to_binary_string(long long int n);

// TEST(Constructor, def_cons) {
//   BigInt bInt_a;
//   ASSERT_EQ(bInt_a.empty(), true);
// }

// TEST(Constructor, int_cons) {
//   BigInt bInt_a(100);
//   ASSERT_EQ(bInt_a.empty(), false);
//   std::string bin_val = to_binary_string(100);
//   ASSERT_EQ(bInt_a.get_number(), bin_val);
// }

// TEST(Constructor, string_cons1) {
//   ASSERT_THROW({ BigInt bInt_a("sdff"); }, std::invalid_argument);
// }

// TEST(Constructor, string_cons) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 10000 - 5000;
//     std::string num_s = std::to_string(number);
//     BigInt bInt_a(num_s);
//     std::string bin_val = to_binary_string(number);
//     ASSERT_EQ(bInt_a.get_number(), bin_val);
//   }
// }

// TEST(Constructor, copy_cons) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 10000 - 5000;
//     std::string num_s = std::to_string(number);
//     BigInt bInt_a(num_s);
//     BigInt bInt_b(bInt_a);
//     std::string bin_val = to_binary_string(number);
//     ASSERT_EQ(bInt_b.get_number(), bin_val);
//   }
// }

// TEST(Constructor, move_cons) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 10000 - 5000;
//     std::string num_s = std::to_string(number);
//     BigInt bInt_a(num_s);
//     BigInt bInt_b(std::move(bInt_a));
//     std::string bin_val = to_binary_string(number);
//     ASSERT_EQ(bInt_b.get_number(), bin_val);
//   }
// }

// TEST(Copy_assignment, assign1) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 100000 - 50000;
//     BigInt bInt_a(number);
//     BigInt bInt_b = bInt_a;
//     ASSERT_EQ(bInt_a.get_number(), bInt_b.get_number());
//   }
// }

// TEST(Copy_assignment, assign_same) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 10000 - 5000;
//     std::string num_s = std::to_string(number);
//     BigInt bInt_a(num_s);
//     bInt_a = bInt_a;
//     std::string bin_val = to_binary_string(number);
//     ASSERT_EQ(bInt_a.get_number(), bin_val);
//   }
// }

// TEST(Operators, oper_negation) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 1000 - 500;
//     std::string num_s = std::to_string(number);
//     BigInt bInt_a(num_s);
//     BigInt bInt_b = ~bInt_a;
//     std::string bin_val = to_binary_string(~number);
//     ASSERT_EQ(bInt_b.get_number(), bin_val);
//   }
// }

// TEST(Move_assignment, assign1) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 1000 - 500;
//     std::string num_s = std::to_string(number);
//     BigInt bInt_a(num_s);
//     BigInt bInt_b = std::move(bInt_a);
//     std::string bin_val = to_binary_string(number);
//     ASSERT_EQ(bInt_b.get_number(), bin_val);
//   }
// }

// TEST(Move_assignment, assign_same) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 1000 - 500;
//     BigInt bInt_a(number);
//     bInt_a = std::move(bInt_a);
//     ASSERT_EQ(bInt_a.empty(), true);
//   }
// }

// TEST(Operators, operXOR) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     long int number2 = std::rand() % 10000 - 5000;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1);
//     // std::cout << "Value a " << number1 << std::endl;
//     number1 = number1 ^ number2;
//     bin_val1 = to_binary_string(number1);
//     std::string bin_val2 = to_binary_string(number2);
//     // std::cout << "Value b " << number2 << std::endl;
//     bInt_a ^= bInt_b;
//     ASSERT_EQ(bInt_a.get_number(), bin_val1);
//   }
// }

// TEST(Operators, operBinMul1) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     long int number2 = std::rand() % 10000 - 5000;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1);
//     number1 = number1 & number2;
//     bin_val1 = to_binary_string(number1);
//     std::string bin_val2 = to_binary_string(number2);
//     bInt_a &= bInt_b;
//     ASSERT_EQ(bInt_a.get_number(), bin_val1);
//   }
// }

// TEST(Operators, operBinSum1) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     long int number2 = std::rand() % 10000 - 5000;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1);
//     number1 = number1 | number2;
//     bin_val1 = to_binary_string(number1);
//     std::string bin_val2 = to_binary_string(number2);
//     bInt_a |= bInt_b;
//     ASSERT_EQ(bInt_a.get_number(), bin_val1);
//   }
// }

// TEST(Operators, operIncrPref) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     BigInt bInt_a(number1);
//     std::string bin_val1 = to_binary_string(number1 + 1);
//     ++bInt_a;
//     ASSERT_EQ(bInt_a.get_number(), bin_val1);
//   }
// }

// TEST(Operators, operIncrPost) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     BigInt bInt_a(number1);
//     BigInt bInt_b = bInt_a++;
//     std::string bin_val1 = to_binary_string(number1);
//     std::string bin_val2 = to_binary_string(number1 + 1);
//     ASSERT_EQ(bInt_b.get_number(), bin_val1);
//     ASSERT_EQ(bInt_a.get_number(), bin_val2);
//   }
// }

// TEST(Operators, operDecPref) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     // std::cout << number1 << std::endl;
//     BigInt bInt_a(number1);
//     std::string bin_val1 = to_binary_string(number1 - 1);
//     --bInt_a;
//     ASSERT_EQ(bInt_a.get_number(), bin_val1);
//   }
// }

// TEST(Operators, operDecPost) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     BigInt bInt_a(number1);
//     BigInt bInt_b = bInt_a--;
//     std::string bin_val1 = to_binary_string(number1);
//     std::string bin_val2 = to_binary_string(number1 - 1);
//     ASSERT_EQ(bInt_b.get_number(), bin_val1);
//     ASSERT_EQ(bInt_a.get_number(), bin_val2);
//   }
// }

// TEST(Operators, operLess) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     // std::cout << number1 << " " << number2 << std::endl;

//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     ASSERT_EQ(bInt_a < bInt_b, number1 < number2);
//   }
// }

// TEST(Operators, operMore) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     ASSERT_EQ(bInt_a > bInt_b, number1 > number2);
//   }
// }

// TEST(Operators, operEqual) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     ASSERT_EQ(bInt_a == bInt_b, number1 == number2);
//   }
// }

// TEST(Operators, operLessEqual) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     ASSERT_EQ(bInt_a <= bInt_b, number1 <= number2);
//   }
// }

// TEST(Operators, operMoreEqual) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     ASSERT_EQ(bInt_a >= bInt_b, number1 >= number2);
//   }
// }

// TEST(Methods, Sum) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 100;
//     long int number2 = std::rand() % 1000 - 100;
//     // std::cout << i << " " << number1 << " " << number2 << std::endl;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1 + number2);
//     bInt_a += bInt_b;
//     // std::cout << bInt_a.get_number() << std::endl;
//     ASSERT_EQ(bInt_a.get_number(), bin_val1);
//   }
// }

// TEST(Methods, Sub) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 100;
//     long int number2 = std::rand() % 1000 - 100;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1 - number2);
//     std::cout << number1 << " " << number2 << std::endl;
//     bInt_a -= bInt_b;
//     // std::cout << bInt_a.get_number() << std::endl;
//     ASSERT_EQ(bInt_a.get_number(), bin_val1);
//   }
// }

TEST(Operators, operUnPlus) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    BigInt bInt_a(number);
    BigInt bInt_b = +bInt_a;
    std::string bin_val = to_binary_string(+number);
    ASSERT_EQ(bInt_b.get_number(), bin_val);
  }
}

TEST(Operators, operUnMinus) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    BigInt bInt_a(number);
    BigInt bInt_b = -bInt_a;
    std::string bin_val = to_binary_string(-number);
    ASSERT_EQ(bInt_b.get_number(), bin_val);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string to_binary_string(long long int n) {
  std::string buffer;
  long long int val = (n >= 0) ? n : -1 * n;
  buffer.reserve(std::numeric_limits<char>::digits);
  do {
    buffer += char('0' + val % 2);
    val = val / 2;
  } while (val > 0);

  if (n < 0) buffer += char('-');

  std::string ans(buffer.crbegin(), buffer.crend());
  // if (n < 0) {
  //   ans.insert(ans.begin(), '-');
  // }
  return ans;
}
