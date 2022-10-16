#include <gtest/gtest.h>

#include <cmath>

#include "bigInt.h"

TEST(Constructor, def_cons) {
  BigInt bInt_a;
  ASSERT_EQ(bInt_a.empty(), true);
}

TEST(Constructor, int_cons) {
  for (int i = 0; i < 100; ++i) {
    int number = std::rand() % 1000 - 500;
    BigInt bInt_a(number);
    ASSERT_EQ(bInt_a.empty(), false);
    ASSERT_EQ((int)bInt_a, number);
  }
}

TEST(Constructor, string_cons1) {
  ASSERT_THROW({ BigInt bInt_a("sdff"); }, std::invalid_argument);
}

TEST(Constructor, string_cons) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 10000 - 5000;
    std::string num_s = std::to_string(number);
    BigInt bInt_a(num_s);
    ASSERT_EQ((int)bInt_a, number);
  }
}

TEST(Constructor, copy_cons) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 10000 - 5000;
    std::string num_s = std::to_string(number);
    BigInt bInt_a(num_s);
    BigInt bInt_b(bInt_a);
    ASSERT_EQ((int)bInt_b, number);
  }
}

TEST(Constructor, move_cons) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 10000 - 5000;
    std::string num_s = std::to_string(number);
    BigInt bInt_a(num_s);
    BigInt bInt_b(std::move(bInt_a));
    ASSERT_EQ((int)bInt_b, number);
  }
}

TEST(Copy_assignment, assign1) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 100000 - 50000;
    BigInt bInt_a(number);
    BigInt bInt_b = bInt_a;
    ASSERT_EQ((int)bInt_a, (int)bInt_b);
  }
}

TEST(Copy_assignment, assign_same) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 10000 - 5000;
    std::string num_s = std::to_string(number);
    BigInt bInt_a(num_s);
    bInt_a = bInt_a;
    ASSERT_EQ((int)bInt_a, number);
  }
}

TEST(Operators, oper_negation) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    std::string num_s = std::to_string(number);
    BigInt bInt_a(num_s);
    BigInt bInt_b = ~bInt_a;
    ASSERT_EQ((int)bInt_b, ~number);
  }
}

TEST(Move_assignment, assign1) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    std::string num_s = std::to_string(number);
    BigInt bInt_a(num_s);
    BigInt bInt_b = std::move(bInt_a);
    ASSERT_EQ((int)bInt_b, number);
  }
}

TEST(Move_assignment, assign_same) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    BigInt bInt_a(number);
    bInt_a = std::move(bInt_a);
    ASSERT_EQ(bInt_a.empty(), true);
  }
}

TEST(Operators, operXOR) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    long int number2 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    int ans = number1 ^ number2;
    BigInt tmp = bInt_a ^ bInt_b;
    bInt_a ^= bInt_b;
    ASSERT_EQ((int)bInt_a, ans);
    ASSERT_EQ((int)tmp, ans);
  }
}

TEST(Operators, operBinMul1) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    long int number2 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    BigInt tmp = bInt_a & bInt_b;
    bInt_a &= bInt_b;
    int ans = number1 & number2;
    ASSERT_EQ((int)bInt_a, ans);
    ASSERT_EQ((int)tmp, ans);
  }
}

TEST(Operators, operBinSum) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    long int number2 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    BigInt tmp = bInt_a | bInt_b;
    int number = tmp;
    bInt_a |= bInt_b;
    int ans = number1 | number2;
    ASSERT_EQ((int)bInt_a, ans);
    ASSERT_EQ((int)tmp, ans);
  }
}

TEST(Operators, operIncrPref) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    ++bInt_a;
    ASSERT_EQ((int)bInt_a, number1 + 1);
  }
}

TEST(Operators, operIncrPost) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b = bInt_a++;
    ASSERT_EQ((int)bInt_a, number1 + 1);
    ASSERT_EQ((int)bInt_b, number1);
  }
}

TEST(Operators, operDecPref) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    // std::cout << number1 << std::endl;
    BigInt bInt_a(number1);
    --bInt_a;
    ASSERT_EQ((int)bInt_a, number1 - 1);
  }
}

