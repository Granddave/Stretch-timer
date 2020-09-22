#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "version.h"

// Qt
#include <QShortcut>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);
    m_ui->st_label->setText("Stretch Timer " + QString(STRETCHTIMER_VERSION));

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(close()));
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}
