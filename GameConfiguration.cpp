#include "GameConfiguration.hpp"
#include "ui_GameConfiguration.h"
#include <QPushButton>

GameConfiguration::GameConfiguration(QWidget *parent)
    : QDialog(parent), m_Ui(new Ui::GameConfiguration)
{
  m_Ui->setupUi(this);

  // ensure that the okbutton is disabled at the start
  updateOkButton();

  connect(m_Ui->player1LineEdit, &QLineEdit::textEdited, this,
          &GameConfiguration::updateOkButton);
  connect(m_Ui->player2LineEdit, &QLineEdit::textEdited, this,
          &GameConfiguration::updateOkButton);
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
