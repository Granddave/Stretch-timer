#include "settingswidget.h"
#include "ui_settingswidget.h"
#include "common.h"

#include <QShortcut>
#include <QSettings>
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget* parent) : QDialog(parent), m_ui(new Ui::SettingsWidget)
{
    m_ui->setupUi(this);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    loadSettings();

    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));
    connect(m_ui->hide_radioButton, SIGNAL(toggled(bool)), this, SLOT(hideCloseRadioChanged(bool)));
    connect(m_ui->darkTheme_checkBox, SIGNAL(toggled(bool)), this, SLOT(darkThemeToggled(bool)));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(close()));
}

SettingsWidget::~SettingsWidget()
{
    delete m_ui;
}

/* Loads settings from file */
void SettingsWidget::loadSettings()
{
    QSettings settings;

    // Message
    const QString message = settings.value("timeoutMessage", "Time to stretch!").toString();
    m_ui->timeoutMessagelineEdit->setText(message);

    // Message time
    const int time = settings.value("secondsToDisplay", 5).toInt();
    m_ui->timeToShow_spinBox->setValue(time);

#ifdef AGGRESSIVE_MODE_SUPPORTED
    const bool aggressiveMode = settings.value("aggressiveMode", false).toBool();
    m_ui->aggressiveMode_checkBox->setChecked(aggressiveMode);
#else  // AGGRESSIVE_MODE_SUPPORTED
    m_ui->aggressiveMode_checkBox->hide();
    m_ui->aggressiveMode_label->hide();
#endif // AGGRESSIVE_MODE_SUPPORTED

    // Quit on close
    const bool quitOnClose = settings.value("quitOnClose", false).toBool();
    if (quitOnClose)
    {
        m_ui->quit_radioButton->setChecked(true);
        m_ui->disablePopup_checkBox->setEnabled(false);
        m_ui->disablePopup_label->setEnabled(false);
    }
    else
    {
        m_ui->hide_radioButton->setChecked(true);
    }

    const bool showPopupWhenHide = !settings.value("showPopupWhenHide", true).toBool();
    settings.setValue("showPopupWhenHide", showPopupWhenHide);
    m_ui->disablePopup_checkBox->setChecked(showPopupWhenHide);

    const bool darkTheme = settings.value("darkTheme", true).toBool();
    m_ui->darkTheme_checkBox->setChecked(darkTheme);
}

/* Saves settings to file */
void SettingsWidget::saveSettings()
{
    QSettings settings;

    const QString message = m_ui->timeoutMessagelineEdit->text();
    settings.setValue("timeoutMessage", message);

    const int time = m_ui->timeToShow_spinBox->value();
    settings.setValue("secondsToDisplay", time);

    const bool quitOnClose = m_ui->quit_radioButton->isChecked();
    settings.setValue("quitOnClose", quitOnClose);

    const bool aggressiveMode = m_ui->aggressiveMode_checkBox->isChecked();
    settings.setValue("aggressiveMode", aggressiveMode);

    const bool showPopupWhenHide = !m_ui->disablePopup_checkBox->isChecked();
    settings.setValue("showPopupWhenHide", showPopupWhenHide);

    const bool darkTheme = m_ui->darkTheme_checkBox->isChecked();
    settings.setValue("darkTheme", darkTheme);

    qDebug() << "SETTINGS: Saved";
}

void SettingsWidget::hideCloseRadioChanged(const bool b)
{
    m_ui->disablePopup_checkBox->setEnabled(b);
    m_ui->disablePopup_label->setEnabled(b);
}

void SettingsWidget::darkThemeToggled(const bool b)
{
    Q_UNUSED(b);
    m_ui->darkTheme_checkBox->setText("Restart for change to take effect");
}
