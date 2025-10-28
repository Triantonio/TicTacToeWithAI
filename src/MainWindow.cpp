#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_Ui(new Ui::MainWindow),
      m_GameConfiguration(GameConfiguration::getInstance())
{
  m_Ui->setupUi(this);
  // Styling for the labels of the player names
  m_Ui->player1Label->setFont(QFont("Lucida Bright", 14, QFont::Normal));
  m_Ui->player1Label->setStyleSheet("QLabel{color: blue;}");
  m_Ui->player2Label->setFont(QFont("Lucida Bright", 14, QFont::Normal));
  m_Ui->player2Label->setStyleSheet("QLabel{color: red;}");

  // Enabling of the actions
  connect(m_Ui->actionNewGame, &QAction::triggered, this,
          &MainWindow::startNewGame);
  connect(m_Ui->tictactoe, &TicTacToeWidget::changePlayer, this,
          &MainWindow::boldCurrentPlayerName);
  connect(m_Ui->tictactoe, &TicTacToeWidget::finishGame, this,
          &MainWindow::determineGameOutcomeMessage);
  connect(m_Ui->actionQuitGame, &QAction::triggered, this,
          &MainWindow::quitGame);
  connect(this, &MainWindow::startAiMode, m_Ui->tictactoe,
          &TicTacToeWidget::setAiMode);
  connect(this, &MainWindow::startEasyAiMode, m_Ui->tictactoe,
          &TicTacToeWidget::setEasyAiMode);

  setMainTitleMedia();

  boldCurrentPlayerName();
}

MainWindow::~MainWindow() { delete m_Ui; }

void MainWindow::setMainTitleMedia()
{
  QString path =
      QCoreApplication::applicationDirPath() + "/../../resources/video/TitleIntro.wmv";
  if (!QFile::exists(path))
  {
    return;
  }

  m_MediaPlayer = new QMediaPlayer(this);
  m_MediaPlayer->setVideoOutput(m_Ui->videoWidget);
  m_MediaPlayer->setVolume(50);

  m_MediaPlayer->setMedia(QUrl::fromLocalFile(path));
  m_MediaPlayer->play();
}

void MainWindow::startNewGame()
{ // Reset the player names.
  m_Ui->player1Label->setText("");
  m_Ui->player2Label->setText("");
  // Reset the game size
  m_GameConfiguration->setGameSide(SideRange::minRange);
  // Clear configuration fields
  m_GameConfiguration->setPlayer1Name("");
  m_GameConfiguration->setPlayer2Name("");
  // reset configuration
  m_GameConfiguration->resetConfiguration();
  // Reset the mode to 2 player mode
  m_Ui->tictactoe->setTwoPlayerMode();

  // If the user press "cancel", the new game is aborted.
  if (m_GameConfiguration->exec() == QDialog::Rejected)
  {
    // abortion
    return;
  }
  // check for Ai mode
  if (m_GameConfiguration->getPlayer2Name() == SpecialData::aiName)
  {
    m_Ui->tictactoe->resetContainers();
    emit startAiMode();
  }
  else if (m_GameConfiguration->getPlayer2Name() == SpecialData::aiEasyName)
  {
    m_Ui->tictactoe->resetContainers();
    emit startEasyAiMode();
  }

  // configuration of player names
  m_Ui->player1Label->setText(m_GameConfiguration->getPlayer1Name());
  m_Ui->player2Label->setText(m_GameConfiguration->getPlayer2Name());
  int gameSide = m_GameConfiguration->getGameSide();
  // TODO when AI implemented
  // Mode mode = m_GameConfiguration->getMode();
  // Adjustment of the tictactoe board
  m_Ui->tictactoe->setFixedHeight(Data::widthFactor *
                                  (gameSide + Data::boardSpacing));
  m_Ui->tictactoe->setFixedWidth(Data::widthFactor *
                                 (gameSide + Data::boardSpacing));
  // Hide the game title
  m_Ui->videoWidget->setVisible(false);
  // Update the side of the game
  m_Ui->tictactoe->setGameSide(gameSide);
  // Launch the game
  m_Ui->tictactoe->startOrRestartGame();
  // Enable the tictactoe board
  m_Ui->tictactoe->setEnabled(true);
}

void MainWindow::boldCurrentPlayerName()
{
  QFont player1Font = m_Ui->player1Label->font();
  player1Font.setBold(m_Ui->tictactoe->getCurrentPlayer() == Player::Player1);
  m_Ui->player1Label->setFont(player1Font);

  QFont player2Font = m_Ui->player2Label->font();
  player2Font.setBold(m_Ui->tictactoe->getCurrentPlayer() == Player::Player2);
  m_Ui->player2Label->setFont(player2Font);
}

void MainWindow::determineGameOutcomeMessage()
{ // Acquire the game outcome
  Winner winner = m_Ui->tictactoe->getGameOutcome();
  if (winner == Winner::WinnerPlayer1)
  {
    m_Ui->tictactoe->setGameOutcomeMessage("The winner is " +
                                           m_Ui->player1Label->text());
  }
  else if (winner == Winner::WinnerPlayer2)
  {
    m_Ui->tictactoe->setGameOutcomeMessage("The winner is " +
                                           m_Ui->player2Label->text());
  }
  else if (winner == Winner::Draw)
  {
    m_Ui->tictactoe->setGameOutcomeMessage("The game is a Draw");
  }
}

void MainWindow::quitGame()
{ // TODO: Add a message box asking for quitting.
  qApp->quit();
}
