#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QGridLayout>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QWidget>

struct MetaData
{
  static constexpr int ROWS = 3;
  static constexpr int COLUMNS = 3;
  static constexpr const char *spaceCharacter = " ";
  static constexpr const char *player1Symbol = "X";
  static constexpr const char *player2Symbol = "O";
};

/// \brief An enum to represent the player.
enum Player
{
  Player1,
  Player2
};

/// \brief An enum to represent the winner.
enum Winner
{
  WinnerPlayer1,
  WinnerPlayer2,
  Draw,
  NoWinnerYet
};

class TicTacToeWidget : public QWidget
{
  Q_OBJECT

public:
  TicTacToeWidget(QWidget *parent = nullptr);
  ~TicTacToeWidget() override;

  /// \brief A function that resets the board.
  void resetBoard();

  /// \brief Defines which player has to move.
  /// \param Player moving.
  void setCurrentPlayer(Player player);

  /// \brief  Getter function where it returns which player has to move.
  /// \return Returns which player has to move.
  Player getPlayer() const;

private slots:
  /// \brief A slot to handle clicks on the board.
  void handleClicksOnBoard(int);

private:
  /// \brief A function which creates the board of the tictactoegame
  void createBoard();

  /// \brief Determines the Winner of the game.
  /// \return Returns the result.
  Winner determineWinner(const QString &, int);

  /// \brief The game board.
  QList<QPushButton *> m_Board;

  /// \brief An object to represent the player.
  Player m_Player;
};
#endif // TICTACTOEWIDGET_H
