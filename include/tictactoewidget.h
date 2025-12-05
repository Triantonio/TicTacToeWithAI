#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

/// @file tictactoewidget.h
/// @brief Declares the TicTacToeWidget responsible for rendering the board.

#include <QAudioOutput>
#include <QGridLayout>
#include <QList>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSignalMapper>
#include <QTimer>
#include <QUrl>
#include <QWidget>
#include <memory>
#include <stdlib.h>
#include <time.h>

/// @struct MetaData
/// @brief Stores constants used to configure gameplay and visuals.
struct MetaData
{
  static constexpr int FREEZETIME = 1500;              ///< Pause duration between games.
  static constexpr const char *spaceCharacter = " ";  ///< Placeholder symbol.
  static constexpr const char *player1Symbol = "X";    ///< Player 1 board symbol.
  static constexpr const char *player2Symbol = "O";    ///< Player 2 board symbol.
  static constexpr const char *player1Colour = "blue"; ///< Player 1 highlight color.
  static constexpr const char *player2Colour = "red";  ///< Player 2 highlight color.
  static constexpr const char *drawColour = "purple";  ///< Draw highlight color.
  static constexpr int endOfGameWidth = 500;           ///< Width of the end game dialog.
  static constexpr int widthFactor = 50;               ///< Button width scaling factor.
  static constexpr int boardSpacing = 1;               ///< Spacing between board tiles.
  static constexpr int aiDelayDuration = 1000;         ///< Delay before AI performs a move.
};

/// @enum Player
/// @brief Identifies the player that should perform the next move.
enum Player
{
  Player1, ///< Player one.
  Player2  ///< Player two.
};

/// @enum Mode
/// @brief Represents the game mode in which the widget operates.
enum Mode
{
  AiMode,      ///< Standard AI opponent.
  TwoPlayerMode, ///< Human vs. human mode.
  EasyAiMode   ///< Simplified AI opponent.
};

/// @enum Winner
/// @brief Enumerates the possible results of a game session.
enum Winner
{
  WinnerPlayer1, ///< Player one won the game.
  WinnerPlayer2, ///< Player two won the game.
  Draw,          ///< The match ended in a draw.
  NoWinnerYet    ///< The game is still ongoing.
};

/// @class TicTacToeWidget
/// @brief Visual component that renders the grid and coordinates gameplay.
class TicTacToeWidget : public QWidget
{
  Q_OBJECT

public:
  /// @brief Builds the widget and initializes the board controls.
  /// @param parent Optional parent widget for Qt ownership.
  TicTacToeWidget(QWidget *parent = nullptr);
  /// @brief Releases resources and owned Qt objects.
  ~TicTacToeWidget() override;

  /// @brief Resets the board to its initial empty state.
  void resetBoard();

  /// @brief Sets which player should move next.
  /// @param player Identifier of the player that should move.
  void setCurrentPlayer(Player player);

  /// @brief Retrieves the player that should move next.
  /// @return Player enum describing the current player.
  Player getCurrentPlayer() const;

