#include "tictactoewidget.h"
#include <QDebug>
#include <QLabel>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent), m_Player(Player::Player1), m_Winner(Winner::NoWinnerYet),
      m_Mode(Mode::TwoPlayerMode)
{
  connect(this,
          static_cast<void (TicTacToeWidget::*)(int)>(
              &TicTacToeWidget::sendAiMoves),
          this, &TicTacToeWidget::handleClicksOnBoard);
  connect(this, &TicTacToeWidget::triggerAi, this,
          &TicTacToeWidget::triggerAiMoveCalculation);
  connect(this, &TicTacToeWidget::startAiMoveCalculation, this,
          &TicTacToeWidget::calculateAiMove);

  // Audio Settings
  // QT6 Version
  /*
  m_MediaPlayer = new QMediaPlayer(this);
  m_AudioOutput = new QAudioOutput();
  m_MediaPlayer->setAudioOutput(m_AudioOutput);
  m_AudioOutput->setVolume(50);
  */
  m_MediaPlayer = new QMediaPlayer(this);
  m_MediaPlayer->setVolume(50);
}

TicTacToeWidget::~TicTacToeWidget() {}

void TicTacToeWidget::resetBoard()
{
  for (int i = 0; i < m_GameSide * m_GameSide; ++i)
  {
    m_Board.at(i)->setText(MetaData::spaceCharacter);
  }
}

void TicTacToeWidget::setCurrentPlayer(Player player)
{
  m_Player = player;
  if (m_Mode == Mode::AiMode)
  {
    emit triggerAi();
  }
}

Player TicTacToeWidget::getCurrentPlayer() const { return m_Player; }

void TicTacToeWidget::handleClicksOnBoard(int buttonIndex)
{
  if (buttonIndex < 0 || buttonIndex >= m_Board.size())
    return;

  QPushButton *button = m_Board.at(buttonIndex);
  button->setFont(QFont("Tahoma", 12, QFont::Bold));

  if (button->text() != MetaData::spaceCharacter)
    return;

  QString symbol;

  if (m_Player == Player::Player1)
  {
    // Play the sound for player 1 move
    // QT6
    /*m_MediaPlayer->setSource(QUrl("qrc:/sounds/Player1Move.mp3"));*/
    m_MediaPlayer->setMedia(QUrl("qrc:/sounds/Player1Move.mp3"));
    m_MediaPlayer->play();
    // record the move of player 1
    m_Player1LastMove = buttonIndex;
    symbol = MetaData::player1Symbol;
    button->setText(symbol);
    button->setStyleSheet(QString("QPushButton{color: ") +
                          MetaData::player1Colour +
                          "; background: lightyellow;}");
    button->setDisabled(true);
  }
  else if (m_Player == Player::Player2)
  {
    // Play the sound for player 2 move
    /*m_MediaPlayer->setSource(QUrl("qrc:/sounds/Player2Move.mp3"));*/
    m_MediaPlayer->setMedia(QUrl("qrc:/sounds/Player2Move.mp3"));
    m_MediaPlayer->play();
    // set the move of player 2
    symbol = MetaData::player2Symbol;
    button->setText(symbol);
    button->setStyleSheet(QString("QPushButton{color: ") +
                          MetaData::player2Colour +
                          "; background: lightgreen;}");
    button->setDisabled(true);
  }

  m_Winner = determineWinner(symbol, buttonIndex);
  if (m_Winner == Winner::NoWinnerYet)
  {
    if (m_Player == Player::Player1)
    {
      setCurrentPlayer(Player::Player2);
      emit changePlayer();
    }
    else if (m_Player == Player::Player2)
    {
      setCurrentPlayer(Player::Player1);
      emit changePlayer();
    }
  }
  else
  {
    if (m_Winner == Winner::WinnerPlayer1)
    {
      // m_MediaPlayer->setSource(QUrl("qrc:/sounds/Player1Win.mp3"));
      m_MediaPlayer->setMedia(QUrl("qrc:/sounds/Player1Win.mp3"));
      m_MediaPlayer->play();
    }
    else if (m_Winner == Winner::WinnerPlayer2)
    {
      // m_MediaPlayer->setSource(QUrl("qrc:/sounds/Player2Win.mp3"));
      m_MediaPlayer->setMedia(QUrl("qrc:/sounds/Player2Win.mp3"));
      m_MediaPlayer->play();
    }
    else if (m_Winner == Winner ::Draw)
    {
      // m_MediaPlayer->setSource(QUrl("qrc:/sounds/Draw.mp3"));
      m_MediaPlayer->setMedia(QUrl("qrc:/sounds/Draw.mp3"));
      m_MediaPlayer->play();
    }

    this->setDisabled(true);
    QTimer::singleShot(MetaData::FREEZETIME, this, SIGNAL(finishGame()));

    connect(this, &TicTacToeWidget::finishGame, this,
            &TicTacToeWidget::handleEndOfGame);
  }
}

