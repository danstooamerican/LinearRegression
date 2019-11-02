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

typedef struct {
    long long numerator;
    long long denominator;
} Fraction;

typedef struct {
    Fraction x;
    Fraction y;
} ExactDataPoint;

typedef struct {
    int size;
    ExactDataPoint* array;
} ExactDataArray;

#endif