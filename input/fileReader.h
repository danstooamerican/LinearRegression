#ifndef FILEREADER_H
#define FILEREADER_H

#include "../linearRegression/linearRegression.h"

typedef struct {
    int size;
    DataPoint* array;
} DataArray;

extern DataArray readFile(char*);

#endif