  /// @brief Retrieves the configured board side length.
  /// @return Board dimension in cells.
  int getGameSide() const;
  /// @brief Updates the board side length.
  /// @param newGameSide Requested new board dimension.
  void setGameSide(int newGameSide);
  /// @brief Retrieves the outcome of the last finished game.
  /// @return Winner enumeration describing the result.
  Winner getGameOutcome() const;
  /// @brief Stores the textual message describing the game outcome.
  /// @param message Text presented to the players.
  void setGameOutcomeMessage(const QString &message);
  /// @brief Clears internal containers tracking board state.
  void resetContainers();

signals:
  /// @brief Emitted when the game session finishes.
  void finishGame();
  /// @brief Emitted when the current player changes.
  void changePlayer();
  /// @brief Announces the move computed by the AI.
  /// @param move Index representing the board position.
  void sendAiMoves(int move);
  /// @brief Requests the easy AI to generate a move.
  void triggerEasyAi();
  /// @brief Requests the regular AI to generate a move.
  void triggerAi();
  /// @brief Signals that AI move calculation should begin.
  void startAiMoveCalculation();
  /// @brief Signals that easy AI move calculation should begin.
  void startEasyAiMoveCalculation();

public slots:
  /// @brief Initiates a new game or restarts the current one.
  void startOrRestartGame();
  /// @brief Switches the widget to the easy AI mode.
  void setEasyAiMode();
  /// @brief Switches the widget to the standard AI mode.
  void setAiMode();
  /// @brief Switches the widget to two-player mode.
  void setTwoPlayerMode();

private slots:
  /// @brief Handles button clicks on the board.
  /// @param index Index of the clicked tile.
  void handleClicksOnBoard(int index);
  /// @brief Performs cleanup when the game ends.
  void handleEndOfGame();
  /// @brief Initiates the move calculation for the easy AI.
  void triggerEasyAiMoveCalculation();
  /// @brief Initiates the move calculation for the regular AI.
  void triggerAiMoveCalculation();
  /// @brief Computes the move for the easy AI opponent.
  void calculateEasyAiMove();
  /// @brief Computes the move for the regular AI opponent.
  void calculateAiMove();
  /// @brief Broadcasts the move chosen by the AI opponent.
  /// @param move Board index chosen by the AI.
  void transmitAiMove(int move);

private:
  /// @brief Creates the board UI elements and layout.
  void createBoard();
  /// @brief Determines whether the game has a winner.
  /// @param boardSymbol Symbol used by the player.
  /// @param move Last move index to evaluate.
  /// @return Winner enumeration describing the outcome.
  Winner determineWinner(const QString &boardSymbol, int move);
  /// @brief Switches to the next player and notifies listeners.
  void togglePlayer();
  /// @brief Plays the sound associated with a finished game outcome.
  /// @param winner The detected game result.
  void playOutcomeSound(Winner winner);
  /// @brief Applies consistent styling and audio feedback to a move.
  /// @param button Button that was activated by the player.
  /// @param symbol Symbol to render on the button.
  /// @param color Foreground color for the text.
  /// @param background Background color for the tile.
  /// @param sound Url of the sound effect to play.
  void applyMoveStyling(QPushButton *button, const QString &symbol,
                       const QString &color, const QString &background,
                       const QUrl &sound);
  /// @brief Clears the current layout and board widgets.
  void clearCurrentLayout();

  struct OutcomeColors
  {
    QString labelStyle;
    QString buttonStyle;
  };

  /// @brief Retrieves the colors associated with a game outcome.
  /// @param winner Outcome of the game.
  /// @return Styling configuration for labels and buttons.
  OutcomeColors outcomeColorsFor(Winner winner) const;

  /// @brief Builds the label shown at the end of the game.
  /// @param message Message to display.
  /// @param styleSheet Style to apply to the label.
  QLabel *createOutcomeLabel(const QString &message, const QString &styleSheet);

  /// @brief Builds the restart button shown at the end of the game.
  /// @param styleSheet Style to apply to the button.
  QPushButton *createOutcomeButton(const QString &styleSheet);

  QList<QPushButton *> m_Board; ///< Collection of board buttons.
  Player m_Player;              ///< Player scheduled to move next.
  Winner m_Winner;              ///< Outcome of the current game.
  int m_GameSide;               ///< Size of the board side.
  QString m_GameOutcomeMessage; ///< User-facing message of the game outcome.
  Mode m_Mode;                  ///< Active gameplay mode.
  QList<int> m_Player1Moves;    ///< History of moves performed by player one.
  int m_Player1LastMove;        ///< Last move performed by player one.
  QList<int> m_AiOpponentMoves; ///< History of moves performed by the AI.

  QMediaPlayer *m_MediaPlayer; ///< Audio/visual feedback for gameplay.
  QAudioOutput *m_AudioOutput; ///< Output device used by the media player.
};

#endif // TICTACTOEWIDGET_H
