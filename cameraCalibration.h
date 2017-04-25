// a kemara kalibraciohoz szukseges kod
// ez a kod elerheto az opencv konyvetrabol
//		C:\opencv31\sources\samples\cpp\tutorial_code\calib3d\camera_calibration
#pragma once
#ifndef CAMERACALLIBRATION_H_
#define CAMERACALLIBRATION_H_

#include <iostream>
#include <ctime>
#include <cstdio>

#include "messages.h"
#include "fileHandlerFunctions.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include <opencv2/videoio.hpp>

class Settings
{
public:
    Settings() : goodInput(false) {}
    enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
    enum InputType { INVALID, CAMERA, VIDEO_FILE, IMAGE_LIST };

    void write(cv::FileStorage &fs) const                        //Write serialization for this class
    {
        fs << "{"
           << "BoardSize_Width" << boardSize.width
           << "BoardSize_Height" << boardSize.height
           << "Square_Size" << squareSize
           << "Calibrate_Pattern" << patternToUse
           << "Calibrate_NrOfFrameToUse" << nrFrames
           << "Calibrate_FixAspectRatio" << aspectRatio
           << "Calibrate_AssumeZeroTangentialDistortion" << calibZeroTangentDist
           << "Calibrate_FixPrincipalPointAtTheCenter" << calibFixPrincipalPoint

           << "Write_DetectedFeaturePoints" << writePoints
           << "Write_extrinsicParameters" << writeExtrinsics
           << "Write_outputFileName" << outputFileName

           << "Show_UndistortedImage" << showUndistorsed

           << "Input_FlipAroundHorizontalAxis" << flipVertical
           << "Input_Delay" << delay
           << "Input" << input
           << "}";
    }
    void read(const cv::FileNode &node)                          //Read serialization for this class
    {
        node["BoardSize_Width"] >> boardSize.width;
        node["BoardSize_Height"] >> boardSize.height;
        node["Calibrate_Pattern"] >> patternToUse;
        node["Square_Size"] >> squareSize;
        node["Calibrate_NrOfFrameToUse"] >> nrFrames;
        node["Calibrate_FixAspectRatio"] >> aspectRatio;
        node["Write_DetectedFeaturePoints"] >> writePoints;
        node["Write_extrinsicParameters"] >> writeExtrinsics;
        node["Write_outputFileName"] >> outputFileName;
        node["Calibrate_AssumeZeroTangentialDistortion"] >> calibZeroTangentDist;
        node["Calibrate_FixPrincipalPointAtTheCenter"] >> calibFixPrincipalPoint;
        node["Calibrate_UseFisheyeModel"] >> useFisheye;
        node["Input_FlipAroundHorizontalAxis"] >> flipVertical;
        node["Show_UndistortedImage"] >> showUndistorsed;
        node["Input"] >> input;
        node["Input_Delay"] >> delay;
        validate();
    }
    void validate()
    {
        goodInput = true;
        if (boardSize.width <= 0 || boardSize.height <= 0)
        {
            std::cerr << "Invalid Board size: " << boardSize.width << " " << boardSize.height << std::endl;
            goodInput = false;
        }
        if (squareSize <= 10e-6)
        {
            std::cerr << "Invalid square size " << squareSize << std::endl;
            goodInput = false;
        }
        if (nrFrames <= 0)
        {
            std::cerr << "Invalid number of frames " << nrFrames << std::endl;
            goodInput = false;
        }

        if (input.empty())      // Check for valid input
            inputType = INVALID;
        else
        {
            if (input[0] >= '0' && input[0] <= '9')
            {
                std::stringstream ss(input);
                ss >> cameraID;
                inputType = CAMERA;
            }
            else
            {
                if (readStringList(input, imageList))
                {
                    inputType = IMAGE_LIST;
                    nrFrames = (nrFrames < (int)imageList.size()) ? nrFrames : (int)imageList.size();
                }
                else
                    inputType = VIDEO_FILE;
            }
            if (inputType == CAMERA)
                inputCapture.open(cameraID);
            if (inputType == VIDEO_FILE)
                inputCapture.open(input);
            if (inputType != IMAGE_LIST && !inputCapture.isOpened())
                inputType = INVALID;
        }
        if (inputType == INVALID)
        {
            std::cerr << " Input does not exist: " << input;
            goodInput = false;
        }

        flag = cv::CALIB_FIX_K4 | cv::CALIB_FIX_K5;
        if (calibFixPrincipalPoint) flag |= cv::CALIB_FIX_PRINCIPAL_POINT;
        if (calibZeroTangentDist)   flag |= cv::CALIB_ZERO_TANGENT_DIST;
        if (aspectRatio)            flag |= cv::CALIB_FIX_ASPECT_RATIO;

        if (useFisheye)
        {
            // the fisheye model has its own enum, so overwrite the flags
            flag = cv::fisheye::CALIB_FIX_SKEW | cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC |
                   // fisheye::CALIB_FIX_K1 |
                   cv::fisheye::CALIB_FIX_K2 | cv::fisheye::CALIB_FIX_K3 | cv::fisheye::CALIB_FIX_K4;
        }

        calibrationPattern = NOT_EXISTING;
        if (!patternToUse.compare("CHESSBOARD")) calibrationPattern = CHESSBOARD;
        if (!patternToUse.compare("CIRCLES_GRID")) calibrationPattern = CIRCLES_GRID;
        if (!patternToUse.compare("ASYMMETRIC_CIRCLES_GRID")) calibrationPattern = ASYMMETRIC_CIRCLES_GRID;
        if (calibrationPattern == NOT_EXISTING)
        {
            std::cerr << " Camera calibration mode does not exist: " << patternToUse << std::endl;
            goodInput = false;
        }
        atImageList = 0;

    }
    cv::Mat nextImage()
    {
        cv::Mat result;
        if (inputCapture.isOpened())
        {
            cv::Mat view0;
            inputCapture >> view0;
            view0.copyTo(result);
        }
        else if (atImageList < imageList.size())
            result = cv::imread(imageList[atImageList++], cv::IMREAD_COLOR);

        return result;
    }

