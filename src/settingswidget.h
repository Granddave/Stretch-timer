#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QDialog>

namespace Ui
{
class SettingsWidget;
}

class SettingsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget* parent = nullptr);
    ~SettingsWidget();

private slots:
    void saveSettings();
    void hideCloseRadioChanged(bool b);
    void darkThemeToggled(bool b);

private:
    void loadSettings();

    Ui::SettingsWidget* m_ui;
};

#endif // SETTINGSWIDGET_H
