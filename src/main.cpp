/// @file main.cpp
/// @brief Application entry point.

#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/image/Icon.ico"));

  /*
  TicTacToeWidget w;
  w.show();
  */

  /*
  GameConfiguration *gameConfiguration = GameConfiguration::getInstance();
  gameConfiguration->show();
  gameConfiguration->setGameSide(5);
  int ret = a.exec();
  delete gameConfiguration;
  */
  MainWindow window;
  window.show();
  return a.exec();
}
