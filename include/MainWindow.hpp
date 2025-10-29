#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

/// @file MainWindow.hpp
/// @brief Declares the main window that orchestrates gameplay and UI widgets.

#include "GameConfiguration.hpp"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>

/// @struct Data
/// @brief Constants that drive layout and sizing of UI components.
struct Data
{
  static constexpr int widthFactor = 50; ///< Width scaling factor.
  static constexpr int boardSpacing = 1; ///< Space between board tiles.
};

namespace Ui
{
class MainWindow;
}

/// @class MainWindow
/// @brief Application entry point window responsible for managing gameplay.
///
/// The window owns the configuration dialog, routes player actions and controls
/// introductory multimedia assets.
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /// @brief Creates the main application window.
  /// @param parent Optional parent widget for Qt ownership.
  explicit MainWindow(QWidget *parent = nullptr);
  /// @brief Cleans up owned widgets and multimedia resources.
  ~MainWindow() override;

signals:
  /// @brief Emitted when the regular AI mode should be started.
  void startAiMode();
  /// @brief Emitted when the easy AI mode should be started.
  void startEasyAiMode();

private slots:
  /// @brief Handles the start of a new game session.
  void startNewGame();

  /// @brief Highlights the label that represents the current player.
  void boldCurrentPlayerName();

  /// @brief Computes and displays the message describing the game outcome.
  void determineGameOutcomeMessage();

  /// @brief Closes the application.
  void quitGame();

private:
  /// @brief Configures the multimedia player that renders the title video.
  void setMainTitleMedia();

  Ui::MainWindow *m_Ui; ///< Pointer to the auto-generated UI elements.

  GameConfiguration *m_GameConfiguration; ///< Shared configuration dialog.

  /// @brief Media player used to play the introductory video.
  QMediaPlayer *m_MediaPlayer;
};

#endif // MAINWINDOW_HPP
