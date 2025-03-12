#include "tictactoewidget.h"

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

Winner TicTacToeWidget::determineWinner(const QString &, int) {}
