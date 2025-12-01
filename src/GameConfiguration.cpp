/// @file GameConfiguration.cpp
/// @brief Defines the logic for the game configuration dialog.

#include "GameConfiguration.hpp"
#include "qdebug.h"
#include "ui_GameConfiguration.h"
#include <QPushButton>

#if defined(_MSC_VER) && (defined(QT_DEBUG) || defined(_DEBUG))
#include "Infrastructure/SetDebugNew.h"
#endif
GameConfiguration::GameConfiguration(QWidget *parent)
    : QDialog(parent), m_Ui(new Ui::GameConfiguration)
{
  m_Ui->setupUi(this);

  // ensure that the okbutton is disabled at the start
  updateOkButton();

  m_Ui->spinBox->setRange(SideRange::minRange, SideRange::maxRange);
  m_Ui->horizontalSlider->setRange(SideRange::minRange, SideRange::maxRange);

  m_Ui->twoPlayerModerRadioButton->setChecked(true);

  connect(m_Ui->player1LineEdit, &QLineEdit::textChanged, this,
          &GameConfiguration::updateOkButton);
  connect(m_Ui->player2LineEdit, &QLineEdit::textChanged, this,
          &GameConfiguration::updateOkButton);

  connect(m_Ui->buttonBox, &QDialogButtonBox::clicked, this,
          &GameConfiguration::setGame);

  connect(m_Ui->horizontalSlider, &QSlider::valueChanged, m_Ui->spinBox,
          &QSpinBox::setValue);
  connect(m_Ui->spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          m_Ui->horizontalSlider, &QSlider::setValue);

  connect(m_Ui->aiModeRadioButton, &QRadioButton::clicked, this,
          &GameConfiguration::setAIMode);
  connect(m_Ui->aiEasyModeRadioButton, &QRadioButton::clicked, this,
          &GameConfiguration::setEasyAIMode);
  connect(m_Ui->twoPlayerModerRadioButton, &QRadioButton::clicked, this,
          &GameConfiguration::setTwoPlayerMode);

  // Another way of making the connect.
  // connect(m_Ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
  //     [this](int value) { m_Ui->horizontalSlider->setValue(value); });
}

GameConfiguration::~GameConfiguration() { delete m_Ui; }

void GameConfiguration::updateOkButton()
{
  bool player1NameEntered = m_Ui->player1LineEdit->text().isEmpty();
  bool player2NameEntered = m_Ui->player2LineEdit->text().isEmpty();
  // Retrieve the Ok Button
  QPushButton *okButton = m_Ui->buttonBox->button(QDialogButtonBox::Ok);
  okButton->setDisabled(player1NameEntered || player2NameEntered);
}

void GameConfiguration::setPlayer1Name(const QString &name) const
{
  m_Ui->player1LineEdit->setText(name);
}

void GameConfiguration::setPlayer2Name(const QString &name) const
{
  m_Ui->player2LineEdit->setText(name);
}

QString GameConfiguration::getPlayer1Name() const
{
  return m_Ui->player1LineEdit->text();
}

QString GameConfiguration::getPlayer2Name() const
{
  return m_Ui->player2LineEdit->text();
}

void GameConfiguration::setGameSide(int side) const
{
  if (side < SideRange::minRange || side > SideRange::maxRange)
    return;

  m_Ui->spinBox->setValue(side);
  m_Ui->horizontalSlider->setValue(side);
}

int GameConfiguration::getGameSide() const { return m_Ui->spinBox->value(); }

/*
Mode GameConfiguration::getMode() const
{
  if (m_Ui->twoPlayerModerRadioButton->isChecked())
  {
    return TwoPlayer;
  }
  else if (m_Ui->aiModeRadioButton->isChecked())
  {
    return Ai;
  }
}
*/

GameConfiguration *GameConfiguration::getInstance()
{
  static GameConfiguration instance;
  return &instance;
}

void GameConfiguration::resetConfiguration()
{
  m_Ui->twoPlayerModerRadioButton->setChecked(true);
  m_Ui->player2LineEdit->setEnabled(true);
  m_Ui->player2LineEdit->setText("");
}

void GameConfiguration::setGame(QAbstractButton *button)
{
  if (button == m_Ui->buttonBox->button(QDialogButtonBox::Ok))
  {
    if (m_Ui->twoPlayerModerRadioButton->isChecked())
    {
      qDebug() << "2 player mode";
    }
    else if (m_Ui->aiModeRadioButton->isChecked())
    {
      qDebug() << "AI player mode";
    }
  }
}

void GameConfiguration::setAIMode()
{
  m_Ui->player2LineEdit->setText(SpecialData::aiName);
  m_Ui->player2LineEdit->setDisabled(true);
}

void GameConfiguration::setEasyAIMode()
{
  m_Ui->player2LineEdit->setText(SpecialData::aiEasyName);
  m_Ui->player2LineEdit->setDisabled(true);
}

void GameConfiguration::setTwoPlayerMode()
{
  if (m_Ui->player2LineEdit->text() ==
      (SpecialData::aiName || SpecialData::aiEasyName))
  {
    m_Ui->player2LineEdit->setText(""); // TODO :replace with clear()
    m_Ui->player2LineEdit->setEnabled(true);
  }
}
