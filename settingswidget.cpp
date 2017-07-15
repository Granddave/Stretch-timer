#include "settingswidget.h"
#include "ui_settingswidget.h"

#include <QShortcut>
#include <QSettings>
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::SettingsWidget)
{
    _ui->setupUi(this);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    loadSettings();

    connect(_ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));

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

    // Quit on close
    bool quitOnClose = settings.value("quitOnClose", false).toBool();
    if(quitOnClose)
    {
        _ui->quit_radioButton->setChecked(true);
    }
    else
    {
        _ui->hide_radioButton->setChecked(true);
    }
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

    qDebug() << "SETTINGS: Saved";
}
