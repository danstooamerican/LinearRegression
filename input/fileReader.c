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
    } else {
        *array = temp;
    }   
}

DataArray readFile(char* path) {
    FILE *fp = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    
    if (fp == NULL) {
        printf("Error opening file.\n");
    } else {
        int readDataPoints = 0;
        int size = 4;

        DataPoint *dataPoints;
        dataPoints = (DataPoint*) malloc(size * sizeof(DataPoint));

        while(getline(&line, &len, fp) != -1) {
            if (readDataPoints == size) {
                resizeArray(&dataPoints, size * 2);
                size *= 2;
            }
            DataPoint dataPoint;

            char *valuePair = strtok(line, " ");

            dataPoint.x = atof(&valuePair[0]);
            dataPoint.y = atof(&valuePair[1]);

            dataPoints[readDataPoints] = dataPoint;
            readDataPoints++;
        }

        fclose(fp);
        free(line);

        DataArray dataArray;
        dataArray.array = dataPoints;
        dataArray.size = readDataPoints;

        return dataArray;
    }    
}