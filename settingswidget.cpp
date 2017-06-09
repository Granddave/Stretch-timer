#include "settingswidget.h"
#include "ui_settingswidget.h"

#include <QShortcut>
#include <QSettings>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::SettingsWidget)
{
    _ui->setupUi(this);

    loadSettings();

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(close()));
}



SettingsWidget::~SettingsWidget()
{
    delete _ui;
}

void SettingsWidget::loadSettings()
{
    QSettings settings;

    _ui->closeAction_CheckBox->setChecked(settings.value("quitOnClose").toBool());
    if(_ui->closeAction_CheckBox->isChecked())
    {

    }
    else
    {

    }
}
