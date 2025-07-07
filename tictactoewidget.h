#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QGridLayout>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QTimer>
#include <QWidget>

struct MetaData
{
  static constexpr int ROWS = 3;
  static constexpr int COLUMNS = 3;
  static constexpr int ROWSCOLUMNS = 3; // LA DIAGONAL
  static constexpr int BOARDSIZE = ROWSCOLUMNS * ROWSCOLUMNS;
  static constexpr int FREEZETIME = 1500;
  static constexpr const char *spaceCharacter = " ";
  static constexpr const char *player1Symbol = "X";
  static constexpr const char *player2Symbol = "O";
  static constexpr const char *player1Colour = "blue";
  static constexpr const char *player2Colour = "red";
  static constexpr const char *drawColour = "purple";
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

signals:
  void finishGame();

private slots:
  /// \brief A slot to handle clicks on the board.
  void handleClicksOnBoard(int);
  /// \brief A slot to hande the end of the game.
  void handleEndOfGame();
  /// \brief A function to manage the restart of the game
  void restartGame();

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

  /// \brief An object to represent the outcome winner.
  Winner m_Winner;
};
#endif // TICTACTOEWIDGET_H
