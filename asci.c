#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) { //создает файл наполненый невидимыми символами для проверки флагов e, t, v Cat
    FILE *fp;
    fp = fopen(argv[1], "w");
    for(int i = 0; i < 128; i++) {
        fprintf(fp, "%c  \n", i);
    }
    fclose(fp);
    return 0;
}
