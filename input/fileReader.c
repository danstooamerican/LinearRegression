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

void resizeArrayExact(ExactDataPoint** array, size_t n)
{
    ExactDataPoint *temp = (ExactDataPoint*)realloc(*array, (n * sizeof(**array)));

    if (temp == NULL)
    {
        printf("Cannot allocate more memory.\n");
        free(temp);
    } else {
        *array = temp;
    }   
}

DataPoint parseLine(char *line) 
{
    char *xValue = strtok(line, " ");
    char *yValue = strtok(NULL, " ");

    return (DataPoint){atof(xValue), atof(yValue)};
}

ExactDataPoint parseLineExact(char *line) 
{
    char *xValue = strtok(line, " ");
    char *yValue = strtok(NULL, " ");

    char *xNumerator = strtok(xValue, "/");
    char *xDenominator = strtok(NULL, "/");

    char *yNumerator = strtok(yValue, "/");
    char *yDenominator = strtok(NULL, "/");

    return (ExactDataPoint){{atof(xNumerator), atof(xDenominator)}, {atof(yNumerator), atof(yDenominator)}};
}

DataArray readFile(char* path) 
{
    FILE *fp = fopen(path, "r");
    
    if (fp == NULL) 
    {
        printf("Error opening file.\n");
    } else 
    {
        int readDataPoints = 0;
        int size = 1;

        DataPoint *dataPoints;
        dataPoints = (DataPoint*) malloc(size * sizeof(DataPoint));

        const int MAX_READ = 1024;
        char str[MAX_READ];
        while (fgets(str, MAX_READ, fp) != NULL) 
        {
            if (readDataPoints == size) 
            {
                resizeArray(&dataPoints, size * 2);
                size *= 2;
            }

            DataPoint dataPoint = parseLine(str);
            
            dataPoints[readDataPoints] = dataPoint;
            readDataPoints++;
        }

        fclose(fp);

        return (DataArray){readDataPoints, dataPoints};
    }    
}

ExactDataArray readFileExact(char *path) 
{
    FILE *fp = fopen(path, "r");
    
    if (fp == NULL) 
    {
        printf("Error opening file.\n");
    } else 
    {
        int readDataPoints = 0;
        int size = 1;

        ExactDataPoint *dataPoints;
        dataPoints = (ExactDataPoint*) malloc(size * sizeof(ExactDataPoint));

        const int MAX_READ = 1024;
        char str[MAX_READ];
        while (fgets(str, MAX_READ, fp) != NULL) 
        {
            if (readDataPoints == size) 
            {
                resizeArrayExact(&dataPoints, size * 2);
                size *= 2;
            }
            
            ExactDataPoint dataPoint = parseLineExact(str);
            
            dataPoints[readDataPoints] = dataPoint;
            readDataPoints++;
        }

        fclose(fp);

        ExactDataArray result ={readDataPoints, dataPoints};

        return result;
    }    
}