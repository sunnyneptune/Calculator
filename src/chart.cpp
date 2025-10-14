#include "chart.h"

#include <string.h>

#include "ui_chart.h"

extern "C" {
#include "calculator.h"
}

Chart::Chart(QWidget *parent) : QDialog(parent), ui(new Ui::Chart) {
  ui->setupUi(this);
  ui->widget->xAxis->setRange(-50, 50);
  ui->widget->yAxis->setRange(-50, 50);
  on_Draw_clicked("here");
  connect(ui->Draw, SIGNAL(clicked()), this, SLOT(on_clicked()));
}

Chart::~Chart() { delete ui; }

void Chart::on_Draw_clicked(QString calculation) {
  ui->func_name->setText(calculation);
}

void Chart::on_clicked() {
  QString x_min = ui->xMin->text();
  QString x_max = ui->xMax->text();
  QString y_min = ui->yMin->text();
  QString y_max = ui->yMax->text();

  int is_correct = 1;

  bool is_int_x_max = false;
  long int max_x_num = x_max.toInt(&is_int_x_max);
  if (is_int_x_max == false && x_max.size() > 0) {
    ui->xMax->setText("*type error*");
    is_correct = 0;
  }

  bool is_int_x_min = false;
  long int min_x_num = x_min.toInt(&is_int_x_min);
  if (is_int_x_min == false && x_min.size() > 0) {
    ui->xMin->setText("*type error*");
    is_correct = 0;
  }

  bool is_int_y_max = false;
  long int max_y_num = y_max.toInt(&is_int_y_max);
  if (is_int_y_max == false && y_max.size() > 0) {
    ui->yMax->setText("*type error*");
    is_correct = 0;
  }

  bool is_int_y_min = false;
  long int min_y_num = y_min.toInt(&is_int_y_min);
  if (is_int_y_min == false && y_min.size() > 0) {
    ui->yMin->setText("*type error*");
    is_correct = 0;
  }

  ui->widget->xAxis->setRange(min_x_num, max_x_num);
  ui->widget->yAxis->setRange(min_y_num, max_y_num);

  QVector<double> x, y;
  char input_x[256] = "\0";
  char string[260] = "\0";
  char output[256] = "\0";
  double doub = 0;

  QByteArray input_bytes = ui->func_name->text().toUtf8();

  std::strcpy(string, input_bytes.constData());
  is_correct = validation(string);
  if (!is_correct) {
    ui->func_name->setText("*misprint*");
    ui->yMin->setText("*type error*");
    ui->yMax->setText("*type error*");
    ui->xMin->setText("*type error*");
    ui->xMax->setText("*type error*");
  } else {
    int result_code = 0;
    for (double i = min_x_num; i <= max_x_num; i += 0.11) {
      std::sprintf(input_x, "%lf", i);
      result_code = calculator(string, input_x, output);
      if (result_code == 1) {
        doub = s21_strtold(output);
        x.push_back(i);
        if (doub >= min_y_num && doub <= max_y_num) {
          y.push_back(doub);
        } else {
          y.push_back(std::numeric_limits<double>::quiet_NaN());
        }
      }
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
    x.squeeze();
    y.squeeze();
  }
}
