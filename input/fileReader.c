#include "fileReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void resizeArray(DataPoint** array, size_t n)
{
    DataPoint *temp = (DataPoint*)realloc(*array, (n * sizeof(**array)));

    if (temp == NULL)
    {
        printf("Cannot allocate more memory.\n");
        free(temp);
    } else {
        *array = temp;
    }   
}

DataArray readFile(char* path) {
    FILE *fp = fopen(path, "r");
    
    if (fp == NULL) {
        printf("Error opening file.\n");
    } else {
        int readDataPoints = 0;
        int size = 1;

        DataPoint *dataPoints;
        dataPoints = (DataPoint*) malloc(size * sizeof(DataPoint));

        const int MAX_READ = 1024;
        char str[MAX_READ];
        while (fgets(str, MAX_READ, fp) != NULL) {
            if (readDataPoints == size) {
                resizeArray(&dataPoints, size * 2);
                size *= 2;
            }            

            char *xValue = strtok(str, " ");
            char *yValue = strtok(NULL, " ");

            DataPoint dataPoint = {atof(xValue), atof(yValue)};
            
            dataPoints[readDataPoints] = dataPoint;
            readDataPoints++;
        }

        fclose(fp);

        DataArray dataArray = {readDataPoints, dataPoints};

        return dataArray;
    }    
}