#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStringListModel>

extern "C" {
#include "credit.h"
}

namespace Ui {
class creditWindow;
}

class creditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit creditWindow(QWidget *parent = nullptr);
  ~creditWindow();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::creditWindow *ui;
  QStandardItemModel *model;
};

#endif  // CREDITWINDOW_H