void TicTacToeWidget::createBoard()
{
  QGridLayout *grid = new QGridLayout(this);

  QSignalMapper *mapper = new QSignalMapper(this);

  for (int row = 0; row < m_GameSide; ++row)
  {
    for (int column = 0; column < m_GameSide; ++column)
    {
      QPushButton *button = new QPushButton(this);

      button->setText(MetaData::spaceCharacter);
      button->setMinimumHeight(50);
      button->setMinimumWidth(50);

      grid->addWidget(button, row, column);

      mapper->setMapping(button, m_Board.size());
      connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
      connect(mapper, SIGNAL(mappedInt(int)), this,
              SLOT(handleClicksOnBoard(int)));
      m_Board.append(button);
    }
  }
}

Winner TicTacToeWidget::determineWinner(const QString &symbol, int buttonIndex)
{
  // step 1: get the row number and column number of the clicker button
  int rowNumber = buttonIndex / m_GameSide;
  int columnNumber = buttonIndex % m_GameSide;

  // counting variable
  int counter = 0;

  // horizontal check
  //  forward check
  int newColumn = columnNumber;
  bool validateSecondCheck = true;
  while (++newColumn < m_GameSide)
  {
    // position of next button
    int newPosition = rowNumber * m_GameSide + newColumn;
    // retrieve next button
    QPushButton *button = m_Board.at(newPosition);
    // check if the next button does not have the desired symbol
    if (button->text() != symbol)
    {
      validateSecondCheck = false;
      break;
    }
    else
    {
      // count the symbol on next button
      ++counter;
    }
  }
  // horizontal check;  backward check
  newColumn = columnNumber;
  while (validateSecondCheck && --newColumn >= 0)
  {
    // position of the next button in the board
    int newPosition = rowNumber * m_GameSide + newColumn;
    // retrieve the next button
    QPushButton *button = m_Board.at(newPosition);
    // Check if the next button does not have the desired symbol
    if (button->text() != symbol)
    {
      break;
    }
    else
    {
      // coutn the symbol on the next button
      ++counter;
    }
  }

  if (++counter == m_GameSide)
  {
    if (symbol == MetaData::player1Symbol)
    {
      return Winner::WinnerPlayer1;
    }
    else if (symbol == MetaData::player2Symbol)
    {
      return Winner::WinnerPlayer2;
    }
  }

  // vertical check: upward and backward
  counter = 0;
  validateSecondCheck = true;
  int newRow = rowNumber;

  // upward check
  while (--newRow >= 0)
  {
    // get the position index of the next position in the upward direction
    int newPositionIndex = newRow * m_GameSide + columnNumber;
    // retrieve the button on which the player made his move
    QPushButton *button = m_Board.at(newPositionIndex);
    if (button->text() != symbol)
    {
      validateSecondCheck = false;
      break;
    }
    else
    {
      ++counter;
    }
  }

  // downward check
  newRow = rowNumber;
  while (validateSecondCheck && ++newRow < m_GameSide)
  {
    // get the position index of the next position in the downward direction
    int newPositionIndex = newRow * m_GameSide + columnNumber;
    // retrieve the button on which the player made his move
    QPushButton *button = m_Board.at(newPositionIndex);
    if (button->text() != symbol)
    {
      validateSecondCheck = false;
      break;
    }
    else
    {
      ++counter;
    }
  }

  // did the player win vertically?
  if (++counter == m_GameSide)
  {
    if (symbol == MetaData::player1Symbol)
    {
      return Winner::WinnerPlayer1;
    }
    else if (symbol == MetaData::player2Symbol)
    {
      return Winner::WinnerPlayer2;
    }
  }

  // backlash diagonal check
  // upward direction
  counter = 0;
  validateSecondCheck = true;
  // row and column for the next position in the diagonal
  newRow = rowNumber;
  newColumn = columnNumber;
  while (--newRow >= 0 && --newColumn >= 0)
  // get the position index of the next position
  {
    int newPositionIndex = newRow * m_GameSide + newColumn;
    // retireve the button at the new position
    QPushButton *button = m_Board.at(newPositionIndex);
    if (button->text() != symbol)
    {
      validateSecondCheck = false;
      break;
    }
    else
    {
      ++counter;
    }
  }

  // downward check
  newRow = rowNumber;
  newColumn = columnNumber;

  while (validateSecondCheck && ++newRow < m_GameSide &&
         ++newColumn < m_GameSide)
  // get the position index of the next position
  {
    int newPositionIndex = newRow * m_GameSide + newColumn;
    // retireve the button at the new position
    QPushButton *button = m_Board.at(newPositionIndex);
    if (button->text() != symbol)
    {
      break;
    }
    else
    {
      ++counter;
    }
  }

  // did the player win diagonally? (backlash direction)
  if (++counter == m_GameSide)
  {
    if (symbol == MetaData::player1Symbol)
    {
      return Winner::WinnerPlayer1;
    }
    else if (symbol == MetaData::player2Symbol)
    {
      return Winner::WinnerPlayer2;
    }
  }

  // forward slash diagonal check
  // upward direction
  counter = 0;
  validateSecondCheck = true;
  newRow = rowNumber;
  newColumn = columnNumber;
  while (--newRow >= 0 && ++newColumn < m_GameSide)
  {
    // index position of the next position
    int newPositionIndex = newRow * m_GameSide + newColumn;
    // retrieve the button at the next position
    QPushButton *button = m_Board.at(newPositionIndex);
    if (button->text() != symbol)
    {
      validateSecondCheck = false;
      break; // stop the upward check
    }
    else
    {
      ++counter;
    }
  }

  // downward direction
  newRow = rowNumber;
  newColumn = columnNumber;
  while (validateSecondCheck && ++newRow < m_GameSide && --newColumn >= 0)
  {
    // index position of the next position
    int newPositionIndex = newRow * m_GameSide + newColumn;
    // retrieve the button at the next position
    QPushButton *button = m_Board.at(newPositionIndex);
    if (button->text() != symbol)
    {
      break;
    }
    else
    {
      ++counter;
    }
  }

  // did the player win diagonally? (forwar slash)
  if (++counter == m_GameSide)
  {
    if (symbol == MetaData::player1Symbol)
    {
      return Winner::WinnerPlayer1;
    }
    else if (symbol == MetaData::player2Symbol)
    {
      return Winner::WinnerPlayer2;
    }
  }

  // chekc for the draw
  for (int i = 0; i < m_GameSide * m_GameSide; i++)
  {
    if (m_Board.at(i)->text() == MetaData::spaceCharacter)
    {
      return Winner::NoWinnerYet;
    }
  }
  return Winner::Draw;
}

