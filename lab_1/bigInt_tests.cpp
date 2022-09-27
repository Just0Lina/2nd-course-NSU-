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
//   for (int i = 0; bin_val.size() < 7; ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val[i] - '0'));
//   }
// }

// TEST(Constructor, string_cons1) {
//   ASSERT_THROW({ BigInt bInt_a("sdff"); }, std::invalid_argument);
// }

// TEST(Constructor, string_cons2) {
//   long int number = 1222;
//   std::string num_s = std::to_string(number);
//   BigInt bInt_a(num_s);
//   std::string bin_val = to_binary_string(number);
//   for (int i = 0; i < bin_val.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val[i] - '0'));
//   }
// }

// TEST(Constructor, copy_cons) {
//   long int number = 34546596096;
//   std::string num_s = std::to_string(number);
//   BigInt bInt_a(num_s);
//   BigInt bInt_b(bInt_a);
//   std::string bin_val = to_binary_string(number);

//   for (int i = 0; i < bin_val.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
//   }
// }

// TEST(Constructor, move_cons) {
//   long int number = 34546596096;
//   std::string num_s = std::to_string(number);
//   BigInt bInt_a(num_s);
//   BigInt bInt_b(std::move(bInt_a));
//   std::string bin_val = to_binary_string(number);

//   for (int i = 0; i < bin_val.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
//   }
// }

// TEST(Copy_assignment, assign1) {
//   std::string num = "3454659609566";
//   BigInt bInt_a(num);
//   BigInt bInt_b = bInt_a;
//   for (int i = 0; i < num.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bInt_b[i]);
//   }
// }

// TEST(Copy_assignment, assign_same) {
//   long int number = 3454659609566;
//   std::string num_s = std::to_string(number);
//   BigInt bInt_a(num_s);
//   bInt_a = bInt_a;
//   std::string bin_val = to_binary_string(number);
//   for (int i = 0; i < bin_val.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val[i] - '0'));
//   }
// }

// TEST(Operators, oper_negation) {
//   for (int i = 0; i < 100; ++i) {
//     long int number = std::rand() % 1000 - 500;
//     std::string num_s = std::to_string(number);
//     BigInt bInt_a(num_s);
//     BigInt bInt_b = ~bInt_a;
//     std::string bin_val = to_binary_string(~number);
//     if (number > 0) {
//       ASSERT_EQ(bInt_b.sign(), bool(bin_val[0] - '0'));
//       for (int i = 1; i < bin_val.size(); ++i) {
//         // std::cout << bInt_a[i - 1] << "! " << bInt_b[i - 1] << "!! "
//         //           << bin_val[i] << std::endl;
//         ASSERT_EQ(bInt_b[i - 1], bool(bin_val[i] - '0'));
//       }
//     } else {
//       for (int i = 0; i < bin_val.size(); ++i) {
//         // std::cout << bInt_a[i] << "! " << bInt_b[i] << "!! " << bin_val[i]
//         //           << std::endl;
//         ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
//       }
//     }
//   }
// }

// TEST(Move_assignment, assign1) {
//   long int number = 3454659609566;
//   std::string num_s = std::to_string(number);
//   BigInt bInt_a(num_s);
//   BigInt bInt_b = std::move(bInt_a);
//   std::string bin_val = to_binary_string(number);
//   for (int i = 0; i < bin_val.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
//   }
// }

// TEST(Move_assignment, assign_same) {
//   std::string num = "3454659609566";
//   BigInt bInt_a(num);
//   bInt_a = std::move(bInt_a);
//   ASSERT_EQ(bInt_a.empty(), true);
// }

// TEST(Operators, operXOR) {
//   long int number1 = 10;
//   long int number2 = 8;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string num_s2 = std::to_string(number2);
//   BigInt bInt_b(num_s2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') ^ (bin_val2[j] - '0')) + '0';
//     }
//   }
//   bInt_a ^= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operXOR2) {
//   long int number1 = 234;
//   long int number2 = 15;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') ^ (bin_val2[j] - '0')) + '0';
//     }
//   }
//   bInt_a ^= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operXOR3) {
//   long int number1 = 47;
//   long int number2 = 64;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') ^ (bin_val2[j] - '0')) + '0';
//     }
//   }
//   bInt_a ^= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operBinMul1) {
//   long int number1 = 10;
//   long int number2 = 8;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string num_s2 = std::to_string(number2);
//   BigInt bInt_b(num_s2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') & (bin_val2[j] - '0')) + '0';
//     } else {
//       bin_val1[i] = '0';
//     }
//   }
//   bInt_a &= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operBinMul2) {
//   long int number1 = 234;
//   long int number2 = 15;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);

//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   std::cout << bin_val1 << "\n" << bin_val2 << std::endl;

