/* lcatu.c is intended for use on 1 or more files */

#include <stdio.h>

int main(int argc, char** argv) {
    int count = 0;
    if (argc <= 1) {
        printf("not enough arguments, please include at least 1 file name")
    }
    else if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
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
    }
    
    return 0; 
}