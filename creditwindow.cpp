#include "creditwindow.h"

#include <QTableWidget>

#include "ui_creditwindow.h"

// creditWindow::creditWindow(QWidget *parent)
//     : QDialog(parent), ui(new Ui::creditWindow) {
//   ui->setupUi(this);
// }

// creditWindow::~creditWindow() { delete ui; }

// void creditWindow::on_pushButton_clicked() {
//   credit_input input;
//   input.length = 0;
//   input.percent = 0;
//   input.sum = 0;
//   input.type = 0;

//  credit_output output;
//  output.monthly_pay = 0;
//  output.overpayment = 0;
//  output.total_pay = 0;

//  input.length = ui->length->text().toDouble();
//  input.percent = ui->percent->text().toDouble();
//  input.sum = ui->sum->text().toDouble();
//  if (ui->annuitet->isChecked())
//    input.type = 1;
//  else
//    input.type = 2;

//  QStringListModel *model;
//  model = new QStringListModel(this);
//  QStringList stringList;
//  //    open(QFile::ReadWrite);
//  QFile textFile("data_file.txt");
//  textFile.open(QIODevice::ReadWrite | QIODevice::Text);
//  calculate_credit(input, &output);
//  //     if(!textFile.open(QIODevice::ReadOnly)) {
//  //         QMessageBox::information(0,"Error",textFile.errorString());
//  //     }
//  //  if(textFile.exists()){
//  //    QMessageBox::information(0,"Error not
//  //    exist(())",/*textFile.errorString()*/"Error not exist(())");
//  //      qDebug() << "HERERE";
//  //  }
//  QTextStream textStream(&textFile);
//  while (true) {
//    QString line = textStream.readLine();
//    if (line.isNull())
//      break;
//    else
//      stringList.append(line);  // populate the stringlist
//  }
//  // Populate the model
//  model->setStringList(stringList);
//  // Glue model and view together
//  ui->list->setModel(model);
//  ui->overpay->setText(QString::number(output.overpayment, 'g', 15));
//  ui->totalSum->setText(QString::number(output.total_pay, 'g', 15));
//  textFile.close();
//  QFile::remove(textFile);
//}

creditWindow::creditWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::creditWindow) {
  ui->setupUi(this);
  this->setMinimumSize(800, 400);
  // Настройка таблицы
  ui->tableWidget->setColumnCount(5);
  ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                                             << "Месяц"
                                             << "Сумма платежа"
                                             << "Основной платеж"
                                             << "Платеж по процентам"
                                             << "Остаток долга");
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);  // Растяжение колонок
  ui->tableWidget->setSizeAdjustPolicy(
      QAbstractScrollArea::AdjustToContents);  // Автоматическая подгонка
                                               // размера
}

creditWindow::~creditWindow() { delete ui; }

void creditWindow::on_pushButton_clicked() {
  credit_input input;
  credit_output output = {0};

  // Получение данных из интерфейса
  input.length = ui->length->text().toInt();
  input.percent = ui->percent->text().toDouble();
  input.sum = ui->sum->text().toDouble();
  input.type = ui->annuitet->isChecked() ? 1 : 2;

  // Вызов функции расчета
  if (calculate_credit(input, &output) == 0) {
    // Настройка таблицы
    ui->tableWidget->setRowCount(output.payment_count);
    for (int i = 0; i < output.payment_count; i++) {
      ui->tableWidget->setItem(
          i, 0,
          new QTableWidgetItem(QString::number(output.payments[i].month)));
      ui->tableWidget->setItem(i, 1,
                               new QTableWidgetItem(QString::number(
                                   output.payments[i].monthly_pay, 'f', 2)));
      ui->tableWidget->setItem(i, 2,
                               new QTableWidgetItem(QString::number(
                                   output.payments[i].main_part, 'f', 2)));
      ui->tableWidget->setItem(i, 3,
                               new QTableWidgetItem(QString::number(
                                   output.payments[i].percent_pay, 'f', 2)));
      ui->tableWidget->setItem(i, 4,
                               new QTableWidgetItem(QString::number(
                                   output.payments[i].debt_remain, 'f', 2)));
    }

    // Автоматическая подгонка ширины колонок под содержимое
    ui->tableWidget->resizeColumnsToContents();

    // Отображение переплаты и общей суммы
    ui->overpay->setText(QString::number(output.overpayment, 'f', 2));
    ui->totalSum->setText(QString::number(output.total_pay, 'f', 2));

    // Освобождение памяти
    free(output.payments);
  } else {
    // Обработка ошибки выделения памяти
    ui->overpay->setText("Ошибка расчета");
    ui->totalSum->setText("Ошибка расчета");
  }
}