//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') & (bin_val2[j] - '0')) + '0';
//     } else {
//       bin_val1[i] = '0';
//     }
//   }
//   std::cout << bin_val1 << std::endl;
//   bInt_a &= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operBinMul3) {
//   long int number1 = 47;
//   long int number2 = 64;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') & (bin_val2[j] - '0')) + '0';
//     } else {
//       bin_val1[i] = '0';
//     }
//   }
//   bInt_a &= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operBinSum1) {
//   long int number1 = 10;
//   long int number2 = 8;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string num_s2 = std::to_string(number2);
//   BigInt bInt_b(num_s2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') | (bin_val2[j] - '0')) + '0';
//     }
//   }
//   bInt_a |= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operBinSum2) {
//   long int number1 = 234;
//   long int number2 = 15;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') | (bin_val2[j] - '0')) + '0';
//     }
//   }
//   bInt_a |= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operBinSum3) {
//   long int number1 = 47;
//   long int number2 = 64;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number2);
//   for (int i = bin_val1.size() - 1, j = bin_val2.size() - 1; i >= 0; --i,
//   --j) {
//     if (j >= 0) {
//       bin_val1[i] = ((bin_val1[i] - '0') | (bin_val2[j] - '0')) + '0';
//     }
//   }
//   bInt_a |= bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operIncr) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     // std::cout << number1 << std::endl;
//     BigInt bInt_a(number1);
//     std::string bin_val1 = to_binary_string(number1 + 1);
//     // std::cout << bin_val1 << std::endl;
//     ++bInt_a;
//     for (int i = 0; i < bin_val1.size(); ++i) {
//       ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//     }
//   }
// }

// TEST(Operators, operIncrPost1) {
//   for (int i = 0; i < 50; ++i) {
//     int number1 = std::rand() % 10000 - 5000;
//     BigInt bInt_a(number1);
//     std::string bin_val1 = to_binary_string(number1);
//     std::string bin_val2 = to_binary_string(number1 + 1);
//     BigInt bInt_b = bInt_a++;
//     BigInt bInt_c = bInt_a;
//     for (int i = 0; i < bin_val1.size(); ++i) {
//       ASSERT_EQ(bInt_b[i], bool(bin_val1[i] - '0'));
//     }
//     for (int i = 0; i < bin_val2.size(); ++i) {
//       ASSERT_EQ(bInt_c[i], bool(bin_val2[i] - '0'));
//     }
//   }
// }

// TEST(Operators, operDecPref1) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     // std::cout << number1 << std::endl;
//     BigInt bInt_a(number1);
//     std::string bin_val1 = to_binary_string(number1 - 1);
//     --bInt_a;
//     for (int i = bin_val1.size() - 1; i >= 0; --i) {
//       ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//     }
//   }
// }

// TEST(Operators, operDecPost1) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 10000 - 5000;
//     // std::cout << number1 << std::endl;
//     BigInt bInt_a(number1);
//     std::string bin_val1 = to_binary_string(number1);
//     std::string bin_val2 = to_binary_string(number1 - 1);
//     BigInt bInt_b = bInt_a--;
//     BigInt bInt_c = bInt_a;
//     for (int i = 0; i < bin_val1.size(); ++i) {
//       ASSERT_EQ(bInt_b[i], bool(bin_val1[i] - '0'));
//     }
//     for (int i = 0; i < bin_val2.size(); ++i) {
//       ASSERT_EQ(bInt_c[i], bool(bin_val2[i] - '0'));
//     }
//   }
// }

// TEST(Operators, operLess) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::cout << number1 << " " << number2 << std::endl;
//     std::string bin_val1 = to_binary_string(number1 + number2);
//     ASSERT_EQ(bInt_a < bInt_b, number1 < number2);
//   }
// }

// TEST(Operators, operMore) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1 + number2);
//     ASSERT_EQ(bInt_a > bInt_b, number1 > number2);
//   }
// }

// TEST(Operators, operEqual) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1 + number2);
//     ASSERT_EQ(bInt_a == bInt_b, number1 == number2);
//   }
// }

// TEST(Operators, operLessEqual) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1 + number2);
//     ASSERT_EQ(bInt_a <= bInt_b, number1 <= number2);
//   }
// }

// TEST(Operators, operMoreEqual) {
//   for (int i = 0; i < 100; ++i) {
//     long int number1 = std::rand() % 1000 - 500;
//     long int number2 = std::rand() % 1000 - 500;
//     BigInt bInt_a(number1);
//     BigInt bInt_b(number2);
//     std::string bin_val1 = to_binary_string(number1 + number2);
//     ASSERT_EQ(bInt_a >= bInt_b, number1 >= number2);
//   }
// }

TEST(Methods, Sum) {
  for (int i = 0; i < 1; ++i) {
    // long int number1 = std::rand() % 100 - 100;
    // long int number2 = std::rand() % 100;
    long int number1 = -17;
    long int number2 = 86;
    std::cout << number1 << " " << number2 << std::endl;
    BigInt bInt_a(number1);
    BigInt bInt_b(number2);
    std::string bin_val1 = to_binary_string(number1 + number2);
    for (int i = 0; i < bInt_a.size(); ++i) {
      // std::cout << bInt_a[i] << " ";
      // ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
    }
    std::cout << std::endl;
    for (int i = 0; i < bInt_b.size(); ++i) {
      // std::cout << bInt_b[i] << " ";
      // ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
    }
    bInt_a += bInt_b;
    for (int i = 0; i < bin_val1.size(); ++i) {
      std::cout << bInt_a[i] << " " << bin_val1[i] << std::endl;
      // ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
    }
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string to_binary_string(long long int n) {
  std::string buffer;  // символы ответа в обратном порядке
  // выделим память заранее по максимуму
  long long int val = (n >= 0) ? n : -1 * n;
  buffer.reserve(std::numeric_limits<unsigned int>::digits);
  do {
    buffer += char('0' + val % 2);  // добавляем в конец
    val = val / 2;
  } while (val > 0);
  return std::string(buffer.crbegin(),
                     buffer.crend());  // разворачиваем результат
}
