#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int start = 0;
    char label[20], mneumonic[20], operand[20];
    char opcode[20], code[20], symbol[20], symboladdress[20];
    char locctr[20], length[20],size[20];

    FILE *inter = fopen("inter.txt", "r");
    FILE *op = fopen("optab.txt", "r");
    FILE *sym = fopen("symtab.txt", "r");
    FILE *len = fopen("length.txt", "r");
    FILE *obj = fopen("object.txt", "w");
    //FILE *listing = fopen("listing.txt", "w");

    if ( !op || !sym || !len || !inter || !obj  ) {
        printf("Error opening files!\n");
        exit(1);
    }

    // Read the first line (START)
    //1009	ALPHA	WORD	2
    fscanf(inter, "%s %s %s %s", locctr, label, mneumonic, operand);
    fscanf(len, "%s %s", length,size);
    //fprintf(listing,"****\t%s\t%s\t%s\n",label,mneumonic,operand);

    if (strcmp(mneumonic, "START") == 0) {
        start = (int)strtol(operand, NULL, 16); // Convert hex to int
        fprintf(obj, "H^%s^%06X^%06s\n", label, start, length);
        fprintf(obj, "T^%06X^%02X", start,atoi(size));
        fscanf(inter, "%s %s %s %s", locctr, label, mneumonic, operand);
    }

    while (strcmp(mneumonic, "END") != 0) {
        int flag = 0;
        rewind(op);

        while (fscanf(op, "%s %s", opcode, code) != EOF) {
            if (strcmp(opcode, mneumonic) == 0) {
                flag = 1;
                rewind(sym);

                while (fscanf(sym, "%s %s", symbol, symboladdress) != EOF) {
                    if (strcmp(symbol, operand) == 0) {
                        fprintf(obj, "^%s%s", code, symboladdress);
                        break;
                    }
                }
                break;
            }
        }

        if (flag == 0) {
            if (strcmp(mneumonic, "WORD") == 0) {
                fprintf(obj, "^%06d", atoi(operand));
               // fprintf(listing,"%06X\n", atoi(operand));
            } else if (strcmp(mneumonic, "BYTE") == 0) {
                fprintf(obj,"^");
                if (operand[0] == 'C') {
                    for (int i = 2; i < strlen(operand) - 1; i++)
                        if(operand[i] >= '0' && operand[i] <= '9'){
                            fprintf(obj, "%02X", operand[i]-'0');
                        }else{
                            fprintf(obj, "%02X", operand[i]);
                        }
                        //fprintf(object, "%02X", operand[i]);
                } else if (operand[0] == 'X') {
                    for (int i = 2; i < strlen(operand) - 1; i++)
                        fprintf(obj, "%c", operand[i]);
                }
            }
        }
        //fprintf(listing, "%s\t%s  \t%s  \t%s\t", locctr, label, mneumonic, operand);
        
        fscanf(inter, "%s %s %s %s", locctr, label, mneumonic, operand);
    }

    fprintf(obj, "\nE^%06X", start);

    //fclose(i);
    fclose(op);
    fclose(sym);
    fclose(len);
    fclose(obj);
    fclose(inter);
    //fclose(listing);

    printf(" Object Program generated successfully in 'object.txt'\n");
    return 0;
}


