#ifndef CREDIT_H
#define CREDIT_H

#include <math.h>
#include <stdlib.h>
typedef struct {
  double sum;
  int length;
  double percent;
  int type;  // 1 - аннуитетный, 2 - дифференцированный
} credit_input;

typedef struct {
  int month;
  double monthly_pay;
  double main_part;
  double percent_pay;
  double debt_remain;
} payment_row;

typedef struct {
  double monthly_pay;  // Для аннуитетного платежа или 0 для дифференцированного
  double overpayment;
  double total_pay;
  payment_row *payments;  // Динамический массив платежей
  int payment_count;      // Количество строк в таблице
} credit_output;

int calculate_credit(credit_input input, credit_output *output);

#endif  // CREDIT_H
