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


void QuteCursor::on_calibrate_clicked()
{
    ui->calibrate->setDisabled(true);
    runCameraCalib();
    ui->calibrate->setEnabled(true);
}

void QuteCursor::on_cursor_clicked()
{
    ui->cursor->setDisabled(true);
    this->hide();
    runHeadCursor();
    this->show();
    ui->cursor->setEnabled(true);
}

void QuteCursor::on_actionCalibrate_camera_triggered()
{
    ui->calibrate->setDisabled(true);
    runCameraCalib();
    ui->calibrate->setEnabled(true);
}

void QuteCursor::on_actionStart_QuteCursor_triggered()
{
    ui->cursor->setDisabled(true);
    this->hide();
    runHeadCursor();
    this->show();
    ui->cursor->setEnabled(true);
}

void QuteCursor::on_actionQuit_triggered()
{
    QMessageBox::StandardButton quit;
    quit = QMessageBox::question(new QWidget, "Quit Qute Cursor", "Are you sure you want Quit this application?", QMessageBox::Yes|QMessageBox::No);
    if (quit == QMessageBox::Yes)
    {
        exit(0);
    }
}
