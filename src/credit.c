#include "credit.h"

// int main() {
//   credit_input input = {0};
//   credit_output output = {0};
//   input.sum = 100000;
//   input.length = 24;
//   input.percent = 20;
//   input.type = 2;
//   calculate_credit(input, &output);
// }

// int calculate_credit(credit_input input, credit_output *output) {
//   output->total_pay += input.sum;
//   double month_pay = 0;
//   int i = 0;
//   double rate = input.percent / 100;
//   double percent_pay = 0;
//   double debt_remain = input.sum;
//   double main_part = 0;
//   FILE *f = fopen("data_file.txt", "r+");

//  printf("месяц\tсумма платежа\tосновной платеж\tплатеж по "
//              "процентам\tостаток долга\n");
//  if (f) {
//    fprintf(f,
//            "месяц\tсумма платежа\tосновной платеж\tплатеж по "
//            "процентам\tостаток долга\n");
//  }
//  if (input.type == 1) {  // аннуитетные
//    double month_rate = rate / 12;
//    month_pay =
//        (input.sum * month_rate) / (1 - pow(1 + month_rate, -1 *
//        input.length));
//    while (input.length != 0) {
//      i++;
//      percent_pay = debt_remain * month_rate;
//      main_part = month_pay - percent_pay;
//      debt_remain -= main_part;
//      output->overpayment += percent_pay;
//      input.length--;
//      printf("%d\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\n", i, month_pay,
//                      main_part, percent_pay, debt_remain);
//      if (f) {
//        fprintf(f, "%d\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\n", i, month_pay,
//                main_part, percent_pay, debt_remain);
//      }
//    }

//    int ch;
//    while ((ch = fgetc(f)) != EOF) {
//            putchar(ch); // Вывод символа на экран
//        }
//    fclose(f);

//  }
//  else {  // дифференцированные
//    main_part = input.sum / input.length;
//    while (input.length != 0) {
//      i++;
//      percent_pay = debt_remain * rate / 12;
//      month_pay = percent_pay + main_part;
//      output->overpayment += percent_pay;
//      debt_remain -= main_part;
//      input.length--;
//      printf("%d\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\n", i, month_pay,
//                      main_part, percent_pay, debt_remain);
//      if (f) {
//        fprintf(f, "%d\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\n", i, month_pay,
//                main_part, percent_pay, debt_remain);
//      }
//    }
//    fclose(f);
//  }
//  output->total_pay += output->overpayment;

//  printf("total_pay %f\n", output->total_pay);
//  printf("overpayment %f\n", output->overpayment);
//  return 0;
//}

int calculate_credit(credit_input input, credit_output *output) {
  output->total_pay = input.sum;
  output->overpayment = 0;
  output->monthly_pay = 0;
  output->payment_count = input.length;
  output->payments = (payment_row *)malloc(input.length * sizeof(payment_row));
  if (!output->payments) {
    return 1;  // Ошибка выделения памяти
  }

  double month_pay = 0;
  int i = 0;
  double rate = input.percent / 100;
  double percent_pay = 0;
  double debt_remain = input.sum;
  double main_part = 0;

  if (input.type == 1) {  // Аннуитетные
    double month_rate = rate / 12;
    month_pay =
        (input.sum * month_rate) / (1 - pow(1 + month_rate, -input.length));
    output->monthly_pay = month_pay;
    while (input.length != 0) {
      percent_pay = debt_remain * month_rate;
      main_part = month_pay - percent_pay;
      debt_remain -= main_part;
      output->overpayment += percent_pay;

      // Заполняем строку таблицы
      output->payments[i].month = i + 1;
      output->payments[i].monthly_pay = month_pay;
      output->payments[i].main_part = main_part;
      output->payments[i].percent_pay = percent_pay;
      output->payments[i].debt_remain = debt_remain;

      i++;
      input.length--;
    }
  } else {  // Дифференцированные
    main_part = input.sum / output->payment_count;
    while (input.length != 0) {
      percent_pay = debt_remain * rate / 12;
      month_pay = percent_pay + main_part;
      output->overpayment += percent_pay;
      debt_remain -= main_part;

      // Заполняем строку таблицы
      output->payments[i].month = i + 1;
      output->payments[i].monthly_pay = month_pay;
      output->payments[i].main_part = main_part;
      output->payments[i].percent_pay = percent_pay;
      output->payments[i].debt_remain = debt_remain;

      i++;
      input.length--;
    }
  }
  output->total_pay += output->overpayment;
  return 0;
}
