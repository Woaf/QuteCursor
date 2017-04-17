// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

This example program shows how to find frontal human faces in an image and
estimate their pose.  The pose takes the form of 68 landmarks.  These are
points on the face such as the corners of the mouth, along the eyebrows, on
the eyes, and so forth.


This face detector is made using the classic Histogram of Oriented
Gradients (HOG) feature combined with a linear classifier, an image pyramid,
and sliding window detection scheme.  The pose estimator was created by
using dlib's implementation of the paper:
One Millisecond Face Alignment with an Ensemble of Regression Trees by
Vahid Kazemi and Josephine Sullivan, CVPR 2014
and was trained on the iBUG 300-W face landmark dataset.

Also, note that you can train your own models using dlib's machine learning
tools.  See train_shape_predictor_ex.cpp to see an example.


Finally, note that the face detector is fastest when compiled with at least
SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
chip then you should enable at least SSE2 instructions.  If you are using
cmake to compile this program you can enable them by using one of the
following commands when you create the build project:
cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
This will set the appropriate compiler options for GCC, clang, Visual
Studio, or the Intel compiler.  If you are using another compiler then you
need to consult your compiler's manual to determine how to enable these
instructions.  Note that AVX is the fastest but requires a CPU from at least
2011.  SSE4 is the next fastest and is supported by most current machines.
*/

#include "welcomeMessage.h"
#include "directoryAccessFunctions.h"
#include "cameraCalibration.h"
#include "fileHandlerFunctions.h"
#include "calculaitonFunctions.h"
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

#include <QApplication>
#include <QMessageBox>

using namespace std;
using namespace dlib;
using namespace cv;

// ----------------------------------------------------------------------------------------

void runCameraCalib()
{
    writeFolderContentsToAFile();
    QMessageBox::StandardButton quit;
    quit = QMessageBox::question(new QWidget, "Camera calibration", "Are you sure you want calibrate Your camera?", QMessageBox::Yes|QMessageBox::No);
    if (quit == QMessageBox::Yes)
    {
        if (calibrateCameraOnce() != 0)
        {
            cout << "Cannot callibrate camera!" << endl;
        }
    }
}