    static bool readStringList(const std::string &filename, std::vector<std::string> &l)
    {
        l.clear();
        cv::FileStorage fs(filename, cv::FileStorage::READ);
        if (!fs.isOpened())
            return false;
        cv::FileNode n = fs.getFirstTopLevelNode();
        if (n.type() != cv::FileNode::SEQ)
            return false;
        cv::FileNodeIterator it = n.begin(), it_end = n.end();
        for (; it != it_end; ++it)
            l.push_back((std::string)*it);
        return true;
    }
public:
    cv::Size boardSize;              // The size of the board -> Number of items by width and height
    Pattern calibrationPattern;  // One of the Chessboard, circles, or asymmetric circle pattern
    float squareSize;            // The size of a square in your defined unit (point, millimeter,etc).
    int nrFrames;                // The number of frames to use from the input for calibration
    float aspectRatio;           // The aspect ratio
    int delay;                   // In case of a video input
    bool writePoints;            // Write detected feature points
    bool writeExtrinsics;        // Write extrinsic parameters
    bool calibZeroTangentDist;   // Assume zero tangential distortion
    bool calibFixPrincipalPoint; // Fix the principal point at the center
    bool flipVertical;           // Flip the captured images around the horizontal axis
    std::string outputFileName;       // The name of the file where to write
    bool showUndistorsed;        // Show undistorted images after calibration
    std::string input;                // The input ->
    bool useFisheye;             // use fisheye camera model for calibration

    int cameraID;
    std::vector<std::string> imageList;
    size_t atImageList;
    cv::VideoCapture inputCapture;
    InputType inputType;
    bool goodInput;
    int flag;

private:
    std::string patternToUse;
};

enum { DETECTION = 0, CAPTURING = 1, CALIBRATED = 2 };

bool runCalibrationAndSave(Settings &s, cv::Size imageSize, cv::Mat  &cameraMatrix, cv::Mat &distCoeffs,
                           std::vector<std::vector<cv::Point2f> > imagePoints);

static void help();
static inline void read(const cv::FileNode &node, Settings &x, const Settings &default_value = Settings());
static inline void write(cv::FileStorage &fs, const cv::String &, const Settings &s);
int calibrateCameraOnce(QWidget* window);
static double computeReprojectionErrors(const std::vector<std::vector<cv::Point3f> > &objectPoints,
                                        const std::vector<std::vector<cv::Point2f> > &imagePoints,
                                        const std::vector<cv::Mat> &rvecs, const std::vector<cv::Mat> &tvecs,
                                        const cv::Mat &cameraMatrix, const cv::Mat &distCoeffs,
                                        std::vector<float> &perViewErrors, bool fisheye);
static void calcBoardCornerPositions(cv::Size boardSize, float squareSize, std::vector<cv::Point3f> &corners,
                                     Settings::Pattern patternType /*= Settings::CHESSBOARD*/);
static bool runCalibration(Settings &s, cv::Size &imageSize, cv::Mat &cameraMatrix, cv::Mat &distCoeffs,
                           std::vector<std::vector<cv::Point2f> > imagePoints, std::vector<cv::Mat> &rvecs, std::vector<cv::Mat> &tvecs,
                           std::vector<float> &reprojErrs, double &totalAvgErr);
static void saveCameraParams(Settings &s, cv::Size &imageSize, cv::Mat &cameraMatrix, cv::Mat &distCoeffs,
                             const std::vector<cv::Mat> &rvecs, const std::vector<cv::Mat> &tvecs,
                             const std::vector<float> &reprojErrs, const std::vector<std::vector<cv::Point2f> > &imagePoints,
                             double totalAvgErr);
bool runCalibrationAndSave(Settings &s, cv::Size imageSize, cv::Mat &cameraMatrix, cv::Mat &distCoeffs,
                           std::vector<std::vector<cv::Point2f> > imagePoints);


#endif
