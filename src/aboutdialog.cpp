#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "version.h"

// Qt
#include <QShortcut>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), _ui(new Ui::AboutDialog)
{
    _ui->setupUi(this);
    _ui->st_label->setText("Stretch Timer " + QString(STRETCHTIMER_VERSION));

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(close()));
}

AboutDialog::~AboutDialog()
{
    delete _ui;
}