int runHeadCursor()
{
    try
    {
        // elinditjuk az elsodleges kamerat
        VideoCapture cap(0);
        if (!cap.isOpened())
        {
            cout << "Could not detect camera!" << endl;
            return -1;
        }

        ifstream cameraMatrixFile;
        cameraMatrixFile.open("cameraMatrixFile");
        if (!cameraMatrixFile.is_open())
        {
            cout << "Could not open an existing camera matrix file." << endl;
            cout << "Opening default camera matrix file." << endl;
            createCameraMatrixFile();
        }

        // a kallibracio eredmenye:
        double focalLength_fx;
        double focalLength_fy;

        readAndSetCameraClaibrationValues(focalLength_fx, focalLength_fy);

        // az ablak, ahova kirajzoljuk a kamerat es a felismert arcokat
        image_window win;
        win.clear_overlay();
        win.set_pos(0, 0);
        // camera input dimensions: 480p -> 640x480
        image_window win2;
        win2.clear_overlay();
        win2.set_size(640, 480);
        win2.set_pos(640, 0);

        // Beolvassuk a mesh koordinatakat egy tombbe
        Point3d meshFacePoints[49];
        returnMeshPointsFromAFile(meshFacePoints);
        // kulon kiemeljuk a P3P-hez hasznalt harom pontot a modellbol
        Point3d mesh_rightEye(42.9242, -26.283, -14.6029 );
        Point3d mesh_leftEye(-41.8163, -25.2319, -15.2555);
        Point3d mesh_noseTip(-0.498939, 11.9414, 25.9834 );

        // We need a face detector.  We will use this to get bounding boxes for
        // each face in an image.
        frontal_face_detector detector = get_frontal_face_detector();
        // And we also need a shape_predictor.  This is the tool that will predict face
        // landmark positions given an image and face bounding box.  Here we are just
        // loading the model from the shape_predictor_68_face_landmarks.dat file you gave
        // as a command line argument.
        shape_predictor sp;
        // argv[1] -> shape_predictor_68_face_landmarks.dat (az arcfelismereshez hasznalt dlib adatfajl ~ 97Mb)
        deserialize("shape_predictor_68_face_landmarks.dat") >> sp;

        // amig be nem zarjuk az ablakot
        while (!win.is_closed())
        {

            // eltaroljuk a kamera adatiat egy matrixban, es atkonvertaljuk egy dlib altal kezelheto
            // image adattagra, amivel tud dolgozni a detector
            Mat cameraInformationUnflipped;
            cap >> cameraInformationUnflipped;

            Mat bg;
            bg = imread("bg.jpg");
            cv_image<dlib::bgr_pixel> info(bg);

            // tukrozzuk a kamera kepet
            Mat cameraInformation;
            // cv::flip(source matrix, destination matrix, 1 for horizontal flip)
            flip(cameraInformationUnflipped, cameraInformation, 1);

            // a dlib szamara ertelmezheto tipusra konvertaljuk a kamera adatait
            cv_image<bgr_pixel> image_cameraInformation(cameraInformation);

            // felismert arcok egy boxban (egyenkent)
            std::vector<dlib::rectangle> faces = detector(image_cameraInformation);

            // felismert arcok
            std::vector<full_object_detection> shapes;
            for (unsigned long i = 0; i < faces.size(); i++)
            {
                shapes.push_back(sp(image_cameraInformation, faces[i]));

                // Step 1: A koordinatak normalizalasa (iplimage)
                // Pontok definialasa
                // A kameratol megkapott
                // elosztjuk oket a kalibracio utan kapott fx es fy ertekekkel
                Point3d rightEye_raw((shapes[0].part(45).x()), (shapes[0].part(45).y()), 1);
                Point3d leftEye_raw((shapes[0].part(36).x() ), (shapes[0].part(36).y()), 1);
                Point3d noseTip_raw((shapes[0].part(30).x() ), (shapes[0].part(30).y()), 1);
                Point3d centroidOf_rawFacePoints = returnCentroidOfThreePoints(2, rightEye_raw, leftEye_raw, noseTip_raw);

                rightEye_raw = returnUnitRemovedPoints(rightEye_raw, centroidOf_rawFacePoints, focalLength_fx, focalLength_fy);
                leftEye_raw = returnUnitRemovedPoints(leftEye_raw, centroidOf_rawFacePoints, focalLength_fx, focalLength_fy);
                noseTip_raw = returnUnitRemovedPoints(noseTip_raw, centroidOf_rawFacePoints, focalLength_fx, focalLength_fy);

                // Normalizalo hanyados definialasa
                double normalizingCoefficientOf_rigthEye = returnThreeDimensionalDistance(rightEye_raw);
                double normalizingCoefficientOf_leftEye = returnThreeDimensionalDistance(leftEye_raw);
                double normalizingCoefficientOf_noseTip = returnThreeDimensionalDistance(noseTip_raw);

                // Uj normalizalt koordinatak az 1 sugaru gombon
                Point3d rightEye_normalized = rightEye_raw / normalizingCoefficientOf_rigthEye;
                Point3d leftEye_normalized = leftEye_raw / normalizingCoefficientOf_leftEye;
                Point3d noseTip_normalized = noseTip_raw / normalizingCoefficientOf_noseTip;

                // a felismert arc pontjai kozepre igazitva
                Point drawable_rightEye = returnDrawablePoint(rightEye_normalized, normalizingCoefficientOf_rigthEye*focalLength_fx, 320, 240);
                Point drawable_leftEye = returnDrawablePoint(leftEye_normalized, normalizingCoefficientOf_leftEye*focalLength_fx, 320, 240);
                Point drawable_noseTip = returnDrawablePoint(noseTip_normalized, normalizingCoefficientOf_noseTip*focalLength_fx, 320, 240);
                Scalar blue = Scalar(255, 0, 0);
                Scalar green = Scalar(0, 255, 0);
                Scalar red = Scalar(0, 0, 255);
                circle(bg, drawable_rightEye, 15, blue,  2, 8);
                circle(bg, drawable_leftEye, 15, green, 2, 8);
                circle(bg, drawable_noseTip, 15, red,   2, 8);

                // Step 2: elokszitjuk a p3p egyenletrendszert
                // az elek altal bezart szogek
                //A: right eye normalized
                //B: left eye normalized
                //C: nose tip normalized

                /*
                double cosines[3] = { 0, 0, 0 };
                returnAnglesBetweenThreePoints(cosines, rightEye_normalized, leftEye_normalized, noseTip_normalized);

                double cosineOf_UV = cosines[0];
                double cosineOf_UW = cosines[1];
                double cosineOf_VW = cosines[2];

                // AB<-(szemek kozti tavolsag), BC<-(bal szem es orr tavolsaga), AC<-(jobb szem es orr tavolsaga):
                double distanceOf_AB = returnThreeDimensionalDistance(mesh_rightEye, mesh_leftEye);
                double distanceOf_BC = returnThreeDimensionalDistance(mesh_leftEye, mesh_noseTip);
                double distanceOf_AC = returnThreeDimensionalDistance(mesh_rightEye, mesh_noseTip);
                */

                // OWN METHOD:

                double distanceOf_PA = returnThreeDimensionalDistance(rightEye_normalized);
                double distanceOf_PB = returnThreeDimensionalDistance(leftEye_normalized);
                double distanceOf_PC = returnThreeDimensionalDistance(noseTip_normalized);

                // Step 4: megtallajuk a 3d koordinatakat az A B es C pontokhoz
                // A = rightEye_normalized * || PA ||
                // B =  leftEye_normalized * || PB ||
                // C =  noseTip_normlaized * || PC ||

                Point3d correspondingPointOf_A = rightEye_normalized * 1000;
                Point3d correspondingPointOf_B = leftEye_normalized *  1000;
                Point3d correspondingPointOf_C = noseTip_normalized *  1000;
                correspondingPointOf_A.z /= -100;
                correspondingPointOf_B.z /= -100;
                correspondingPointOf_C.z /= 40;

                Point asdf = returnDrawablePoint(correspondingPointOf_A,  1, 320, 240);
                Point asdf2 = returnDrawablePoint(correspondingPointOf_B, 1, 320, 240);
                Point asdf3 = returnDrawablePoint(correspondingPointOf_C, 1, 320, 240);

                Scalar yellow(0, 255, 255);
                circle(bg, asdf, 5, yellow, 2, 3);
                circle(bg, asdf2, 5, yellow, 2, 3);
                circle(bg, asdf3, 5, yellow, 2, 3);

                // Step 5: forgatasi matrix es mozgatasi (transzlacios) vektor kiszamitasa
                // B = R*A + t (ahol B a mesh ponjtai, es A az arc pontjai)
                // 1) A 'centroid'-ok kiszamitasa mindket ponthalmazra
                // 2) Az origoba transzformalas, hogy megtalaljuk az optimalis forgatasi matrixot
                // 3) A transfomacios vektor kiszamolasa

                // 1 Cenrtoidok
                // FONTOS: legyenek a mesh pointok a 3d mesh pontjai!!!!

                Point3d centroidOf_MeshPoints = returnCentroidOfThreePoints(3, mesh_rightEye, mesh_leftEye, mesh_noseTip);
                Point3d centroidOf_CorrespondingPoints = returnCentroidOfThreePoints(2, correspondingPointOf_A, correspondingPointOf_B, correspondingPointOf_C);

                // 2 centroidok kozepre huzasa a hozzajuk tartozo ponthalmazokkal

                Point fdsa = returnDrawablePoint(mesh_rightEye, 1, 320, 240);
                Point fdsa2 = returnDrawablePoint(mesh_leftEye, 1, 320, 240);
                Point fdsa3 = returnDrawablePoint(mesh_noseTip, 1, 320, 240);

                Scalar cyan(255, 255, 0);
                circle(bg, fdsa, 5, cyan, 2, 3);
                circle(bg, fdsa2, 5, cyan, 2, 3);
                circle(bg, fdsa3, 5, cyan, 2, 3);

                // 3 a forgatasi matrix kiszamolasa
                // eloszor eltaroljuk a szukseges szamokat egy vektorban
                // ___      [ x y z ]
                // \     [x] x2 xy xz
                // /     |y| xy y2 yz
                // ^^^   [z] xz yz z2
                //
                Mat_<double> HMatrix = Mat_<double>::ones(3, 3);
                Mat_<double> HMat2   = Mat_<double>::ones(3, 3);
                Mat_<double> HMat3   = Mat_<double>::ones(3, 3);
                returnMatrixOfTwoVectors(HMatrix, mesh_rightEye, correspondingPointOf_A);
                returnMatrixOfTwoVectors(HMat2, mesh_leftEye, correspondingPointOf_B);
                returnMatrixOfTwoVectors(HMat3, mesh_noseTip, correspondingPointOf_C);
                HMatrix = HMatrix + HMat2 + HMat3;

                SVD USV = SVD(HMatrix);

                Mat_<double> matrixOf_Rotation = USV.vt.t() * USV.u.t();
                if (determinant(matrixOf_Rotation) < 0)
                {
                    matrixOf_Rotation.col(2) *= -1;
                }

                double rotationRadiansAroundXAxis = atan2(matrixOf_Rotation.at<double>(2, 1), matrixOf_Rotation.at<double>(2, 2));
                //cout << "x axis: " << rotationRadiansAroundXAxis * 180 / pi << endl;
                double rotationRadiansAroundYAxis = atan2(-matrixOf_Rotation.at<double>(2, 0), sqrt(pow(matrixOf_Rotation.at<double>(2, 1), 2) + pow(matrixOf_Rotation.at<double>(2, 2), 2)));
                //cout << "y axis: " << rotationRadiansAroundYAxis * 180 / pi << endl;
                double rotationRadiansAroundZAxis = atan2(matrixOf_Rotation.at<double>(1, 0), matrixOf_Rotation.at<double>(0, 0));
                //cout << "z axis: " << rotationRadiansAroundZAxis << endl;

                // transzlacio vektor kiszamolasa
                Mat_<double> vectorOf_Translation = Mat_<double>(centroidOf_rawFacePoints);
                //cout << "translation: " << endl << vectorOf_Translation << endl;

                // Step 6: kirajzolunk koroket a szemek es az orr pontjaihoz
                // beszorozzuk a mesh pontokat a forgatasi matrixal
                // es hozza adjuk a transzlacios vektort

                Mat_<double> meshContainer;
                Point3d mesh3d;
                Point drawablePoint;
                Scalar deepblue(143, 72, 21);
                for (int i = 0; i < 49; i++)
                {
                    meshContainer = matrixOf_Rotation * Mat_<double>(meshFacePoints[i]);
                    mesh3d = Point3d(meshContainer.at<double>(0, 0), meshContainer.at<double>(0, 1), meshContainer.at<double>(0, 2));
                    drawablePoint = returnDrawablePoint(mesh3d, 1, 320, 240);
                    circle(bg, drawablePoint, 2, deepblue, 2, 0, 0);
                }

                // Step 7: move cursor
                //ShowCursor(0);

                POINT currentCursorPos;
                GetCursorPos(&currentCursorPos);

                double move_on_y;
                double move_on_x;

                if ((abs(rotationRadiansAroundZAxis) < 0.20))
                {
                    leftMouseButtonReleaseEvent();
                }
                else
                {
                    //cout << "left click" << endl;
                    leftMouseButtonDownEvent();
                }

                if (rotationRadiansAroundXAxis < 0)
                {
                    move_on_y = 2386.86 * -rotationRadiansAroundXAxis + 1370.5;
                }
                else
                {
                    move_on_y = 2741 * -rotationRadiansAroundXAxis + 1370.5;
                }
                move_on_x = 16522.1 * rotationRadiansAroundYAxis + 1440;

                Point2d smoothTransition(0.9*currentCursorPos.x + 0.1*move_on_x, 0.9*currentCursorPos.y + 0.1*move_on_y );

                SetCursorPos((int)smoothTransition.x, (int)smoothTransition.y);

            }

            // kirajzoljuk az arcokat
            win.clear_overlay();
            win2.clear_overlay();
            win.set_image(image_cameraInformation);
            win.add_overlay(render_face_detections(shapes));
            win2.set_background_color(255, 255, 255);
            win2.set_image(info);
        }
    }
    // HIBA eseten
    catch (exception &e)
    {
        writeErrorFile(e);
        return -1;
    }

    showAppreciationMessage();
    showCopyrightMessage();

    return 0;
}

//----------------------------------------------------------------
