#pragma once
#ifndef HEADPOSECURSOR_H_
#define HEADPOSEFURSOR_H_

#include "messages.h"
#include "directoryAccessFunctions.h"
#include "cameraCalibration.h"
#include "fileHandlerFunctions.h"
#include "calculationFunctions.h"
#include "developmentalFunctions.h"
#include "errorHandling.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include <opencv2/videoio.hpp>

#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

#include <QWidget>

void runCameraCalib(QWidget* parentWindow);
int runHeadCursor(QWidget* parentWindow);

#endif
