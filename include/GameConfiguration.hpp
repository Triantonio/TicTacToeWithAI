#ifndef GAMECONFIGURATION_HPP
#define GAMECONFIGURATION_HPP

/// @file GameConfiguration.hpp
/// @brief Declares the GameConfiguration dialog for configuring new matches.

#include "qabstractbutton.h"
#include <QDialog>

namespace Ui
{
class GameConfiguration;
}

/// @struct SideRange
/// @brief Provides compile-time boundaries for the board side length.
struct SideRange
{
  static constexpr int minRange = 3;  ///< Minimum number of rows/columns.
  static constexpr int maxRange = 10; ///< Maximum number of rows/columns.
};

/// @struct SpecialData
/// @brief Stores user-facing strings used by the AI configurations.
struct SpecialData
{
  static constexpr const char *aiName = "Mister AI"; ///< Default AI name.
  static constexpr const char *aiEasyName =
      "Mister Easy AI"; ///< Easy AI alias.
};

/// @class GameConfiguration
/// @brief Singleton dialog used to configure a new Tic-Tac-Toe game session.
///
/// The dialog exposes setters and getters for player names, board dimensions
/// and AI related options. It ensures that only one instance of the
/// configuration dialog exists at runtime.
class GameConfiguration : public QDialog
{
  Q_OBJECT

private:
  /// @brief Constructs a configuration dialog.
  /// @param parent Parent widget used for Qt ownership.
  explicit GameConfiguration(QWidget *parent = nullptr);

public:
  /// @brief Destroys the dialog and releases owned resources.
  ~GameConfiguration() override;

  /// @brief Sets the name of player 1.
  /// @param name Display name assigned to player 1.
  void setPlayer1Name(const QString &name) const;
  /// @brief Sets the name of player 2.
  /// @param name Display name assigned to player 2.
  void setPlayer2Name(const QString &name) const;

  /// @brief Retrieves the configured name for player 1.
  /// @return The player 1 display name.
  QString getPlayer1Name() const;
  /// @brief Retrieves the configured name for player 2.
  /// @return The player 2 display name.
  QString getPlayer2Name() const;

  /// @brief Sets the selected board side size.
  /// @param side Board dimension in cells.
  void setGameSide(int side) const;
  /// @brief Retrieves the currently selected board side size.
  /// @return Board dimension in cells.
  int getGameSide() const;

  /// @brief Retrieves the single instance of the configuration dialog.
  /// @return Pointer to the global GameConfiguration instance.
  static GameConfiguration *getInstance();

  /// @brief Resets the AI configuration to its default settings.
  void resetConfiguration();

private slots:
  /// @brief Updates the enabled state of the OK button.
  void updateOkButton();

  /// @brief Starts or cancels the game depending on the clicked button.
  /// @param button Button reference used to identify the requested action.
  void setGame(QAbstractButton *button);

  /// @brief Enables the easy AI mode option.
  void setEasyAIMode();

  /// @brief Enables the regular AI mode option.
  void setAIMode();

  /// @brief Enables the two-player mode option.
  void setTwoPlayerMode();

private:
  Ui::GameConfiguration *m_Ui; ///< Generated UI form pointer.
};

#endif // GAMECONFIGURATION_HPP
