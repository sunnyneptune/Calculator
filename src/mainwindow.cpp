#include "mainwindow.h"

#include <QTextEdit>

#include "./ui_mainwindow.h"
// #include "calculator.h"

extern "C" {
#include "calculator.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setMinimumSize(400, 500);
  ui->result_show->setAlignment(Qt::AlignLeft);
  ui->result_show_2->setAlignment(Qt::AlignLeft);

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));

  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(show_and_get_string()));

  connect(ui->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(delete_symbol()));

  connect(ui->pushButton_plusminus, SIGNAL(clicked()), this,
          SLOT(reverse_sign()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this,
          SLOT(on_pushButton_AC_clicked()));

  // When clicked we will summon the method
}

MainWindow::~MainWindow() { delete ui; }
// Главный метод - MainWindow
// создаем метод для обработки нажатий на кнопки

void MainWindow::zero_check() {
  if ((ui->result_show->text()).size() == 1 && ui->result_show->text() == "0") {
    ui->result_show->setText("");
  }
}

void MainWindow::show_and_get_string() {
  // sender(); получить кнопку, на которую нажали, будет наследоваться от класса
  // QPushButton
  zero_check();
  QPushButton *current_button = (QPushButton *)sender();
  double all_numbers;  // записываем в числовой формат
  QString new_label;   // записываем в формат строки
  QString x_label;
  if (current_button->text() == "+" || current_button->text() == "-" ||
      current_button->text() == "*" || current_button->text() == "/") {
    new_label = (ui->result_show->text() + current_button->text());
    ui->result_show->setText(new_label);
  } else {
    if (x_value == 1 && eq_value != 1) {
      if (current_button->text() == ".") {
        ui->label->setText(ui->label->text() + ".");
      } else {
        all_numbers = (current_button->text().toDouble());
        x_label = (ui->label->text() + QString::number(all_numbers, 'g', 15));
        ui->label->setText(x_label);
      }
    } else {
      if (current_button->text() == ".") {
        ui->result_show->setText(ui->result_show->text() + ".");
      } else {
        all_numbers = (current_button->text().toDouble());
        new_label =
            (ui->result_show->text() + QString::number(all_numbers, 'g', 15));
        ui->result_show->setText(new_label);
      }
    }
  }
}

void MainWindow::delete_symbol() {
  QString string = ui->result_show->text();
  string.chop(1);
  ui->result_show->setText(string);
}

void MainWindow::reverse_sign() {
  zero_check();
  QString calc_text = ui->result_show->text();
  if (!calc_text.size()) return;
  if (calc_text.at(0) != '-' || calc_text.at(1) != '(') {
    if (calc_text.size() == 1)
      calc_text.insert(0, QString("-"));
    else {
      calc_text.insert(0, QString("-("));
      calc_text.append(")");
    }
  } else {
    if (calc_text.at((calc_text.size()) - 1) != ')') {
      calc_text.insert(0, QString("-("));
      calc_text.append(")");
    } else {
      calc_text.remove(0, 2);
      calc_text.chop(1);
    }
  }
  ui->result_show->setText(calc_text);
}

void MainWindow::on_pushButton_AC_clicked() {
  // выключить все кнопки

  ui->result_show_2->setText("0");
  ui->label->setText("");
  ui->result_show->setText("0");
  x_value = 0;
  eq_value = 0;
}

void MainWindow::on_pushButton_equal_clicked() {
  if (x_value == 1) {
    x_value = 0;
    eq_value = 1;
  } else {
    QString calc_text = ui->result_show->text();
    QString what_in_x = ui->label->text();

    char input_str[500] = "\0";
    char output_str[500] = "\0";
    char x[200] = "\0";

    QByteArray input_bytes = calc_text.toUtf8();
    QByteArray x_bytes = what_in_x.toUtf8();

    std::strcpy(input_str, input_bytes.constData());
    std::strcpy(x, x_bytes.constData());

    int result = 1;
    result = calculator(input_str, x, output_str);

    if (result == 0) {
      ui->result_show_2->setText("Error");
    } else {
      ui->result_show_2->setText(QString(output_str));
    }
  }
}

void MainWindow::on_pushButton_lbracket_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "("));
}

void MainWindow::on_pushButton_rbracket_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + ")"));
}

void MainWindow::on_pushButton_acos_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "acos("));
}

void MainWindow::on_pushButton_cos_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "cos("));
}

void MainWindow::on_pushButton_sin_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "sin("));
}

void MainWindow::on_pushButton_asin_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "asin("));
}

void MainWindow::on_pushButton_ln_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "ln("));
}

void MainWindow::on_pushButton_pow_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "^"));
}

void MainWindow::on_pushButton_log_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "log("));
}

void MainWindow::on_pushButton_sqrt_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "sqrt("));
}

void MainWindow::on_pushButton_tan_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "tan("));
}

void MainWindow::on_pushButton_atan_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "atan("));
}

void MainWindow::on_pushButton_clicked() {
  window = new Chart(this);
  window->show();
  connect(this, &MainWindow::signal, window, &Chart::on_Draw_clicked);
  emit signal(ui->result_show->text());
}

void MainWindow::on_pushButton_mod_clicked() {
  zero_check();
  ui->result_show->setText((ui->result_show->text() + "mod("));
}

void MainWindow::on_pushButton_x_clicked() {
  QString value;
  zero_check();
  if ((ui->label->text()).size() == 1 && ui->label->text() == "0") {
    ui->label->setText("");
  }
  ui->result_show->setText((ui->result_show->text() + "x"));
  x_value = 1;
}

void MainWindow::on_radioButton_clicked() {
  creditWindow *creditwindow = new creditWindow(this);
  creditwindow->show();
}

void MainWindow::on_radioButton_2_clicked() {
  depositWindow *depositwindow = new depositWindow(this);
  depositwindow->show();
}
