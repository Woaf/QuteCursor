#ifndef MESSAGES_H_
#define MESSAGES_H_

#include <iostream>
#include <QMessageBox>

// GUI
void showCameraNotFoundMessage(QWidget* window);
bool confirmCalibration(QWidget* window);
void creatingNewMatrixFileMessage(QWidget* window);
void showCalibrationSuccessMessage(QWidget* window);
void showCalibrationFailureMessage(QWidget* window);

// console
void showWelcomeMessage();
void showUserManual();
void showAppreciationMessage();
void showCopyrightMessage();

#endif
