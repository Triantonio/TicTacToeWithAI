/// @file main.cpp
/// @brief Application entry point.

#include "MainWindow.hpp"
#include <QApplication>

#if defined(_MSC_VER) && (defined(QT_DEBUG) || defined(_DEBUG))
#include "Infrastructure/ReportingHook.h"
#include "Infrastructure/SetDebugNew.h"
#endif
int main(int argc, char *argv[])
{
#if defined(_MSC_VER) && (defined(QT_DEBUG) || defined(_DEBUG))
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  setFilterDebugHook();
#endif

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
