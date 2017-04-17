#include "fileHandlerFunctions.h"

using namespace std;
using namespace cv;

bool calibrateCameraQuery()
{
    char calibrate;
    cout << "Calibrate camera [y/n]: ";
    cin >> calibrate;
    return (calibrate == 'y' || calibrate == 'Y');
}

void createCameraMatrixFile()
{
    ofstream cameraMatrixFile;
    cameraMatrixFile.open("cameraMatrixFile");
    cameraMatrixFile << 1020 << " " << 0 << " " << 640 << endl << 0 << " " << 1020 << " " << 360 << endl << 0 << " " << 0 << " " << 1;
    cameraMatrixFile.close();
}

void writeCameraMatrixToAFile(Mat_<double> cameraMatrix)
{
    ofstream cameraMatrixFile;
    cameraMatrixFile.open("cameraMatrixFile");

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (2 == j && 2 != i)
            {
                cameraMatrixFile << cameraMatrix.at<double>(i, j) << " \n";
            }
            else
            {
                cameraMatrixFile << cameraMatrix.at<double>(i, j) << " ";
            }
        }
    }
    cameraMatrixFile.close();
}

void readAndSetCameraClaibrationValues(double &focalLenght_x, double &focalLength_y)
{
    int doubleCounter = 0;
    double temporaryValue = 0;
    ifstream cameraMatrixFile;
    cameraMatrixFile.open("cameraMatrixFile");
    while (cameraMatrixFile >> temporaryValue)
    {
        doubleCounter++;
        if (1 == doubleCounter)
            focalLenght_x = temporaryValue;

        if (5 == doubleCounter)
            focalLength_y = temporaryValue;
    }
    cameraMatrixFile.close();
}

void returnMeshPointsFromAFile(Point3d *meshPoints)
{
    ifstream input("pose_mean_shape.txt");
    double x, y, z = 0;
    int lineCounter = 0;
    while (input >> x >> y >> z)
    {
        Point3d point(x, y, -z);
        meshPoints[lineCounter] = point;
        lineCounter++;
    }
}
