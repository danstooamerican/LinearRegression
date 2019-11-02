#include "linearRegression.h"
#include <stdio.h>

DataPoint average(DataPoint* array, int size) 
{
    double xSum = 0;
    double ySum = 0;
    
    for (int i = 0; i < size; i++) 
    {
        xSum += array[i].x;
        ySum += array[i].y;       
    }

    double xAvg = xSum / size;
    double yAvg = ySum / size;
    DataPoint averages = {xAvg, yAvg};

    return averages;
}

double calculateSlope(DataPoint averages, DataPoint* array, int size) 
{
    double numerator = 0;
    double denominator = 0; 

    for (int i = 0; i < size; i++) 
    {
        double deltaX = array[i].x - averages.x;
        double deltaY = array[i].y - averages.y;

        numerator += deltaX * deltaY;
        denominator += deltaX * deltaX;
    }

    printf("%lf and %lf\n", numerator, denominator);

    return numerator / denominator;
}

double calculateYIntercept(DataPoint averages, double slope) 
{
    double yIntercept = averages.y - slope * averages.x;

    return yIntercept;
}

DataPoint calculate(DataArray data) 
{
    DataPoint averages = average(data.array, data.size);

    printf("avg %lf and %lf\n", averages.x, averages.y);

    double slope = calculateSlope(averages, data.array, data.size);
    double yIntercept = calculateYIntercept(averages, slope);

    DataPoint result = {slope, yIntercept};

    return result;    
}

void reduceFraction(Fraction *out, long n, long m)
{
    int gcd, remainder;

    while (n != 0)
    {
        remainder = m % n;
        m = n;
        n = remainder;
    }

    gcd = m;

    out->numerator = out->numerator / gcd;
    out->denominator = out->denominator / gcd;
}

void addFraction(Fraction *a, Fraction b)
{
    *a = (Fraction){a->numerator * b.denominator + b.numerator * a->denominator, a->denominator * b.denominator};
}

void subFraction(Fraction *a, Fraction b)
{
    *a = (Fraction){a->numerator * b.denominator - b.numerator * a->denominator, a->denominator * b.denominator};
}

void mulFraction(Fraction *a, Fraction b)
{
    *a = (Fraction){a->numerator * b.numerator, a->denominator * b.denominator};
}

void divFraction(Fraction *a, Fraction b)
{
    *a = (Fraction){a->numerator * b.denominator, a->denominator * b.numerator};
}

ExactDataPoint averageExact(ExactDataPoint* array, int size) 
{
    Fraction xSum = {0, 1};
    Fraction ySum = {0, 1};
    
    for (int i = 0; i < size; i++) 
    {
        addFraction(&xSum, array[i].x);
        addFraction(&ySum, array[i].y);      
    }

    Fraction xAvg = {xSum.numerator, xSum.denominator * size};
    Fraction yAvg = {ySum.numerator, ySum.denominator * size};

    reduceFraction(&xAvg, xAvg.numerator, xAvg.denominator);
    reduceFraction(&yAvg, yAvg.numerator, yAvg.denominator);

    ExactDataPoint averages = {xAvg, yAvg};

    return averages;
}

Fraction calculateSlopeExact(ExactDataPoint averages, ExactDataPoint* array, int size) 
{
    Fraction numerator = {0, 1};
    Fraction denominator = {0, 1};

    for (int i = 0; i < size; i++) 
    {
        Fraction deltaX = array[i].x;
        subFraction(&deltaX, averages.x);

        reduceFraction(&deltaX, deltaX.numerator, deltaX.denominator);

        Fraction deltaY = array[i].y;
        subFraction(&deltaY, averages.y);

        reduceFraction(&deltaY, deltaY.numerator, deltaY.denominator);

        Fraction numeratorToAdd = deltaX;
        mulFraction(&numeratorToAdd, deltaY);

        reduceFraction(&numeratorToAdd, numeratorToAdd.numerator, numeratorToAdd.denominator);

        Fraction denominatorToAdd = deltaX;
        mulFraction(&denominatorToAdd, deltaX);

        reduceFraction(&denominatorToAdd, denominatorToAdd.numerator, denominatorToAdd.denominator);

        addFraction(&numerator, numeratorToAdd);
        addFraction(&denominator, denominatorToAdd);

        reduceFraction(&numerator, numerator.numerator, numerator.denominator);
        reduceFraction(&denominator, denominator.numerator, denominator.denominator);
    }

    printf("%lli/%lli ~%lf and %lli/%lli ~%lf\n",   numerator.numerator, numerator.denominator, numerator.numerator / (double)numerator.denominator, 
                                                denominator.numerator, denominator.denominator, denominator.numerator / (double)denominator.denominator);

    Fraction result = numerator;
    divFraction(&result, denominator);

    return result;
}

Fraction calculateYInterceptExact(ExactDataPoint averages, Fraction slope) 
{
    Fraction val1 = slope;
    mulFraction(&val1, averages.x);

    Fraction yIntercept = averages.y;
    subFraction(&yIntercept, val1);

    reduceFraction(&yIntercept, yIntercept.numerator, yIntercept.denominator);

    return yIntercept;
}

ExactDataPoint calculateExact(ExactDataArray data)
{
    ExactDataPoint averages = averageExact(data.array, data.size);

    printf("avg %lli/%lli ~%lf and %lli/%lli ~%lf\n",   averages.x.numerator, averages.x.denominator, averages.x.numerator / (double)averages.x.denominator, 
                                                averages.y.numerator, averages.y.denominator, averages.y.numerator / (double)averages.y.denominator);

    Fraction slope = calculateSlopeExact(averages, data.array, data.size);
    Fraction yIntercept = calculateYInterceptExact(averages, slope);

    ExactDataPoint result = {slope, yIntercept};

    return result;
}

