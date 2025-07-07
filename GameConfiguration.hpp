#ifndef GAMECONFIGURATION_HPP
#define GAMECONFIGURATION_HPP

#include <QDialog>

namespace Ui
{
class GameConfiguration;
}

class GameConfiguration : public QDialog
{
  Q_OBJECT

public:
  explicit GameConfiguration(QWidget *parent = nullptr);
  ~GameConfiguration();

private slots:
  /// \brief A function to update de Ok button of the configuration window.
  void updateOkButton();

private:
  Ui::GameConfiguration *m_Ui;
};

#endif // GAMECONFIGURATION_HPP
