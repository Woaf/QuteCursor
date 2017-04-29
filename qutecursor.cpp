#include "qutecursor.h"
#include <QDebug>

QuteCursor::QuteCursor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuteCursor)
{
    ui->setupUi(this);
    showWelcomeMessage();
    showCopyrightMessage();
    showUserManual();
}

QuteCursor::~QuteCursor()
{
    delete ui;
}

void QuteCursor::calibrateAction()
{

    if (confirmCalibration(this->window()))
    {
        ui->calibrate->setText("Calibrating...");
        ui->calibrate->setDisabled(true);
        ui->menuMenu->setDisabled(true);
        runCameraCalib(this->window());
        ui->calibrate->setText("Calibrate camera");
        ui->calibrate->setEnabled(true);
        ui->menuMenu->setEnabled(true);
    }
}

void QuteCursor::quteCursorAction()
{
    ui->cursor->setDisabled(true);
    this->hide();
    runHeadCursor(this->window());
    this->show();
    ui->cursor->setEnabled(true);
}

void QuteCursor::viewChangeAction()
{
    if(!compactView)
    {
        this->setFixedSize(645, 460);
        ui->calibrate->setDisabled(true);
        ui->cursor->setDisabled(true);
        compactView = true;
    }
    else
    {
        this->setFixedSize(830, 460);
        if(ui->menuMenu->isEnabled())
        {
            ui->calibrate->setEnabled(true);
        }
        else
        {
            ui->calibrate->setDisabled(true);
        }
        ui->cursor->setEnabled(true);
        compactView = false;
    }
}

void QuteCursor::quitAction()
{
    QMessageBox::StandardButton quit;
    quit = QMessageBox::question(this, "Quit Qute Cursor", "Are you sure you want to Quit this application?", QMessageBox::Yes|QMessageBox::No);
    if (quit == QMessageBox::Yes)
    {
        exit(0);
    }
}

void QuteCursor::on_calibrate_clicked()
{
    calibrateAction();
}

void QuteCursor::on_cursor_clicked()
{
    quteCursorAction();
}

void QuteCursor::on_actionCalibrate_camera_triggered()
{
    calibrateAction();
}

void QuteCursor::on_actionStart_QuteCursor_triggered()
{
    quteCursorAction();
}

void QuteCursor::on_actionQuit_triggered()
{
    quitAction();
}

void QuteCursor::on_actionCompact_View_triggered()
{
    viewChangeAction();
}

void QuteCursor::on_pushButton_clicked()
{
    viewChangeAction();
}