int TicTacToeWidget::getGameSide() const { return m_GameSide; }

void TicTacToeWidget::setGameSide(int newGameSide) { m_GameSide = newGameSide; }

Winner TicTacToeWidget::getGameOutcome() const { return m_Winner; }

void TicTacToeWidget::setGameOutcomeMessage(const QString &message)
{
  m_GameOutcomeMessage = message;
}

void TicTacToeWidget::resetContainers()
{
  m_Player1Moves.clear();
  m_AiOpponentMoves.clear();
}

void TicTacToeWidget::handleEndOfGame()
{
  // Emptying of the tictactoe window
  // Retireve Layout
  QLayout *layout = this->layout();
  // Place holder layout item
  QLayoutItem *layoutItem = nullptr;
  // Retrieve the layout items, delete their widget and then delete the layout
  // items 0 1 2 3 4 1 2 3 4 => 0 1 2 3 1 2 3 => 0 1 2
  while (layout != nullptr && (layoutItem = layout->takeAt(0)) != nullptr)
  {
    // delete the widget of the layout item
    delete layoutItem->widget();
    // delete the layout item
    delete layoutItem;
  }
  // delete the layout
  delete layout;
  // clear the board
  m_Board.clear();

  // creation of the layout for the window to display the outcome of the game
  QVBoxLayout *verticalLayout = new QVBoxLayout(this);
  verticalLayout->setAlignment(Qt::AlignCenter);

  // label and restar button
  QLabel *restartLabel = new QLabel(this);
  QPushButton *restartButton = new QPushButton("restart", this);

  QString restartLabelColour;
  QString restartButtonColour;
  if (m_Winner == Winner::WinnerPlayer1)
  {
    restartLabelColour =
        QString(" QLabel{color : ") + MetaData::player1Colour + ";}";
    restartButtonColour =
        QString(" QPushButton{color : ") + MetaData::player1Colour + ";}";
  }
  else if (m_Winner == Winner::WinnerPlayer2)
  {
    restartLabelColour =
        QString(" QLabel{color : ") + MetaData::player2Colour + ";}";
    restartButtonColour =
        QString(" QPushButton{color : ") + MetaData::player2Colour + ";}";
  }
  else if (m_Winner == Winner::Draw)
  {
    restartLabelColour =
        QString(" QLabel{color : ") + MetaData::drawColour + ";}";
    restartButtonColour =
        QString(" QPushButton{color : ") + MetaData::drawColour + ";}";
  }

  // style the button
  restartButton->setMinimumHeight(40);
  restartButton->setMinimumWidth(100);
  restartButton->setFont(QFont("Liberation Serif", 14, QFont::Bold));
  restartButton->setStyleSheet(restartButtonColour);
  // style the label
  restartLabel->setFont(QFont("Liberation Serif", 14, QFont::Bold));
  restartLabel->setStyleSheet(restartLabelColour);
  restartLabel->setText(m_GameOutcomeMessage);
  // Adjust the size of the tictactow board for full display of long names.
  this->setMinimumWidth(MetaData::endOfGameWidth);
  //  organize the widgets in the layout
  verticalLayout->addWidget(restartLabel);
  verticalLayout->addWidget(restartButton);

  // Enable the TicTacToe window
  this->setEnabled(true);
  connect(restartButton, &QPushButton::clicked, this,
          &TicTacToeWidget::startOrRestartGame);
}

