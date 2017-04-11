#include "ownFunctions.h"

using namespace cv;

HWND hWindow;

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

double returnMaximumOfTwoValues(double first, double second)
{
    return first > second ? first : second;
}

Point3d returnUnitRemovedPoints(Point3d point, Point3d centroid, double focalLength_x, double focalLength_y)
{
    return Point3d((point.x - centroid.x) / focalLength_x, (point.y - centroid.y) / focalLength_y, 1);
}

Point3d returnDifferenceOfTwoPoints(Point3d first, Point3d second)
{
    return Point3d(second.x - first.x, second.y - first.y, second.z - first.z);
}

double returnThreeDimensionalDistance(Point3d point)
{
    double ret = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));
    return ret;
}

double returnThreeDimensionalDistance(Point3d first, Point3d second)
{
    double ret = sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2) + pow(second.z - first.z, 2));
    return ret;
}

// int::dimensions should be 1,2 or 3!
Point3d returnCentroidOfThreePoints(int dimensions, Point3d first, Point3d second, Point3d third)
{
    switch (dimensions)
    {
    case(1):
        return Point3d(first.x + second.x + third.x, 0, 0) / 3.0;
        break;
    case(2):
        return Point3d(first.x + second.x + third.x, first.y + second.y + third.y, 0) / 3.0;
        break;
    case(3):
    default:
        return (Point3d(first.x + second.x + third.x, first.y + second.y + third.y, first.z + second.z + third.z) / 3.0);
    }
}

// kesobbi hasznalatra (talan)
Point3d returnCentoridOfNPoints(std::vector<Point3d> points)
{
    double x_coordinates = 0;
    double y_coordinates = 0;
    double z_coordinates = 0;
    int number_of_points = 0;
    std::vector<Point3d>::size_type vectorIterator;
    for (vectorIterator = 0; vectorIterator != points.size(); ++vectorIterator)
    {
        x_coordinates += points[vectorIterator].x;
        y_coordinates += points[vectorIterator].y;
        z_coordinates += points[vectorIterator].z;
        number_of_points++;
    }
    if (number_of_points == 0)
    {
        throw std::invalid_argument("The array of points is empty!");
    }
    return (Point3d(x_coordinates, y_coordinates, z_coordinates) / number_of_points);
}

void returnMatrixOfTwoVectors(Mat &mat, Point3d mesh, Point3d face)
{
    Mat_<double> ret = Mat_<double>::ones(3, 3);
    ret(0, 0) = mesh.x * face.x;
    ret(0, 1) = mesh.x * face.y;
    ret(0, 2) = mesh.x * face.z;
    ret(1, 0) = mesh.y * face.x;
    ret(1, 1) = mesh.y * face.y;
    ret(1, 2) = mesh.y * face.z;
    ret(2, 0) = mesh.z * face.x;
    ret(2, 1) = mesh.z * face.y;
    ret(2, 2) = mesh.z * face.z;

    mat = ret;
}

double returnSumOfAnglesBetweenThreePoints(Point3d first, Point3d second, Point3d third)
{
    double a = sqrt(pow((second.x - first.x), 2) + pow((second.y - first.y), 2) + pow((second.z - first.z),2));
    double b = sqrt(pow((third.x - second.x), 2) + pow((third.y - second.y), 2) + pow((third.z - second.z), 2));
    double c = sqrt(pow((third.x - first.x), 2) + pow((third.y - first.y), 2) + pow((third.z - first.z), 2));

    double alpha = acos((b*b + c*c - a*a) / (2 * b*c)) * 180 / CV_PI;
    double beta  = acos((a*a + c*c - b*b) / (2 * a*c)) * 180 / CV_PI;
    double gamma = acos((a*a + b*b - c*c) / (2 * a*b)) * 180 / CV_PI;

    return alpha + beta + gamma;
}

// first: right eye; second: left eye; third: nose tip
void returnAnglesBetweenThreePoints(double *points, Point3d first, Point3d second, Point3d third)
{

    double a = sqrt(pow((second.x - first.x), 2) + pow((second.y - first.y), 2) + pow((second.z - first.z), 2));
    double b = sqrt(pow((third.x - second.x), 2) + pow((third.y - second.y), 2) + pow((third.z - second.z), 2));
    double c = sqrt(pow((third.x - first.x), 2) + pow((third.y - first.y), 2) + pow((third.z - first.z), 2));

    points[0] = acos((b*b + c*c - a*a) / (2 * b*c));
    points[1] = acos((a*a + c*c - b*b) / (2 * a*c));
    points[2] = acos((a*a + b*b - c*c) / (2 * a*b));
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

Point returnDrawablePoint(Point3d point, double norm_coeff, int window_width, int window_height)
{
    return Point(point.x * norm_coeff + window_width, point.y * norm_coeff + window_height);
}

void setCursorPosition(int x, int y)
{
    RECT mainWindow;
    GetWindowRect(hWindow, &mainWindow);

    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;

    POINT currentCursorPos;
    GetCursorPos(&currentCursorPos);

    Input.mi.dx = (LONG)(currentCursorPos.x*0.9 + x*0.1);
    Input.mi.dy = (LONG)(currentCursorPos.y*0.9 + y*0.1);
    cout << Input.mi.dx << endl << Input.mi.dy << endl << endl;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &Input, sizeof(INPUT));
}

void setCursorPosition2(int x_start, int y_start, int x_end, int y_end, int time, int steps)
{
    double dx = (x_end - x_start) / ((double)steps);
    double dy = (y_end - y_start) / ((double)steps);

    double t = time / ((double) steps);

    for (int i = 0; i < steps; i++)
    {
        Sleep(t);
        setCursorPosition(x_start + dx*i, y_start + dy*i);
    }
}

void leftMouseButtonDownEvent()
{
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));
    /*
    ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));
    */

}

// for later use
void leftMouseButtonReleaseEvent()
{
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));
}