TEST(Operators, operDecPost) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b = bInt_a--;
    ASSERT_EQ((int)bInt_a, number1 - 1);
    ASSERT_EQ((int)bInt_b, number1);
  }
}

TEST(Operators, operLess) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 1000 - 500;
    long int number2 = std::rand() % 1000 - 500;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    ASSERT_EQ(bInt_a < bInt_b, number1 < number2);
  }
}

TEST(Operators, operMore) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 1000 - 500;
    long int number2 = std::rand() % 1000 - 500;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    ASSERT_EQ(bInt_a > bInt_b, number1 > number2);
  }
}

TEST(Operators, operEqual) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 1000 - 500;
    long int number2 = std::rand() % 1000 - 500;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    ASSERT_EQ(bInt_a == bInt_b, number1 == number2);
  }
}

TEST(Operators, operLessEqual) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 1000 - 500;
    long int number2 = std::rand() % 1000 - 500;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    ASSERT_EQ(bInt_a <= bInt_b, number1 <= number2);
  }
}

TEST(Operators, operMoreEqual) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 1000 - 500;
    long int number2 = std::rand() % 1000 - 500;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    ASSERT_EQ(bInt_a >= bInt_b, number1 >= number2);
  }
}

TEST(Methods, Sum) {
  for (int i = 0; i < 100; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    long int number2 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    BigInt tmp = bInt_a + bInt_b;
    bInt_a += bInt_b;
    int ans = number1 + number2;
    ASSERT_EQ((int)bInt_a, ans);
    ASSERT_EQ((int)tmp, ans);
  }
}

TEST(Methods, Sub) {
  for (int i = 0; i < 1000; ++i) {
    long int number1 = std::rand() % 10000 - 5000;
    long int number2 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    BigInt tmp = bInt_a - bInt_b;
    bInt_a -= bInt_b;
    int ans = number1 - number2;
    ASSERT_EQ((int)bInt_a, ans);
    ASSERT_EQ((int)tmp, ans);
  }
}

TEST(Operators, operUnPlus) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    BigInt bInt_a(number);
    BigInt bInt_b = +bInt_a;
    ASSERT_EQ((int)bInt_b, +number);
  }
}

TEST(Operators, operUnMinus) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    BigInt bInt_a(number);
    BigInt bInt_b = -bInt_a;
    ASSERT_EQ((int)bInt_b, -number);
  }
}

TEST(Operators, operMul) {
  for (int i = 0; i < 1000; ++i) {
    int number1 = std::rand() % 1000 - 500;
    int number2 = std::rand() % 1000 - 500;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    BigInt tmp = bInt_a * bInt_b;
    bInt_a *= bInt_b;
    int ans = number1 * number2;
    ASSERT_EQ((int)bInt_a, ans);
    ASSERT_EQ((int)tmp, ans);
  }
}

TEST(Operators, operRem) {
  for (int i = 0; i < 10000; ++i) {
    int number1 = std::rand() % 10000 - 5000;
    int number2 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    if (number2) {
      BigInt tmp = bInt_a % bInt_b;
      bInt_a %= bInt_b;
      int ans = number1 % number2;
      ASSERT_EQ((int)bInt_a, ans);
      ASSERT_EQ((int)tmp, ans);
    } else {
      ASSERT_THROW({ bInt_a %= bInt_b; }, std::out_of_range);
    }
  }
}

TEST(Operators, operQuot) {
  for (int i = 0; i < 10000; ++i) {
    int number1 = std::rand() % 10000 - 5000;
    int number2 = std::rand() % 10000 - 5000;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    if (number2) {
      BigInt tmp = bInt_a / bInt_b;
      bInt_a /= bInt_b;
      int ans = number1 / number2;
      ASSERT_EQ((int)bInt_a, ans);
      ASSERT_EQ((int)tmp, ans);
    } else {
      ASSERT_THROW({ bInt_a /= bInt_b; }, std::out_of_range);
    }
  }
}

TEST(Operators, operOut) {
  for (int i = 0; i < 100; ++i) {
    long int number = std::rand() % 1000 - 500;
    BigInt bInt_a(number);
    BigInt bInt_b = ~bInt_a;
    std::cout << bInt_a << " " << bInt_b << std::endl;
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
