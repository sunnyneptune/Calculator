#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);  // класс QApplication
  MainWindow w;                // класс MainWindow
  w.show();

  return a.exec();
}
