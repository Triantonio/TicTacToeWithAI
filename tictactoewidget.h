#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QGridLayout>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QTimer>
#include <QWidget>
#include <stdlib.h>
#include <time.h>

struct MetaData
{
  static constexpr int FREEZETIME = 1500;
  static constexpr const char *spaceCharacter = " ";
  static constexpr const char *player1Symbol = "X";
  static constexpr const char *player2Symbol = "O";
  static constexpr const char *player1Colour = "blue";
  static constexpr const char *player2Colour = "red";
  static constexpr const char *drawColour = "purple";
  static constexpr int endOfGameWidth = 500;
  static constexpr int widthFactor = 50;
  static constexpr int boardSpacing = 1;
  static constexpr int aiDelayDuration = 1000;
};

/// \brief An enum to represent the player.
enum Player
{
  Player1,
  Player2
};

enum Mode
{
  AiMode,
  TwoPlayerMode
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
  Player getCurrentPlayer() const;

  /// \brief GameSide
  /// \return
  int getGameSide() const;
  /// \brief setGameSide
  /// \param newGameSide
  void setGameSide(int newGameSide);
  /// \brief A function to return the game outcome
  /// \return
  Winner getGameOutcome() const;
  /// \brief a function to set the game outcome message
  /// \param message
  void setGameOutcomeMessage(const QString &message);
  /// \brief Resets the containers
  void resetContainers();

signals:
  /// \brief A signal to signal the end of the game session.
  void finishGame();
  /// \brief A signal to signal that it is the turn of another player.
  void changePlayer();
  /// \brief Transmits AI Moves
  /// \param AI Move
  void sendAiMoves(int move);
  /// \brief Triggers AI.
  void triggerAi();
  /// \brief Triggers the start of ai move calculation
  void startAiMoveCalculation();

public slots:
  /// \brief A function to manage the restart of the game
  void startOrRestartGame();
  /// \brief Sets the Ai Mode.
  void setAiMode();
  /// \brief Reset to the two player mode.
  void setTwoPlayerMode();

private slots:
  /// \brief A slot to handle clicks on the board.
  void handleClicksOnBoard(int);
  /// \brief A slot to hande the end of the game.
  void handleEndOfGame();
  /// \brief Triggers Ai Move Calculation.
  void triggerAiMoveCalculation();
  /// \brief Computers AI move.
  void calculateAiMove();
  /// \brief A function that transmits the ai opponent move.
  /// \param Ai Move
  void transmitAiMove(int move);

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
  /// \brief An object to represent the outcome winner.
  int m_GameSide;
  /// \brief An attribute to store the game outcome message
  QString m_GameOutcomeMessage;
  /// \brief Mode Attribute
  Mode m_Mode;
  /// \brief A container to store the moves of player 1
  QList<int> m_Player1Moves;
  /// \brief A variable to store the last move of player 1
  int m_Player1LastMove;
  /// \brief A container to store the moves of the AI opponent
  QList<int> m_AiOpponentMoves;
};
#endif // TICTACTOEWIDGET_H
