#pragma once
#ifndef ERRORHANDLING_H_
#define ERRORHANDLING_H_

#include <iostream>
#include <fstream>

using namespace std;

void writeQuitMessage();
void writeErrorFile(exception &e);

#endif