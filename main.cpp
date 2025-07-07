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

  GameConfiguration gameConfiguration;
  gameConfiguration.show();

  return a.exec();
}
