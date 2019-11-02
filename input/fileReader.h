#ifndef FILEREADER_H
#define FILEREADER_H

#include "../data.h"
#include "../linearRegression/linearRegression.h"


extern DataArray readFile(char*);

extern ExactDataArray readFileExact(char*);

#endif