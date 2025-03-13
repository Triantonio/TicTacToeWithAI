#include "tictactoewidget.h"
#include <QDebug>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{
  m_Player = Player::Player1;
  createBoard();
}

TicTacToeWidget::~TicTacToeWidget() {}

void TicTacToeWidget::resetBoard()
{
  for (int i = 0; i < MetaData::ROWS * MetaData::COLUMNS; ++i)
  {
    m_Board.at(i)->setText(MetaData::spaceCharacter);
  }
}

void TicTacToeWidget::setCurrentPlayer(Player player) { m_Player = player; }

Player TicTacToeWidget::getPlayer() const { return m_Player; }

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
    symbol = "X";
    button->setText(symbol);
    button->setStyleSheet("QPushButton{color: blue; background: lightyellow;}");
    button->setDisabled(true);
    setCurrentPlayer(Player::Player2);
  }
  else if (m_Player == Player::Player2)
  {
    symbol = "O";
    button->setText(symbol);
    button->setStyleSheet("QPushButton{color: red; background: lightgreen;}");
    button->setDisabled(true);
    setCurrentPlayer(Player::Player1);
  }

  Winner winner = determineWinner(symbol, buttonIndex);
  if (winner == Winner::NoWinnerYet)
  {
  }
  else
  {
    if (winner == Winner::WinnerPlayer1)
    {
      qDebug() << "Player 1 Wins";
    }
  }
}

void TicTacToeWidget::createBoard()
{
  QGridLayout *grid = new QGridLayout(this);

  QSignalMapper *mapper = new QSignalMapper(this);

  for (int row = 0; row < MetaData::ROWS; ++row)
  {
    for (int column = 0; column < MetaData::COLUMNS; ++column)
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
  int rowNumber = buttonIndex / MetaData::COLUMNS;
  int columnNumber = buttonIndex % MetaData::COLUMNS;

  // counting variable
  int counter = 0;

  // horizontal check
  //  forward check
  int newColumn = columnNumber;
  bool validateSecondCheck = true;
  while (++newColumn < MetaData::COLUMNS)
  {
    // position of next button
    int newPosition = rowNumber * MetaData::COLUMNS + newColumn;
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
    int newPosition = rowNumber * MetaData::COLUMNS + newColumn;
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
  if (++counter == MetaData::COLUMNS)
  {
    if (symbol == "X")
    {
      return Winner::WinnerPlayer1;
    }
    else if (symbol == "O")
    {
      return Winner::WinnerPlayer2;
    }
  }
  return Winner::NoWinnerYet;
}
