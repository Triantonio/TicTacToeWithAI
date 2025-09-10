#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "GameConfiguration.hpp"
#include <QMainWindow>

struct Data
{
  static constexpr int widthFactor = 50;
  static constexpr int boardSpacing = 1;
};

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

signals:
  /// \brief Signal that triggers when starting the AI Mode
  void startAiMode();
  /// \brief Signal that triggers when starting the Easy AI Mode
  void startEasyAiMode();

private slots:
  /// \brief A function that manages the start of a new game.
  void startNewGame();

  /// \brief Shows which player turn is by bolding his name .
  void boldCurrentPlayerName();

  /// \brief A function to determine the game outcome message.
  void determineGameOutcomeMessage();

  /// \brief Quits the Game and close the app
  void quitGame();

private:
  Ui::MainWindow *m_Ui;

  GameConfiguration *m_GameConfiguration;
};

#endif // MAINWINDOW_HPP
