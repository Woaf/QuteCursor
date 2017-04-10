#include "qutecursor.h"
#include "ui_qutecursor.h"

QuteCursor::QuteCursor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuteCursor)
{
    ui->setupUi(this);
}

QuteCursor::~QuteCursor()
{
    delete ui;
}
