#include "directoryAccessFunctions.h"

DIR *imagesDirectory;
struct dirent *entity;

void writeFolderContentsToAFile()
{
    int lineCounter = 0;
    ofstream imageCalibrationInputFile;
    imageCalibrationInputFile.open("VID5.xml");

    imageCalibrationInputFile << "<?xml version=\"1.0\"?>" << endl
                              << "<opencv_storage>" << endl
                              << "\t<images>" << endl;

    if ((imagesDirectory = opendir("images\\")) != NULL)
    {
        while ((entity = readdir(imagesDirectory)) != NULL)
        {
            lineCounter++;
            if (lineCounter > 2)
                imageCalibrationInputFile << "\t\timages/" << entity->d_name << endl;
        }
        imageCalibrationInputFile << "\t</images>" << endl
                                  << "</opencv_storage>";
        closedir(imagesDirectory);
        imageCalibrationInputFile.close();
    }
    else
    {
        cerr << "Could not open this directory." << endl;
    }
}