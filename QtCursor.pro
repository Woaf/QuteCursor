#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T14:16:28
#
#-------------------------------------------------

QT       += core gui
#CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCursor
TEMPLATE = app

RC_FILE = qutecursor.rt

INCLUDEPATH += C:\\opencv31\\build\\include
CONFIG(debug,debug|release) {
    LIBS += -LE:\\opencvqtbuild\\lib\\Debug \
            -lopencv_calib3d310d \
            -lopencv_core310d \
            -lopencv_features2d310d \
            -lopencv_flann310d \
            -lopencv_highgui310d \
            -lopencv_imgcodecs310d \
            -lopencv_imgproc310d \
            -lopencv_ml310d \
            -lopencv_objdetect310d \
            -lopencv_photo310d \
            -lopencv_shape310d \
            -lopencv_stitching310d \
            -lopencv_superres310d \
            -lopencv_ts310d \
            -lopencv_video310d \
            -lopencv_videoio310d \
            -lopencv_videostab310d
}

CONFIG(release,debug|release) {
    LIBS += -LE:\\opencvqtbuild\\lib\\Release \
            -lopencv_calib3d310 \
            -lopencv_core310 \
            -lopencv_features2d310 \
            -lopencv_flann310 \
            -lopencv_highgui310 \
            -lopencv_imgcodecs310 \
            -lopencv_imgproc310 \
            -lopencv_ml310 \
            -lopencv_objdetect310 \
            -lopencv_photo310 \
            -lopencv_shape310 \
            -lopencv_stitching310 \
            -lopencv_superres310 \
            -lopencv_ts310 \
            -lopencv_video310 \
            -lopencv_videoio310 \
            -lopencv_videostab310
}

INCLUDEPATH += E:\\dlib-19.2
LIBS += -lgdi32 -lcomctl32 -luser32 -lwinmm -lws2_32

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        qutecursor.cpp\
    ../../../dlib-19.2/dlib/all/source.cpp \
    calculationFunctions.cpp \
    directoryAccessFunctions.cpp \
    errorHandling.cpp \
    fileHandlerFunctions.cpp \
    headPoseCursor.cpp \
    developmentalFunctions.cpp \
    messages.cpp \
    cameraCalibration.cpp

HEADERS  += qutecursor.h \
    cameraCalibration.h \
    directoryAccessFunctions.h \
    dirent.h \
    errorHandling.h \
    fileHandlerFunctions.h \
    headPoseCursor.h \
    developmentalFunctions.h \
    messages.h \
    calculationFunctions.h

FORMS    += qutecursor.ui
