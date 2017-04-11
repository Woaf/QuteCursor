#include "welcomeMessage.h"

using namespace std;

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
