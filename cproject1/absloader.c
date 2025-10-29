#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *fp1, *fp2;
    int i, j, address;
    char ch, line[500], addr[100], name[500], pgmName[500];

    fp1 = fopen("object.txt", "r");
    fp2 = fopen("memory.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file\n");
        return;
    }

    fscanf(fp1, "%s", line);

    if (line[0] == 'H') {
        for (i = 2, j = 0; j < 4; i++, j++) {
            pgmName[j] = line[i];
        }
        pgmName[j] = '\0';
    }

    printf("Program Name : %s\n", pgmName);

    while (fscanf(fp1, "%s", line) == 1) {
        if (line[0] == 'T') {
            for (i = 2, j = 0; i <= 7; i++, j++)
                addr[j] = line[i];
            addr[j] = '\0';
            address = (int)strtol(addr, NULL, 16);

            i = 12;
            while (line[i] != '\0') {
                if (line[i] != '^') {
                    printf("%X\t%c%c\n", address, line[i], line[i + 1]);
                    fprintf(fp2, "%X\t%c%c\n", address, line[i], line[i + 1]);
                    address++;
                    i = i + 2;
                } else {
                    i++;
                }
            }
        } else if (line[0] == 'E') {
            break;
        }
    }

    fclose(fp1);
    fclose(fp2);
}
