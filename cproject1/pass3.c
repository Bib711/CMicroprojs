//logic test
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int start =0;
    char label[20],neumonic[200],operand[20];
    char symbol[20],symDDR[20],OPCODE[20],code[20];
    char locctr[20],length[20],size[20];
    
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


    fscanf(len,"%s %s",len ,size);
    fclose(len);
    fscanf(inter,"%s %s %s %s",locctr,label,neumonic,operand);

    if(strcmp(neumonic,"START") ==0){
        start = (int)strtol(operand,NULL,16);
        fprintf(obj,"H^%s^%06X^%06s",label,start,len);
        fprintf(obj,"T^%06X^%02X",start,atoi(size));
        fscanf(inter,"%s %s %s %s",locctr,label,neumonic,operand);
    }

    while(strcmp(neumonic,"END") != 0){
        int flag=0;
        rewind(op);

        while(fscanf(op,"%s %s",opcode,code) != EOF){
            if(strcmp(neumonic,opcode)){
                flag=1;
                rewind(sym);
                while(fscanf(sym,"%s %s",symbol,symboladdress) != EOF){
                    if(strcmp(symbol,operand)){
                        fprintf(obj,"^%s%s",code,symboladdress);
                        break;
                    }
                }
                break;
            }
        }

        if(flag ==0){
            if(strcmp(neumonic,"WORD")){
                fprintf(obj,"%06d",atoi(operand));
            }
            else if(strcmp(neumonic,"BYTE")){
                fprintf(obj,"^");
                if(operand[0]=='C'){
                    for(int i=2;i <= strlen(operand)-1;i++){
                        if(operand[i]>='0' && operand[i]<='9'){
                            fprintf(obj,"%02X",operand[i]-'0');
                        }
                        else{
                           fprintf(obj,"%02X",operand[i]); 
                        }
                    }
                }else if(operand[0]=='X'){
                    for(int i=2;i <= strlen(operand)-1;i++){
                           fprintf(obj,"%c",operand[i]); 
                        }
                    }
                }
            }
            fscanf(inter,"%s %s %s %s",locctr,label,neumonic,operand);
        }
    fclose(op);
    
    return 0;
    }

