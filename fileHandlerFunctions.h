#pragma once
#ifndef FILEHANDLERFUNCTIONS_H_
#define FILEHANDLERFUNCTIONS_H_

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

bool calibrateCameraQuery();
void createCameraMatrixFile();
void writeCameraMatrixToAFile(cv::Mat_<double> cameraMatrix);
void readAndSetCameraClaibrationValues(double &focalLenght_x, double &focalLength_y);
void returnMeshPointsFromAFile(cv::Point3d *meshPoints);

#endif
