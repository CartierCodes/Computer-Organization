/* lcat.c is intended for use on only 1 file */

#include <stdio.h>

int main(int argc, char** argv) {
    int count = 0;
    if (argc <= 1) {
        printf("not enough arguments, please include a file name\n");
    }
    else if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        char buffer[60];
        if (fp == NULL) {
            printf("failed to open file\n");
            return 1;
        }
        while (fgets(buffer, 60, fp)) {
            count++;
            printf("%d: %s", count, buffer);
        }
        count = 0;
        printf("\n");
        fclose(fp);
    }
    else if (argc > 2) { 
        printf("lcat.c is designed for use with only 1 file... please retry with only 1 file name");
    }

    return 0;
}