#include <QMessageBox>
#include "qutecursor.h"
#include "ui_qutecursor.h"
#include "headPoseCursor.h"
#include "welcomeMessage.h"

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
    QMessageBox::StandardButton calibrate;
    calibrate = QMessageBox::question(this, "Camera calibration", "Are you sure you want calibrate Your camera?", QMessageBox::Yes|QMessageBox::No);
    if (calibrate == QMessageBox::Yes)
    {
        ui->calibrate->setText("Calibrating...");
        ui->calibrate->setDisabled(true);
        runCameraCalib();
        ui->calibrate->setText("Calibrate camera");
        ui->calibrate->setEnabled(true);
    }
}

void QuteCursor::quteCursorAction()
{
    ui->cursor->setDisabled(true);
    this->hide();
    runHeadCursor();
    this->show();
    ui->cursor->setEnabled(true);
}

void QuteCursor::quitAction()
{
    QMessageBox::StandardButton quit;
    quit = QMessageBox::question(this, "Quit Qute Cursor", "Are you sure you want Quit this application?", QMessageBox::Yes|QMessageBox::No);
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
