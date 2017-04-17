#include "developmentalFunctions.h"

using namespace std;
using namespace cv;

HWND hWindow;

Point3d returnUnitRemovedPoints(Point3d point, Point3d centroid, double focalLength_x, double focalLength_y)
{
    return Point3d((point.x - centroid.x) / focalLength_x, (point.y - centroid.y) / focalLength_y, 1);
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
