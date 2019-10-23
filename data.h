#ifndef DATA_H
#define DATA_H

typedef struct {
    double x;
    double y;
} DataPoint;

typedef struct {
    int size;
    DataPoint* array;
} DataArray;

#endif