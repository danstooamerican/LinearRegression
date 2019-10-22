#include <stdio.h>
#include <stdlib.h>
#include "input/fileReader.h"

void printValues(DataArray values) {
    const char LIST_OPTION = 'l';
    printf("%i value pairs have been loaded. Press '%c' to display a list or hit enter.\n", values.size, LIST_OPTION);

    char c;
    c = getchar();

    printf("\n");

    if (c == LIST_OPTION) {
        DataPoint *array = values.array;
        for (int i = 0; i < values.size; i++) {
            printf("%lf : %lf\n", array[i].x, array[i].y);
        }
    }

    printf("\n");
}

/*
    The user passes one argument to the program.
    arg[1]: Name of a text file which is located in the program folder.

    Text file format:
    xValue1 yValue1
           .
           .
           .
    xValueN yValueN

    Values are decimal numbers like -1, 42, 5.1, 7.0012
*/
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Missing argument: Path to data file.\n");

        return EXIT_FAILURE;
    }

    const int DATA_PATH = 1;
    
    DataArray values;
    values = readFile(argv[DATA_PATH]);

    printValues(values);

    return EXIT_SUCCESS;
}