void TicTacToeWidget::startOrRestartGame()
{
  // Reset the width of the game board
  this->setMinimumWidth(MetaData::widthFactor *
                        (m_GameSide + MetaData::boardSpacing));
  // set the first player to start playing
  m_Player = Player::Player1;
  emit changePlayer();
  // Reset the containers if it is the Ai mode
  if (m_Mode == Mode::AiMode)
  {
    resetContainers();
  }

  // empty the tictactoe widget if necessary
  QLayout *layout = this->layout();
  QLayoutItem *layoutItem = nullptr;

  while (layout != nullptr && (layoutItem = layout->takeAt(0)) != nullptr)
  {
    delete layoutItem->widget();
    delete layoutItem;
  }

  delete layout;
  m_Board.clear();

  // create a new board
  createBoard();
  this->setEnabled(true);
}

void TicTacToeWidget::triggerAiMoveCalculation()
{
  if (m_Player == Player::Player2)
  {
    this->setDisabled(true);
    QTimer::singleShot(MetaData::aiDelayDuration, this,
                       SIGNAL(startAiMoveCalculation()));
  }
  else if (m_Player == Player::Player1)
  {
    this->setEnabled(true);
  }
}

// TODO: Implement an Easy AI mode with this code.
/*
void TicTacToeWidget::calculateAiMove()
{ // store the move of player 1
  m_Player1Moves.push_back(m_Player1LastMove);
  // generate a random number based on the board size
  std::srand(time(NULL));
  // A number between 0 and the board size
  int randomNumber = rand() % (m_GameSide * m_GameSide);
  // The number must indicate a free spot on the board
  while (randomNumber >= m_GameSide * m_GameSide ||
         m_Player1Moves.contains(randomNumber) ||
         m_AiOpponentMoves.contains(randomNumber))
  {
    randomNumber = rand() % (m_GameSide * m_GameSide);
  }
  // store ai opponent move
  m_AiOpponentMoves.push_back(randomNumber);
  // transmit ai opponent move for handling
  transmitAiMove(randomNumber);
}
*/

