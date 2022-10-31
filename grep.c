#include<stdio.h>
#include <string.h>
#include <stdlib.h>

void grep_out (char fraze[], char file_name[]);
void finder (char fraze[], FILE *file);

int main(int argc, char* argv[]) {
    grep_out(argv[1],argv[2]);
}

void grep_out(char fraze[], char file_name[]){
    FILE *file;
    file = fopen(file_name, "r");
    finder(fraze,file);
}
void finder (char fraze[], FILE *file){
    int end = 1;
    char output[100];
    while (end == 1){
        fgets(output, 100, file);
        if (output[0] == '\0')
            end = 0;
        if (strstr(output, fraze)!=NULL)
            printf("%s",output);
        memset(output, 0, sizeof(char));
    }
}