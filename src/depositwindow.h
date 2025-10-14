#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDialog>
#include <QTableWidgetItem>

#include "deposit.h"

namespace Ui {
class depositWindow;
}

class depositWindow : public QDialog {
  Q_OBJECT

 public:
  explicit depositWindow(QWidget *parent = nullptr);
  ~depositWindow();

 private slots:
  void on_calculateButton_clicked();
  void on_addDepositButton_clicked();
  void on_addWithdrawalButton_clicked();
  void on_removeDepositButton_clicked();
  void on_removeWithdrawalButton_clicked();

 private:
  Ui::depositWindow *ui;
  QList<transaction> depositList;
  QList<transaction> withdrawalList;
};

#endif  // DEPOSITWINDOW_H