void TicTacToeWidget::calculateAiMove()
{
  // Gathering of the row number and column number of the last move of player 1
  int rowNumber = m_Player1LastMove / m_GameSide;
  int columnNumber = m_Player1LastMove % m_GameSide;

  // Store the last move of player 1
  m_Player1Moves.push_back(m_Player1LastMove);

  // VERTICAL CHECK

  // Acounter for counting the occurrences of the moves of player 1 vertically
  int verticalCounter = 0;
  // A variable to skip the downward check in case the direction was already
  // defened upwards
  bool skipSecondCheck = false;
  // A variable to store the next possible move of the AI opponent
  std::unique_ptr<int> verticalMove(nullptr);
  // upward vertical check
  while (--rowNumber >= 0)
  {
    // gather the index of the next slot in the vertical upward direction
    int verticalUpwardNeighbour = rowNumber * m_GameSide + columnNumber;
    // In case Mr AI had already played in the vertical upward direction,
    // then...
    if (m_AiOpponentMoves.contains(verticalUpwardNeighbour))
    {
      verticalCounter = 0;
      verticalMove = nullptr;
      skipSecondCheck = true;
    }
    // In case the human player has played in the upward direction then
    else if (m_Player1Moves.contains(verticalUpwardNeighbour))
    {
      ++verticalCounter;
    }
    // In case the vertical upward neigbhour was still empty it may be recorded
    // as a possible move
    else if (verticalMove == nullptr)
    {
      verticalMove = std::make_unique<int>(verticalUpwardNeighbour);
    }
  }

  // Downward vertical Check - TODO: Segregate into separated functions
  // Reset the row number
  rowNumber = m_Player1LastMove / m_GameSide;
  while (!skipSecondCheck && ++rowNumber < m_GameSide)
  {
    int verticalDownwardNeighbour = rowNumber * m_GameSide + columnNumber;
    if (m_AiOpponentMoves.contains(verticalDownwardNeighbour))
    {
      verticalCounter = 0;
      verticalMove = nullptr;
    }
    else if (m_Player1Moves.contains(verticalDownwardNeighbour))
    {
      ++verticalCounter;
    }
    else if (verticalMove == nullptr)
    {
      verticalMove = std::make_unique<int>(verticalDownwardNeighbour);
    }
  }

  // HORIZONTAL CHECK

  int horizontalCounter = 0;
  std::unique_ptr<int> horizontalMove(nullptr);
  // Forward Horizontal Check
  // Reset the row number
  rowNumber = m_Player1LastMove / m_GameSide;
  skipSecondCheck = false;
  while (++columnNumber < m_GameSide)
  {
    // Gather the indez of the next slot in the horizontal forward direction
    int horizontalForwardNeighbour = rowNumber * m_GameSide + columnNumber;
    // was the horizontal forward neighbour a move of mr AI
    if (m_AiOpponentMoves.contains(horizontalForwardNeighbour))
    {
      horizontalCounter = 0;
      horizontalMove = nullptr;
      skipSecondCheck = true;
    }
    else if (m_Player1Moves.contains(horizontalForwardNeighbour))
    {
      ++horizontalCounter;
    }
    else if (horizontalMove == nullptr)
    {
      horizontalMove = std::make_unique<int>(horizontalForwardNeighbour);
    }
  }

  // Backward Horizontal Check
  // Reset Column number
  columnNumber = m_Player1LastMove % m_GameSide;
  while (!skipSecondCheck && --columnNumber >= 0)
  {
    int horizontalBackwardNeighbour = rowNumber * m_GameSide + columnNumber;
    if (m_AiOpponentMoves.contains(horizontalBackwardNeighbour))
    {
      horizontalCounter = 0;
      horizontalMove = nullptr;
    }
    else if (m_Player1Moves.contains(horizontalBackwardNeighbour))
    {
      ++horizontalCounter;
    }
    else if (horizontalMove == nullptr)
    {
      horizontalMove = std::make_unique<int>(horizontalBackwardNeighbour);
    }
  }

  // DIAGONAL CHECK

  // Forward Slash Diagonal

  // Variables creation for later use
  int forwardSlashCounter = 0;
  std::unique_ptr<int> forwardSlashMove(nullptr);
  skipSecondCheck = false;

  if (m_Player1LastMove % (m_GameSide - 1) == 0)
  {
    // Upward check
    rowNumber = m_Player1LastMove / m_GameSide;
    columnNumber = m_Player1LastMove % m_GameSide;
    while (--rowNumber >= 0 && ++columnNumber < m_GameSide)
    {
      // Get the index of the next position in the upward direction
      int forwardSlashUpwardNeighbour = rowNumber * m_GameSide + columnNumber;
      if (m_AiOpponentMoves.contains(forwardSlashUpwardNeighbour))
      {
        forwardSlashCounter = 0;
        forwardSlashMove = nullptr;
        skipSecondCheck = true;
      }
      else if (m_Player1Moves.contains(forwardSlashUpwardNeighbour))
      {
        // Count the moves of the human player (player 1) across the forward
        // slash diagonal
        ++forwardSlashCounter;
      }
      else if (forwardSlashMove == nullptr)
      {
        // The move the AI player will make if it does choose to defend the
        // forward slash diagonal
        forwardSlashMove = std::make_unique<int>(forwardSlashUpwardNeighbour);
      }
    }

    // Downward direction

    // Reset The column and row number
    rowNumber = m_Player1LastMove / m_GameSide;
    columnNumber = m_Player1LastMove % m_GameSide;
    while (!skipSecondCheck && ++rowNumber < m_GameSide && --columnNumber >= 0)
    {
      // Get the index of the next position in the upward direction
      int forwardSlashDownwardNeighbour = rowNumber * m_GameSide + columnNumber;
      if (m_AiOpponentMoves.contains(forwardSlashDownwardNeighbour))
      {
        forwardSlashCounter = 0;
        forwardSlashMove = nullptr;
      }
      else if (m_Player1Moves.contains(forwardSlashDownwardNeighbour))
      {
        ++forwardSlashCounter;
      }
      else if (forwardSlashMove == nullptr)
      {
        forwardSlashMove = std::make_unique<int>(forwardSlashDownwardNeighbour);
      }
    }
  }

  // Back Slash Diagonal - TODO: Assingment at home

  // variables creation
  int backSlashCounter = 0;
  std::unique_ptr<int> backSlashMove(nullptr);
  skipSecondCheck = false;

  if (m_Player1LastMove % (m_GameSide + 1) == 0)
  {
    // upward direction
    rowNumber = m_Player1LastMove / m_GameSide;
    columnNumber = m_Player1LastMove % m_GameSide;
    while (--rowNumber >= 0 && --columnNumber >= 0)
    {
      // get the index of the next position in the upward direction
      int backSlashUpwardNeighbour = rowNumber * m_GameSide + columnNumber;
      if (m_AiOpponentMoves.contains(backSlashUpwardNeighbour))
      {
        backSlashCounter = 0;
        backSlashMove = nullptr;
        skipSecondCheck = true;
      }
      else if (m_Player1Moves.contains(backSlashUpwardNeighbour))
      {
        // count the moves of the human player (player 1) across the back slash
        // diagonal
        ++backSlashCounter;
      }
      else if (backSlashMove == nullptr)
      {
        // the move the ai player makes if it chooses to defend the back slash
        // diagonal
        backSlashMove = std::make_unique<int>(backSlashUpwardNeighbour);
      }
    }
    // downward direction
    // reset the column number and row number
    rowNumber = m_Player1LastMove / m_GameSide;
    columnNumber = m_Player1LastMove % m_GameSide;
    while (!skipSecondCheck && ++rowNumber < m_GameSide &&
           ++columnNumber < m_GameSide)
    {
      int backSlashDownwardNeighbour = rowNumber * m_GameSide + columnNumber;
      if (m_AiOpponentMoves.contains(backSlashDownwardNeighbour))
      {
        backSlashCounter = 0;
        backSlashMove = nullptr;
      }
      else if (m_Player1Moves.contains(backSlashDownwardNeighbour))
      {
        ++backSlashCounter;
      }
      else if (backSlashMove == nullptr)
      {
        backSlashMove = std::make_unique<int>(backSlashDownwardNeighbour);
      }
    }
  }

  // Should the vertical direction be defended?
  if (verticalMove != nullptr && verticalCounter >= horizontalCounter &&
      verticalCounter >= forwardSlashCounter &&
      verticalCounter >= backSlashCounter)
  {
    transmitAiMove(*verticalMove);
    m_AiOpponentMoves.push_back(*verticalMove);
    return;
  }
  // Should the horizontal direction be defended?
  else if (horizontalMove && horizontalCounter >= verticalCounter &&
           horizontalCounter >= forwardSlashCounter &&
           horizontalCounter >= backSlashCounter)
  {
    transmitAiMove(*horizontalMove);
    m_AiOpponentMoves.push_back(*horizontalMove);
    return;
  }
  // Should the forward slash direction be defended?
  else if (forwardSlashMove && forwardSlashCounter >= verticalCounter &&
           forwardSlashCounter >= horizontalCounter &&
           forwardSlashCounter >= backSlashCounter)
  {
    transmitAiMove(*forwardSlashMove);
    m_AiOpponentMoves.push_back(*forwardSlashMove);
    return;
  }
  // Should the back slash direction be defended?
  else if (backSlashMove && backSlashCounter >= verticalCounter &&
           backSlashCounter >= horizontalCounter &&
           backSlashCounter >= forwardSlashCounter)
  {
    transmitAiMove(*backSlashMove);
    m_AiOpponentMoves.push_back(*backSlashMove);
    return;
  }

  // Select any available empty position as the AI if no direction could be
  // selected for defence
  for (int move = 0; move < m_GameSide * m_GameSide; ++move)
  {
    if (!m_Player1Moves.contains(move) && !m_AiOpponentMoves.contains(move))
    {
      transmitAiMove(move);
      m_AiOpponentMoves.push_back(move);
      break;
    }
  }
}

void TicTacToeWidget::transmitAiMove(int move) { emit sendAiMoves(move); }

void TicTacToeWidget::setAiMode() { m_Mode = Mode::AiMode; }

void TicTacToeWidget::setTwoPlayerMode() { m_Mode = Mode::TwoPlayerMode; }
