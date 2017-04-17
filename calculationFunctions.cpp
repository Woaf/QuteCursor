#include "calculaitonFunctions.h"

using namespace std;
using namespace cv;

double returnMaximumOfTwoValues(double first, double second)
{
    return first > second ? first : second;
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

Point returnDrawablePoint(Point3d point, double norm_coeff, int window_width, int window_height)
{
    return Point(point.x * norm_coeff + window_width, point.y * norm_coeff + window_height);
}
