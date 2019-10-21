#include "fileReader.h"
#include <stdio.h>
#include <stdlib.h>

DataPoint* readFile(char* path) {
    FILE *fp = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    
    if (fp == NULL) {
        printf("Error opening file.\n");
    } else {
        while(getline(&line, &len, fp) != -1) {
            printf("%s\n", line);
        }

        fclose(fp);
        free(line);
    }    
}