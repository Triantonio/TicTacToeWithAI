#include "GameConfiguration.hpp"
#include "tictactoewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  /*
  TicTacToeWidget w;
  w.show();
  */

  GameConfiguration *gameConfiguration = GameConfiguration::getInstance();
  gameConfiguration->show();
  gameConfiguration->setGameSide(5);
  int ret = a.exec();
  delete gameConfiguration;
  return ret;
}
