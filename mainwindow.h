#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "chart.h"
#include "creditwindow.h"
#include "depositwindow.h"

extern "C" {
#include "calculator.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  double x_value;
  double eq_value;

 private:
  Ui::MainWindow *ui;
  Chart *window;
  creditWindow *creditwindow;
 signals:
  void signal(QString);

 private slots:
  void show_and_get_string();
  void zero_check();
  void reverse_sign();
  void on_pushButton_AC_clicked();
  void delete_symbol();
  void on_pushButton_lbracket_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_rbracket_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_ln_clicked();
  void on_pushButton_pow_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_sqrt_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_atan_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_clicked();
  void on_pushButton_x_clicked();
  void on_radioButton_clicked();
  void on_radioButton_2_clicked();
};
#endif  // MAINWINDOW_H
