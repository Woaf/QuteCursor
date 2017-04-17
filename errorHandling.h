#pragma once
#ifndef ERRORHANDLING_H_
#define ERRORHANDLING_H_

#include <iostream>
#include <fstream>

void writeQuitMessage();
void writeErrorFile(std::exception &e);

#endif
