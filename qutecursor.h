#ifndef QUTECURSOR_H_
#define QUTECURSOR_H_

#include <QMainWindow>
#include <QMessageBox>
#include "qutecursor.h"
#include "ui_qutecursor.h"
#include "headPoseCursor.h"
#include "messages.h"

namespace Ui {
class QuteCursor;
}

class QuteCursor : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuteCursor(QWidget *parent = 0);
    ~QuteCursor();

private slots:
    void calibrateAction();

    void quteCursorAction();

    void viewChangeAction();

    void quitAction();

    void on_calibrate_clicked();

    void on_cursor_clicked();

    void on_actionQuit_triggered();

    void on_actionCalibrate_camera_triggered();

    void on_actionStart_QuteCursor_triggered();

    void on_actionCompact_View_triggered();

    void on_pushButton_clicked();

private:
    Ui::QuteCursor *ui;
    bool compactView = false;
};

#endif // QUTECURSOR_H
