#include "qutecursor.h"
#include "ui_qutecursor.h"
#include <iostream>
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
    runHeadCursor();
    ui->cursor->setEnabled(true);
}
