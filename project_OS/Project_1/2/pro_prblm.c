#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    char srcfileName[20];
    char outfileName[20];
    
    char letter;
    
    FILE *srcStream;
    FILE *outStream;
    
    printf("Please enter name of SOURCE file: ");
    scanf("%s", srcfileName);

    printf("\nPlease enter name of OUTPUT file: ");
    
    scanf("%s", outfileName);


    printf("\n*** Attemping to open & read from sourc file ***\n");

    srcStream = fopen(srcfileName, "r");
    
    if (!srcStream) {
        perror("File failed to open, file may not exist\n");
        exit(1);
    }

    printf("*** Attempting to write to output file ***\n");
    outStream = fopen(outfileName, "w");

    if (!outStream) {
        perror("File failed to open, file may not exist\n");
        exit(1);
    }
    
    while (!feof(srcStream)) {
        letter = fgetc(srcStream);
        fputc(letter, outStream);
    }
    
    printf("*** closing files ***\n");
    
    fclose(srcStream);
    fclose(outStream);
    
    printf("succesfully copied and transfered data from %s to %s\n", srcfileName, outfileName);
    
    return 0;
}