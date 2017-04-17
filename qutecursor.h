#ifndef QUTECURSOR_H_
#define QUTECURSOR_H_

#include <QMainWindow>

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
    void on_calibrate_clicked();

    void on_cursor_clicked();

    void on_actionQuit_triggered();

    void on_actionCalibrate_camera_triggered();

    void on_actionStart_QuteCursor_triggered();

private:
    Ui::QuteCursor *ui;
};

#endif // QUTECURSOR_H
