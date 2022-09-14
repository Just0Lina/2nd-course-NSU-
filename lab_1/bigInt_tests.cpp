#include <gtest/gtest.h>

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
//   long int number = 3454659609566;
//   std::string num_s = std::to_string(number);
//   BigInt bInt_a(num_s);
//   BigInt bInt_b = ~bInt_a;
//   std::string bin_val = to_binary_string(~number);
//   for (int i = 0; i < bin_val.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val[i] - '0'));
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

// TEST(Operators, operIncr1) {
//   long int number1 = 8;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number1 + 1);
//   ++bInt_a;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val2[i] - '0'));
//   }
// }

// TEST(Operators, operIncr2) {
//   long int number1 = 7;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1+1);
//   ++bInt_a;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operIncr3) {
//   long int number1 = 11;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number1 + 1);
//   std::cout << bin_val2 << std::endl;
//   ++bInt_a;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val2[i] - '0'));
//   }
// }

// TEST(Operators, operIncrPost1) {
//   long int number1 = 8;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1 + 1);
//   BigInt bInt_b = bInt_a++;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operIncrPost2) {
//   long int number1 = 7;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val2 = to_binary_string(number1 + 1);
//   std::cout << bin_val2 << std::endl;
//   BigInt bInt_b = bInt_a++;
//   for (int i = 0; i < bin_val2.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val2[i] - '0'));
//   }
// }

// TEST(Operators, operIncrPost3) {
//   long int number1 = 11;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number1 + 1);
//   std::cout << bin_val2 << std::endl;
//   BigInt bInt_b = bInt_a++;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val2[i] - '0'));
//   }
// }

// TEST(Operators, operDecPref1) {
//   long int number1 = 8;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1 - 1);
//   --bInt_a;
//   for (int i = bin_val1.size() - 1; i >= 0; --i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operDecPref2) {
//   long int number1 = 7;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1 - 1);
//   --bInt_a;
//   for (int i = bin_val1.size() - 1; i >= 0; --i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operDecPref3) {
//   long int number1 = 11;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1);
//   std::string bin_val2 = to_binary_string(number1 - 1);
//   std::cout << bin_val2 << std::endl;
//   --bInt_a;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val2[i] - '0'));
//   }
// }

// TEST(Operators, operDecPost1) {
//   long int number1 = 8;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1 - 1);
//   BigInt bInt_b = bInt_a--;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operDecPost2) {
//   long int number1 = 7;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1 - 1);
//   BigInt bInt_b = bInt_a--;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operDecPost3) {
//   long int number1 = 11;
//   std::string num_s1 = std::to_string(number1);
//   BigInt bInt_a(num_s1);
//   std::string bin_val1 = to_binary_string(number1 - 1);
//   BigInt bInt_b = bInt_a--;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_b[i], bool(bin_val1[i] - '0'));
//   }
// }

// TEST(Operators, operLess1) {
//   long int number1 = 11;
//   long int number2 = 40;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   ASSERT_EQ(bInt_a < bInt_b, number1 < number2);
// }

// TEST(Operators, operLess2) {
//   long int number1 = 343;
//   long int number2 = 40;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   ASSERT_EQ(bInt_a < bInt_b, number1 < number2);
// }

// TEST(Operators, operLess3) {
//   long int number1 = 33;
//   long int number2 = 46;
//   BigInt bInt_a(number1);
//   BigInt bInt_b(number2);
//   ASSERT_EQ(bInt_a < bInt_b, number1 < number2);
// }

// TEST(Methods, Sum1) {
//   long int number1 = 1;
//   long int number2 = 1;
//   BigInt bInt_a(number1);
//   std::cout << "HEERE1" << std::endl;
//   BigInt bInt_b(number2);
//   std::cout << "HEERE2" << std::endl;

//   std::string bin_val1 = to_binary_string(number1 + number2);
//   std::cout << "HEERE3" << std::endl;
//   bInt_a += bInt_b;
//   for (int i = 0; i < bin_val1.size(); ++i) {
//     ASSERT_EQ(bInt_a[i], bool(bin_val1[i] - '0'));
//   }
// }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// std::string to_binary_string(long long int n) {
//   std::string buffer;  // символы ответа в обратном порядке
//   // выделим память заранее по максимуму
//   buffer.reserve(std::numeric_limits<unsigned int>::digits);
//   do {
//     buffer += char('0' + n % 2);  // добавляем в конец
//     n = n / 2;
//   } while (n > 0);
//   return std::string(buffer.crbegin(),
//                      buffer.crend());  // разворачиваем результат
// }