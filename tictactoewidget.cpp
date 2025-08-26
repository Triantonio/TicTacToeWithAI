#include "tictactoewidget.h"
#include <QDebug>
#include <QLabel>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent), m_Player(Player::Player1), m_Winner(Winner::NoWinnerYet)
{
}

TicTacToeWidget::~TicTacToeWidget() {}

void TicTacToeWidget::resetBoard()
{
  for (int i = 0; i < m_GameSide * m_GameSide; ++i)
  {
    m_Board.at(i)->setText(MetaData::spaceCharacter);
  }
}

void TicTacToeWidget::setCurrentPlayer(Player player) { m_Player = player; }

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
    symbol = MetaData::player1Symbol;
    button->setText(symbol);
    button->setStyleSheet(QString("QPushButton{color: ") +
                          MetaData::player1Colour +
                          "; background: lightyellow;}");
    button->setDisabled(true);
  }
  else if (m_Player == Player::Player2)
  {
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
