#include "tests.h"

#include <check.h>

#include "calculator.h"

START_TEST(s21_calculator_1) {
  char input[] = "((4+5)*4)^2";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 1296, 1e07);
}
END_TEST

START_TEST(s21_calculator_2) {
  char input[] = "cos((x)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_calculator_3) {
  char input[] = "x^2+x^3+x^1";
  char output[256] = "\0";
  char x[3] = "2";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 14, 1e07);
}
END_TEST

START_TEST(s21_calculator_4) {
  char input[] = "sqrt(-9)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_calculator_5) {
  char input[] = "log(-9)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_calculator_6) {
  char input[] = "cos(0)";
  char output[256] = "\0";
  char x[3] = "2";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 1, 1e07);
}
END_TEST

START_TEST(s21_calculator_7) {
  char input[] = "-(9+1)+3/(-1)";
  char output[256] = "\0";
  char x[3] = "2";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), -13, 1e07);
}
END_TEST

START_TEST(s21_calculator_8) {
  char input[] = "(4*(8+2))+(3*2-(2*3-1)/4)";
  char output[256] = "\0";
  char x[3] = "2";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 44.75, 1e07);
}
END_TEST

START_TEST(s21_calculator_9) {
  char input[] = "x^2";
  char output[256] = "\0";
  char x[3] = "1.1";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 1.21, 1e07);
}
END_TEST

START_TEST(s21_calculator_10) {
  char input[] = "((7.8+x^2)*sqrt(6.7))/(5*(-4)+1)";
  char output[256] = "\0";
  char x[3] = "1.1";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), -1.22746351306, 1e07);
}
END_TEST

START_TEST(s21_calculator_11) {
  char input[] = "((7.8+x^2)*sqrt(6.7))/(5-5)";
  char output[256] = "\0";
  char x[3] = "1.1";
  int result = calculator(input, x, output);
  if (strstr("inf", output)) {
    result = 0;
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_calculator_12) {
  char input[] = "))(((sin(2))+2";
  char output[256] = "\0";
  char x[3] = "1.1";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_calculator_13) {
  char input[] = "2+(+2)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 4, 1e07);
}
END_TEST

START_TEST(s21_calculator_14) {
  char input[] = "1-(-2)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 3, 1e07);
}
END_TEST

START_TEST(s21_calculator_15) {
  char input[] = "-12-13.2^2*13.1-16.234+90.4563456";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), -2220.3216544, 1e07);
}
END_TEST

START_TEST(s21_calculator_16) {
  char input[] = "(1.345587654387512387+2)*2+(tan(12*19^2))";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 6.4291445, 1e07);
}
END_TEST

START_TEST(s21_calculator_17) {
  char input[] = "-12-13.2^2*13.1-16.234+90.4563456";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), -2220.3216544, 1e07);
}
END_TEST

START_TEST(s21_calculator_18) {
  char input[] = "acos(3845)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_calculator_19) {
  char input[] = "atan(0.6483608)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  ck_assert_int_eq(result, 1);
  ck_assert_double_eq_tol(s21_strtold(output), 0.5752220, 1e07);
}
END_TEST

START_TEST(s21_calculator_20) {
  char input[] = "ln(0)";
  char output[256] = "\0";
  char x[3] = "\0";
  int result = calculator(input, x, output);
  if (strstr(output, "inf")) {
    result = 0;
  }
  ck_assert_int_eq(result, 0);
}
END_TEST

int main() {
  Suite *s;
  TCase *tc;
  s = suite_create("calculator");
  tc = tcase_create("some_calculator");
  SRunner *sr = srunner_create(s);
  int number_failed;
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_calculator_1);
  tcase_add_test(tc, s21_calculator_2);
  tcase_add_test(tc, s21_calculator_3);
  tcase_add_test(tc, s21_calculator_4);
  tcase_add_test(tc, s21_calculator_5);
  tcase_add_test(tc, s21_calculator_6);
  tcase_add_test(tc, s21_calculator_7);
  tcase_add_test(tc, s21_calculator_8);
  tcase_add_test(tc, s21_calculator_9);
  tcase_add_test(tc, s21_calculator_10);
  tcase_add_test(tc, s21_calculator_11);
  tcase_add_test(tc, s21_calculator_12);
  tcase_add_test(tc, s21_calculator_13);
  tcase_add_test(tc, s21_calculator_14);
  tcase_add_test(tc, s21_calculator_15);
  tcase_add_test(tc, s21_calculator_16);
  tcase_add_test(tc, s21_calculator_17);
  tcase_add_test(tc, s21_calculator_18);
  tcase_add_test(tc, s21_calculator_19);
  tcase_add_test(tc, s21_calculator_20);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
