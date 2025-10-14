#include "deposit.h"

#include <math.h>
#include <stdlib.h>

int calculate_deposit(deposit_input input, deposit_output* output) {
  output->total_interest = 0.0;
  output->tax_amount = 0.0;
  output->final_balance = input.initial_sum;
  output->row_count = input.term;

  // Выделяем память под таблицу начислений
  output->rows = (deposit_row*)malloc(input.term * sizeof(deposit_row));
  if (!output->rows) {
    return 1;  // Ошибка выделения памяти
  }

  double monthly_rate =
      input.interest_rate / 100.0 / 12.0;  // Месячная процентная ставка
  double current_balance = input.initial_sum;
  double accumulated_interest =
      0.0;  // Накопленные проценты для капитализации или выплат
  int next_payment_month = input.payment_frequency;

  for (int i = 0; i < input.term; i++) {
    output->rows[i].month = i + 1;
    output->rows[i].balance = current_balance;
    output->rows[i].deposit = 0.0;
    output->rows[i].withdrawal = 0.0;

    // Проверяем пополнения
    for (int j = 0; j < input.deposit_count; j++) {
      if (input.deposits[j].month == i + 1) {
        output->rows[i].deposit = input.deposits[j].amount;
        current_balance += input.deposits[j].amount;
      }
    }

    // Проверяем снятия
    for (int j = 0; j < input.withdrawal_count; j++) {
      if (input.withdrawals[j].month == i + 1) {
        output->rows[i].withdrawal = input.withdrawals[j].amount;
        current_balance -= input.withdrawals[j].amount;
      }
    }

    // Рассчитываем проценты за месяц
    double interest = current_balance * monthly_rate;
    accumulated_interest += interest;
    output->rows[i].interest = interest;
    output->total_interest += interest;

    // Проверяем, нужно ли начислять проценты (в зависимости от периодичности
    // выплат)
    if ((i + 1) == next_payment_month || i == input.term - 1) {
      if (input.capitalization) {
        current_balance += accumulated_interest;
      }
      accumulated_interest = 0.0;
      next_payment_month += input.payment_frequency;
      if (next_payment_month > input.term) {
        next_payment_month = input.term;
      }
    }

    output->rows[i].final_balance = current_balance;
    output->final_balance = current_balance;
  }

  // Если капитализация отключена, проценты добавляются к итоговой сумме в конце
  // срока
  if (!input.capitalization) {
    output->final_balance += output->total_interest;
  }

  // Рассчитываем налог на доход
  output->tax_amount = output->total_interest * (input.tax_rate / 100.0);

  return 0;
}
