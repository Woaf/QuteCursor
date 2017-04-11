#ifndef QUTECURSOR_H
#define QUTECURSOR_H

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

private:
    Ui::QuteCursor *ui;
};

#endif // QUTECURSOR_H
