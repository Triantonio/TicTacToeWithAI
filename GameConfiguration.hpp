#ifndef GAMECONFIGURATION_HPP
#define GAMECONFIGURATION_HPP

#include "qabstractbutton.h"
#include <QDialog>

namespace Ui
{
class GameConfiguration;
}

struct SideRange
{
  static constexpr int minRange = 3;
  static constexpr int maxRange = 10;
};

enum Mode
{
  TwoPlayer,
  Ai
};

class GameConfiguration : public QDialog
{
  Q_OBJECT

private:
  explicit GameConfiguration(QWidget *parent = nullptr);

public:
  ~GameConfiguration() override;

  // setters for player names

  /// \brief A function to set the name of player 1
  /// \param name
  void setPlayer1Name(const QString &name) const;
  /// \brief A function to set the name of player 2
  /// \param name
  void setPlayer2Name(const QString &name) const;

  // getters for player names
  /// \brief A function to get the name of player 1
  /// \return
  QString getPlayer1Name() const;
  /// \brief A function to get the name of player 2
  /// \return
  QString getPlayer2Name() const;

  // setter and getter for the game side
  /// \brief A function to set the game side
  /// \param side
  void setGameSide(int side) const;
  /// \brief A function which returns the game side
  /// \return Returns the game side.
  int getGameSide() const;
  /// \brief Returns the selected mode.
  /// \return
  Mode getMode() const;

  // singleton function
  /// \brief A function which returns the unique instance of the
  /// GameConfiguration class \return
  static GameConfiguration *getInstance();

private slots:
  /// \brief A function to update de Ok button of the configuration window.
  void updateOkButton();

  /// \brief Starts or Cancel the game.
  void setGame(QAbstractButton *button);

private:
  Ui::GameConfiguration *m_Ui;

  static GameConfiguration *gameConfiguration;
};

#endif // GAMECONFIGURATION_HPP
