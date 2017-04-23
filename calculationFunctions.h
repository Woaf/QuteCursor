#pragma once
#ifndef CALCULATIONFUNCTIONS_H_
#define CALCULATIONFUNCTIONS_H_

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include <opencv2/videoio.hpp>

double returnMaximumOfTwoValues(double first, double second);
double returnThreeDimensionalDistance(cv::Point3d point);
double returnThreeDimensionalDistance(cv::Point3d first, cv::Point3d second);
cv::Point3d returnCentroidOfThreePoints(int dimensions, cv::Point3d first, cv::Point3d second, cv::Point3d third);
void returnMatrixOfTwoVectors(cv::Mat &mat, cv::Point3d mesh, cv::Point3d face);
cv::Point returnDrawablePoint(cv::Point3d point, double norm_coeff, int window_width, int window_height);
double returnSumOfAnglesBetweenThreePoints(cv::Point3d first, cv::Point3d second, cv::Point3d third);
void returnAnglesBetweenThreePoints(double *points, cv::Point3d first, cv::Point3d second, cv::Point3d third);

#endif
