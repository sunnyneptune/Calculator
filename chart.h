#ifndef CHART_H
#define CHART_H

#include <QDialog>

extern "C" {
#include "calculator.h"
}

namespace Ui {
class Chart;
}

class Chart : public QDialog {
  Q_OBJECT

 public:
  explicit Chart(QWidget *parent = nullptr);
  ~Chart();

 public slots:
  void on_Draw_clicked(QString s);

  // private slots:
  //     void on_Draw_clicked();

 private slots:
  void on_clicked();

 private:
  Ui::Chart *ui;
  double xBegin, xEnd, h, X;
  int N;  // количество точек
  QVector<double> x, y;
};

#endif  // CHART_H
