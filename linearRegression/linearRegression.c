#include "linearRegression.h"
#include <stdio.h>

DataPoint average(DataPoint* array, int size) {
    double xSum = 0;
    double ySum = 0;
    
    for (int i = 0; i < size; i++) {
        xSum += array[i].x;
        ySum += array[i].y;       
    }

    double xAvg = xSum / size;
    double yAvg = ySum / size;
    DataPoint averages = {xAvg, yAvg};

    return averages;
}

double calculateSlope(DataPoint averages, DataPoint* array, int size) {
    double numerator = 0;
    double denominator = 0;

    for (int i = 0; i < size; i++) {
        double deltaX = array[i].x - averages.x;
        double deltaY = array[i].y - averages.y;

        numerator += deltaX * deltaY;
        denominator += deltaX * deltaX;
    }

    return numerator / denominator;
}

double calculateYIntercept(DataPoint averages, double slope) {
    double yIntercept = averages.y - slope * averages.x;

    return yIntercept;
}

DataPoint calculate(DataArray data) {
    DataPoint averages = average(data.array, data.size);

    double slope = calculateSlope(averages, data.array, data.size);
    double yIntercept = calculateYIntercept(averages, slope);

    DataPoint result = {slope, yIntercept};

    return result;    
}

