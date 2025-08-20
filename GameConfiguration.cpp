#include "GameConfiguration.hpp"
#include "ui_GameConfiguration.h"
#include <QPushButton>

GameConfiguration::GameConfiguration(QWidget *parent)
    : QDialog(parent), m_Ui(new Ui::GameConfiguration)
{
  m_Ui->setupUi(this);

  // ensure that the okbutton is disabled at the start
  updateOkButton();

  m_Ui->spinBox->setRange(SideRange::minRange, SideRange::maxRange);
  m_Ui->horizontalSlider->setRange(SideRange::minRange, SideRange::maxRange);

  connect(m_Ui->player1LineEdit, &QLineEdit::textEdited, this,
          &GameConfiguration::updateOkButton);
  connect(m_Ui->player2LineEdit, &QLineEdit::textEdited, this,
          &GameConfiguration::updateOkButton);

  connect(m_Ui->horizontalSlider, &QSlider::valueChanged, m_Ui->spinBox,
          &QSpinBox::setValue);
  connect(m_Ui->spinBox,
          static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          m_Ui->horizontalSlider, &QSlider::setValue);
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

// Initialization of the pointer to the single instance
GameConfiguration *GameConfiguration::gameConfiguration = nullptr;

GameConfiguration *GameConfiguration::getInstance()
{
  if (gameConfiguration == nullptr)
  {
    gameConfiguration = new GameConfiguration;
  }
  return gameConfiguration;
}
