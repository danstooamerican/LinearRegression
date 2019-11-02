#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "input/fileReader.h"
#include "linearRegression/linearRegression.h"

void printValues(DataArray values) {
    const char LIST_OPTION = 'l';
    printf("%i value pairs have been loaded. Press '%c' to display a list or hit enter.\n", values.size, LIST_OPTION);

    char c;
    c = getchar();

    printf("\n");

    if (c == LIST_OPTION) {
        DataPoint *array = values.array;
        for (int i = 0; i < values.size; i++) {
            printf("x: %lf : y: %lf\n", array[i].x, array[i].y);
        }
    }

    printf("\n");
}

void printResult(DataPoint result) {
    printf("Result:\n");
    printf("b* = %lf\n", result.x);
    printf("a* = %lf\n", result.y);
}

void printValuesExact(ExactDataArray values) {
    const char LIST_OPTION = 'l';
    printf("%i value pairs have been loaded. Press '%c' to display a list or hit enter.\n", values.size, LIST_OPTION);

    char c;
    c = getchar();

    printf("\n");

    if (c == LIST_OPTION) {
        ExactDataPoint *array = values.array;
        for (int i = 0; i < values.size; i++) {
            printf("x: %lli/%lli : y: %lli/%lli\n", array[i].x.numerator, array[i].x.denominator, array[i].y.numerator, array[i].y.denominator);
        }
    }

    printf("\n");
}

void printResultExact(ExactDataPoint result) {
    printf("Result:\n");
    printf("b* = %lli/%lli\n", result.x.numerator, result.x.denominator);
    printf("a* = %lli/%lli\n", result.y.numerator, result.y.denominator);

    printf("~b* = %lf\n", result.x.numerator / (double)result.x.denominator);
    printf("~a* = %lf\n", result.y.numerator / (double)result.y.denominator);
}

/*
    The user passes one argument to the program.
    arg[1]: Name of a text file which is located in the program folder.
    arg[2]: Optional toggle for exact mode.

    Text file format:
    xValue1 yValue1
           .
           .
           .
    xValueN yValueN

    Values are decimal numbers like -1, 42, 5.1, 7.0012
*/
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Missing argument: Path to data file.\n");

        return EXIT_FAILURE;
    }

    const int DATA_PATH = 1;
    const int EXACT_TOGGLE = 2;

    if (argc == 3 && *argv[EXACT_TOGGLE] == 'e') 
    {
        ExactDataArray values;
        values = readFileExact(argv[DATA_PATH]);

        printValuesExact(values);

        ExactDataPoint result = calculateExact(values);

        printResultExact(result);
    } else
    {
        DataArray values;
        values = readFile(argv[DATA_PATH]);

        printValues(values);

        DataPoint result = calculate(values);

        printResult(result);
    }    

    return EXIT_SUCCESS;
}

