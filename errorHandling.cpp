#include "errorHandling.h"

using namespace std;

void writeQuitMessage()
{
    cout << "Press 'q' then Enter to exit." << endl;
}

void writeErrorFile(exception &e)
{
    ofstream myFile;
    myFile.open("C:/Users/balin/Desktop/error_message.txt");
    myFile << "EXCEPTION THROWN: \n" << e.what();
    myFile.close();
}
