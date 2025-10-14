#include "depositwindow.h"

#include "ui_depositwindow.h"

depositWindow::depositWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::depositWindow) {
  ui->setupUi(this);

  this->setMinimumSize(800, 600);

  // Настройка таблицы результатов
  ui->resultTable->setColumnCount(6);
  ui->resultTable->setHorizontalHeaderLabels(QStringList() << "Месяц"
                                                           << "Баланс (начало)"
                                                           << "Начислено %"
                                                           << "Пополнение"
                                                           << "Снятие"
                                                           << "Баланс (конец)");
  ui->resultTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->resultTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
  // Настройка таблиц для пополнений и снятий
  ui->depositTable->setColumnCount(2);
  ui->depositTable->setHorizontalHeaderLabels(QStringList() << "Месяц"
                                                            << "Сумма");
  ui->depositTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);

  ui->withdrawalTable->setColumnCount(2);
  ui->withdrawalTable->setHorizontalHeaderLabels(QStringList() << "Месяц"
                                                               << "Сумма");
  ui->withdrawalTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  connect(ui->removeDepositButton, &QPushButton::clicked, this,
          &depositWindow::on_removeDepositButton_clicked);
  connect(ui->removeWithdrawalButton, &QPushButton::clicked, this,
          &depositWindow::on_removeWithdrawalButton_clicked);
}

depositWindow::~depositWindow() { delete ui; }

void depositWindow::on_calculateButton_clicked() {
  deposit_input input;
  deposit_output output = {0};

  // Сбор данных из интерфейса
  input.initial_sum = ui->initialSum->text().toDouble();
  input.term = ui->term->text().toInt();
  input.interest_rate = ui->interestRate->text().toDouble();
  input.tax_rate = ui->taxRate->text().toDouble();
  input.payment_frequency = ui->frequency->currentText().toInt();
  input.capitalization = ui->capitalization->isChecked() ? 1 : 0;

  // Подготовка списков пополнений и снятий
  input.deposit_count = depositList.size();
  input.deposits =
      (transaction *)malloc(input.deposit_count * sizeof(transaction));
  for (int i = 0; i < input.deposit_count; i++) {
    input.deposits[i] = depositList[i];
  }

  input.withdrawal_count = withdrawalList.size();
  input.withdrawals =
      (transaction *)malloc(input.withdrawal_count * sizeof(transaction));
  for (int i = 0; i < input.withdrawal_count; i++) {
    input.withdrawals[i] = withdrawalList[i];
  }
  // Вызов функции расчета
  if (calculate_deposit(input, &output) == 0) {
    // Заполнение таблицы результатов
    ui->resultTable->setRowCount(output.row_count);
    for (int i = 0; i < output.row_count; i++) {
      ui->resultTable->setItem(
          i, 0, new QTableWidgetItem(QString::number(output.rows[i].month)));
      ui->resultTable->setItem(i, 1,
                               new QTableWidgetItem(QString::number(
                                   output.rows[i].balance, 'f', 2)));
      ui->resultTable->setItem(i, 2,
                               new QTableWidgetItem(QString::number(
                                   output.rows[i].interest, 'f', 2)));
      ui->resultTable->setItem(i, 3,
                               new QTableWidgetItem(QString::number(
                                   output.rows[i].deposit, 'f', 2)));
      ui->resultTable->setItem(i, 4,
                               new QTableWidgetItem(QString::number(
                                   output.rows[i].withdrawal, 'f', 2)));
      ui->resultTable->setItem(i, 5,
                               new QTableWidgetItem(QString::number(
                                   output.rows[i].final_balance, 'f', 2)));
    }
    ui->resultTable->resizeColumnsToContents();

    // Вывод итоговых данных
    ui->totalInterest->setText(QString::number(output.total_interest, 'f', 2));
    ui->taxAmount->setText(QString::number(output.tax_amount, 'f', 2));
    ui->finalBalance->setText(QString::number(output.final_balance, 'f', 2));
    free(output.rows);
  } else {
    ui->totalInterest->setText("Ошибка расчета");
    ui->taxAmount->setText("Ошибка расчета");
    ui->finalBalance->setText("Ошибка расчета");
  }

  // Освобождение памяти
  free(input.deposits);
  free(input.withdrawals);
}
void depositWindow::on_addDepositButton_clicked() {
  transaction t;
  t.month = ui->depositMonth->text().toInt();
  t.amount = ui->depositAmount->text().toDouble();
  depositList.append(t);

  // Обновление таблицы пополнений
  ui->depositTable->setRowCount(depositList.size());
  for (int i = 0; i < depositList.size(); i++) {
    ui->depositTable->setItem(
        i, 0, new QTableWidgetItem(QString::number(depositList[i].month)));
    ui->depositTable->setItem(
        i, 1,
        new QTableWidgetItem(QString::number(depositList[i].amount, 'f', 2)));
  }
}

void depositWindow::on_addWithdrawalButton_clicked() {
  transaction t;
  t.month = ui->withdrawalMonth->text().toInt();
  t.amount = ui->withdrawalAmount->text().toDouble();
  withdrawalList.append(t);

  // Обновление таблицы снятий
  ui->withdrawalTable->setRowCount(withdrawalList.size());
  for (int i = 0; i < withdrawalList.size(); i++) {
    ui->withdrawalTable->setItem(
        i, 0, new QTableWidgetItem(QString::number(withdrawalList[i].month)));
    ui->withdrawalTable->setItem(i, 1,
                                 new QTableWidgetItem(QString::number(
                                     withdrawalList[i].amount, 'f', 2)));
  }
}

void depositWindow::on_removeDepositButton_clicked() {
  int selectedRow = ui->depositTable->currentRow();
  if (selectedRow >= 0 && selectedRow < depositList.size()) {
    depositList.removeAt(selectedRow);
    ui->depositTable->removeRow(selectedRow);

    // Пересчитываем результат
    on_calculateButton_clicked();
  }
}

void depositWindow::on_removeWithdrawalButton_clicked() {
  int selectedRow = ui->withdrawalTable->currentRow();
  if (selectedRow >= 0 && selectedRow < withdrawalList.size()) {
    withdrawalList.removeAt(selectedRow);
    ui->withdrawalTable->removeRow(selectedRow);

    // Пересчитываем результат
    on_calculateButton_clicked();
  }
}
