#ifndef DEPOSIT_H
#define DEPOSIT_H

typedef struct {
  int month;  // Месяц, когда происходит пополнение/снятие
  double amount;  // Сумма пополнения или снятия
} transaction;

// Структура для строки таблицы начислений
typedef struct {
  int month;          // Номер месяца
  double balance;     // Баланс на начало месяца
  double interest;    // Начисленные проценты за месяц
  double deposit;     // Пополнение в этом месяце
  double withdrawal;  // Снятие в этом месяце
  double final_balance;  // Баланс на конец месяца
} deposit_row;

// Входные данные для расчета вклада
typedef struct {
  double initial_sum;    // Начальная сумма вклада
  int term;              // Срок размещения (в месяцах)
  double interest_rate;  // Годовая процентная ставка
  double tax_rate;  // Налоговая ставка (в процентах)
  int payment_frequency;  // Периодичность выплат (1 - ежемесячно, 3 -
                          // ежеквартально, 12 - в конце срока)
  int capitalization;  // Капитализация процентов (1 - да, 0 - нет)
  transaction* deposits;     // Список пополнений
  int deposit_count;         // Количество пополнений
  transaction* withdrawals;  // Список снятий
  int withdrawal_count;      // Количество снятий
} deposit_input;

// Выходные данные для расчета вклада
typedef struct {
  double total_interest;  // Общая сумма начисленных процентов
  double tax_amount;     // Сумма налога
  double final_balance;  // Итоговая сумма на конец срока
  int row_count;  // Количество строк в таблице (месяцев)
  deposit_row* rows;  // Таблица с данными по месяцам
} deposit_output;

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations go here
int calculate_deposit(deposit_input input, deposit_output* output);

#ifdef __cplusplus
}
#endif

#endif  // DEPOSIT_H
