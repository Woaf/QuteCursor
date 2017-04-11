#pragma once
#ifndef OWNFUNCTIONS_H_
#define OWNFUNCTIONS_H_

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include <opencv2/videoio.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <Windows.h>

using namespace std;

// TESTED
bool calibrateCameraQuery();
void writeCameraMatrixToAFile(cv::Mat_<double> cameraMatrix);
void createCameraMatrixFile();
void readAndSetCameraClaibrationValues(double &focalLenght_x, double &focalLength_y);
double returnMaximumOfTwoValues(double first, double second);
double returnThreeDimensionalDistance(cv::Point3d point);
double returnThreeDimensionalDistance(cv::Point3d first, cv::Point3d second);
cv::Point3d returnCentroidOfThreePoints(int dimensions, cv::Point3d first, cv::Point3d second, cv::Point3d third);
void returnMatrixOfTwoVectors(cv::Mat &mat, cv::Point3d mesh, cv::Point3d face);
cv::Point returnDrawablePoint(cv::Point3d point, double norm_coeff, int window_width, int window_height);
double returnSumOfAnglesBetweenThreePoints(cv::Point3d first, cv::Point3d second, cv::Point3d third);
void returnAnglesBetweenThreePoints(double *points, cv::Point3d first, cv::Point3d second, cv::Point3d third);
void returnMeshPointsFromAFile(cv::Point3d *meshPoints);
void setCursorPosition(int x, int y);
void setCursorPosition2(int x_start, int y_start, int x_end, int y_end, int time, int steps);
void leftMouseButtonDownEvent();
void leftMouseButtonReleaseEvent();

// UNTESTED
cv::Point3d returnUnitRemovedPoints(cv::Point3d point, cv::Point3d centroid, double focalLength_x, double focalLength_y);
cv::Point3d returnCentoridOfNPoints(std::vector<cv::Point3d> points);

cv::Point3d returnDifferenceOfTwoPoints(cv::Point3d first, cv::Point3d second);

#endif
