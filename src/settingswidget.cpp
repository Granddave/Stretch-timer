#include "settingswidget.h"
#include "ui_settingswidget.h"
#include "common.h"

#include <QShortcut>
#include <QSettings>
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget* parent) : QDialog(parent), _ui(new Ui::SettingsWidget)
{
    _ui->setupUi(this);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    loadSettings();

    connect(_ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
    connect(_ui->hide_radioButton, SIGNAL(toggled(bool)), this, SLOT(hideCloseRadioChanged(bool)));
    connect(_ui->darkTheme_checkBox, SIGNAL(toggled(bool)), this, SLOT(darkThemeToggled(bool)));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(close()));
}

SettingsWidget::~SettingsWidget()
{
    delete _ui;
}

/* Loads settings from file */
void SettingsWidget::loadSettings()
{
    QSettings settings;

    // Message
    QString message = settings.value("timeoutMessage", "Time to stretch!").toString();
    _ui->timeoutMessagelineEdit->setText(message);

    // Message time
    int time = settings.value("secondsToDisplay", 5).toInt();
    _ui->timeToShow_spinBox->setValue(time);

#ifdef AGGRESSIVE_MODE_SUPPORTED
    bool aggressiveMode = settings.value("aggressiveMode", false).toBool();
    _ui->aggressiveMode_checkBox->setChecked(aggressiveMode);
#else  // AGGRESSIVE_MODE_SUPPORTED
    _ui->aggressiveMode_checkBox->hide();
    _ui->aggressiveMode_label->hide();
#endif // AGGRESSIVE_MODE_SUPPORTED

    // Quit on close
    bool quitOnClose = settings.value("quitOnClose", false).toBool();
    if (quitOnClose)
    {
        _ui->quit_radioButton->setChecked(true);
        _ui->disablePopup_checkBox->setEnabled(false);
        _ui->disablePopup_label->setEnabled(false);
    }
    else
    {
        _ui->hide_radioButton->setChecked(true);
    }

    bool showPopupWhenHide = !settings.value("showPopupWhenHide", true).toBool();
    settings.setValue("showPopupWhenHide", showPopupWhenHide);
    _ui->disablePopup_checkBox->setChecked(showPopupWhenHide);

    bool darkTheme = settings.value("darkTheme", true).toBool();
    _ui->darkTheme_checkBox->setChecked(darkTheme);
}

/* Saves settings to file */
void SettingsWidget::saveSettings()
{
    QSettings settings;

    QString message = _ui->timeoutMessagelineEdit->text();
    settings.setValue("timeoutMessage", message);

    int time = _ui->timeToShow_spinBox->value();
    settings.setValue("secondsToDisplay", time);

    bool quitOnClose = _ui->quit_radioButton->isChecked();
    settings.setValue("quitOnClose", quitOnClose);

    bool aggressiveMode = _ui->aggressiveMode_checkBox->isChecked();
    settings.setValue("aggressiveMode", aggressiveMode);

    bool showPopupWhenHide = !_ui->disablePopup_checkBox->isChecked();
    settings.setValue("showPopupWhenHide", showPopupWhenHide);

    bool darkTheme = _ui->darkTheme_checkBox->isChecked();
    settings.setValue("darkTheme", darkTheme);

    qDebug() << "SETTINGS: Saved";
}

void SettingsWidget::hideCloseRadioChanged(bool b)
{
    _ui->disablePopup_checkBox->setEnabled(b);
    _ui->disablePopup_label->setEnabled(b);
}

void SettingsWidget::darkThemeToggled(bool b)
{
    Q_UNUSED(b);
    _ui->darkTheme_checkBox->setText("Restart for change to take effect");
}
