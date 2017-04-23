#include "messages.h"

using namespace std;

// The following functions are to show the messages
// in the gui application

void showCameraNotFoundMessage(QWidget* window)
{
    QMessageBox::critical(window, "Camera detection failure", "Could not detect camera!\n\n"
                                                             "Please make sure that a camera is attached or enabled on Your device.");
}

void creatingNewMatrixFileMessage(QWidget* window)
{
    QMessageBox::information(window, "Camera calibration", "Could not open an existing camera matrix file.\nOpening default camera matrix file.");
}

bool confirmCalibration(QWidget* window)
{
    QMessageBox::StandardButton confirm = QMessageBox::question(window, "Camera calibration", "Are you sure you want to calibrate Your camera?", QMessageBox::Yes|QMessageBox::No);
    if(confirm == QMessageBox::Yes)
    {
        return true;
    }
    return false;
}

void showCalibrationSuccessMessage(QWidget* window)
{
    QMessageBox::information(window,"Successful calibration", "Camera successfully calibrated!");
}

void showCalibrationFailureMessage(QWidget* window)
{
    QMessageBox::critical(window, "Camera calibration", "Could not calibrate camera!\n\n"
                                                             "Make sure that 'default.xml' is not missing from the directory of this application,\n"
                                                             "and that You have given valid images in the images folder.\n"
                                                             "(You should have at lease 10 appropriate images in the images folder.)\n\n"
                                                             "*Hint: an appropriate image requires you to print out the 'pattern.png' picture on a full size A4 paper, "
                                                             "and take several images holding it in different positions while the camera can still see the full image.\n"
                                                             "It is important that You take the images with the camera on the device You wish to use this application on.");
}

// The following functions are left here in case
// the application is run in console
void showWelcomeMessage()
{
    cout << "  _   _                _    ____ " << endl;
    cout << " | | | | ___  __ _  __| |  / ___|   _ _ __ ___  ___  _ __ " << endl;
    cout << " | |_| |\/ _ \\\/ _\` |\/ _\` | | |  | | | | \'__\/ __|\/ _ \\| \'__|" << endl;
    cout << " |  _  |  __\/ (_| | (_| | | |__| |_| | |  \\__ \\ (_) | |   " << endl;
    cout << " |_| |_|\\___|\\__,_|\\__,_|  \\____\\__,_|_|  |___\/\\___\/|_|   " << endl;
    cout << endl;
}

void showUserManual()
{
    cout << "Welcome to Head Cursor." << endl;
    cout << "This application allows You to control your Windows system cursor position." << endl;
    cout << "This program requires you to have a camera connected to Your device, " << endl;
    cout << "preferably placed right in front of You." << endl;
    cout << "In order for this application to run at its best, You may choose to calibrate " << endl;
    cout << "the camera of Your device. If You choose this option, You MUST include reference " << endl;
    cout << "calibration images in the IMAGES folder provided in the directory of this application." << endl;
    cout << endl;
    cout << "After the optional calibration, look in the direction where You wish to place the cursor on " << endl;
    cout << "Your device's screen." << endl;
    cout << endl;
    cout << "To stop the application, close the window which shows the camera input." << endl << endl;
}

void showAppreciationMessage()
{
    cout << "Thank You for using Head Cursor!" << endl;
}

void showCopyrightMessage()
{
    cout << "Head Cursor (c) Balint Fazekas, 2017" << endl;
    cout << "This application uses OpenCV 3.1 and DLIB 19.2 libraries." << endl;
}
