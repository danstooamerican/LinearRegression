#include <stdio.h>
#include <stdlib.h>
#include "input/fileReader.h"

/*
    The user passes one argument to the program.
    arg[1]: Full path to a text file including a list of 
*/
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Missing argument: Path to data file.\n");

        return EXIT_FAILURE;
    }

    const int DATA_PATH = 1;
    
    DataPoint *values;
    values = readFile(argv[DATA_PATH]);

    return EXIT_SUCCESS;
}