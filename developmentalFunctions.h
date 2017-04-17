#pragma once
#ifndef DEVELOPMENTALFUNCTIONS_H_
#define DEVELOPMENTALFUNCTIONS_H_

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

// TESTED

void setCursorPosition(int x, int y);
void setCursorPosition2(int x_start, int y_start, int x_end, int y_end, int time, int steps);
void leftMouseButtonDownEvent();
void leftMouseButtonReleaseEvent();

// UNTESTED
cv::Point3d returnUnitRemovedPoints(cv::Point3d point, cv::Point3d centroid, double focalLength_x, double focalLength_y);
cv::Point3d returnCentoridOfNPoints(std::vector<cv::Point3d> points);
cv::Point3d returnDifferenceOfTwoPoints(cv::Point3d first, cv::Point3d second);

#endif
