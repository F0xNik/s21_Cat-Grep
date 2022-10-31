#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cat(char input[100]);
void output_file(FILE *file, int flag);
int func_choice (char input[100]);
int check_count_file (char input[100], int k_str);
int flag_check(char input[100], int k_str);
int GNU_flag_check(char input[100]);

int main(int argc, char* argv[]) {
    char input[100];
    for(int i = 1; i < argc; i++){
        strcat(input, argv[i]);
        strcat(input, " ");
    }
    //printf("%s",input);
    if (argc < 2)
        fgets(input,100,stdin);
    do {
        if (func_choice(input) == 2) {
            printf("Unknown function\n");
            fseek(stdin,0,SEEK_END);
            scanf("%s", input);
        }
        if (func_choice(input) == 1) {
            cat(input);
        }
    } while (func_choice(input) != 1);
}

int func_choice (char input[100]) {
    int result = 2;
    if (input[0] == 'c' && input[1]=='a' && input[2]=='t')
        result = 1;
    return result;
}

void output_file(FILE *file, int flag) {
    char output[250];
    int schet = 1;
    int end = 1;
    int flag_out = flag;
    int i = 0;
    int fl_b = 0, fl_E = 0, fl_n = 0, fl_s = 0, fl_T = 0, fl_e = 0, fl_t = 0;
        switch (flag_out)
        {
        case 1:
            fl_b = 1;
            break;
        case 2:
            fl_E = 1;
            break;
        case 3:
            fl_n = 1;
            break;
        case 4:
            fl_s = 1;
            break;
        case 5:
            fl_T = 1;
            break;
        case 6:
            fl_e = 1;
            break;
        case 7:
            fl_t = 1;
            break;
        }
    int ch = 0;
    ch = 0;
    int first_empty = 0;
    int j = 0;
    while (end == 1) {
            fgets(output, 250, file); 
            first_empty++;
            if (output[0] == '\0'){//||(int)output[0]==1) {
                end = 0; 
                if (first_empty == 1)
                    ch = 1;
            }
            else {
                if (fl_b == 1 && output[0] != '\n' && output[0] != '\0') {
                    printf("%6d  ",schet);
                    schet++;
                }
                if (fl_n == 1 && output[0] != '\0') {
                    if (!(fl_s == 1 && output[0]=='\n')){
                        printf("%d ",schet);
                    }
                    schet++;
                }
                if(fl_E == 1 || fl_e == 1) {
                    i = 0;
                    while (output[i]!= '\0' && output[i]!='\n') {
                        i++;
                    }
                    if (output[i]=='\n'){
                        output[i] = '\0';
                        strcat(output,"$\n");
                    }
                    else {
                        strcat(output,"$");
                    }
                }
                char sav_simb, sav_simb2;
                if (fl_T == 1 || fl_t == 1) {
                    i=0;
                    while(output[i] != '\0' && output[i] != '\n'){
                        if ((int)output[i] == 9) {
                            output[i]='^';
                            sav_simb = output[i+1];
                            output[i+1] = 'I';
                            i++;
                            j=i+1;
                            while(output[j] != '\0' && output[j] != '\n'){
                                sav_simb2 = output[j];
                                output[j]=sav_simb;
                                sav_simb = sav_simb2;
                                j++;
                            }
                            output[j+1]=output[j];
                            output[j]=sav_simb2;
                        }
                        i++;
                    }
                }
                if (fl_e == 1|| fl_t == 1){
                    //printf("4453");
                    for (int y = 0;output[y]!='\0'; y++){
                        if (output[y]>=0&&output[y]<32&&output[y]!=127&&output[y]!=10){
                            printf("^");
                            printf("%c",output[y]+64);
                        }
                        else if(output[y]==127){
                            printf("^");
                            printf("%c",63);
                        }
                        else{
                            printf("%c",output[y]);
                        }
                    }
                }
                if (end == 1) {
                    if (!(fl_s == 1 && output[0]=='\n')&& fl_e != 1 &&fl_t != 1 )
                        printf("%s",output);
                }
            }
            memset(output, 0, sizeof(char));
    }
    if (ch == 0)
        printf("\n");
}

int check_count_file (char input[100], int k_str) {
    int count = 0;
    k_str--;
    while ( input[k_str] != '\0') {
        if (input[k_str] == ' ')
            count++;
        if (input[k_str] != ' ' && (input[k_str+1] == ' ' || input[k_str+1] == '\0' || input[k_str+1] == '\n'))
            count++;
        k_str++;
    }
    return count / 2;
}
int flag_check(char input[100], int k_str) {
    int int_flag;
    switch (input[k_str])
    {
    case 'b':
        int_flag = 1;
        break;
    case 'E':
        int_flag = 2;
        break;
    case 'n':
        int_flag = 3;
        break;
    case 's':
        int_flag = 4;
        break;
    case 'T':
        int_flag = 5;
        break;
    case 'e':
        int_flag = 6;
        break;
    case 't':
        int_flag = 7;
        break;
    case '-':
        int_flag = GNU_flag_check(input);
        break;
    default:
        int_flag = -1;
        break;
    }
    return int_flag;
}

int GNU_flag_check(char input[100]){
    int k_clone_str = 6;
    char Gnu_vers_flag[30] = "number-nonblank";
    char Gnu_flag_n[10] = "number";
    char Gnu_flag_s[20] = "squeeze-blank";
    int Gnu_b = 1, Gnu_n = 1, Gnu_s = 1;
    int Gnu_flag = -1;
    int iterat = 0; 
    while(Gnu_vers_flag[iterat] != '\0'){
        if (Gnu_vers_flag[iterat]!=input[k_clone_str])
            Gnu_b = 0;
        k_clone_str++;
        iterat++;
    }
    iterat = 0;
    k_clone_str = 6;
    while(Gnu_flag_n[iterat] != '\0'){
        if (Gnu_flag_n[iterat]!=input[k_clone_str]){
            Gnu_n = 0;
        }
        k_clone_str++;
        iterat++;
    }
    if (input[k_clone_str]!=' ')
        Gnu_n = 0;
    iterat = 0;
    k_clone_str = 6;
    while(Gnu_flag_s[iterat] != '\0'){
        if (Gnu_flag_s[iterat]!=input[k_clone_str])
            Gnu_s = 0;
        k_clone_str++;
        iterat++;
    }
    if (Gnu_b == 1)
        Gnu_flag = 1;
    if(Gnu_n == 1)
        Gnu_flag = 3;
    if(Gnu_s == 1)
        Gnu_flag = 4;
    return Gnu_flag;
}

void cat(char input[100]) {
    char path[20];
    int kount_str = 4;
    int clon_count_file = 0;
    int letter = 0;
    int flag = 0;
    int i = 0;
    int eror = 0;
    FILE *file;
        if (input[kount_str]=='-') {
            if (flag_check(input, kount_str+1) == -1 && input[kount_str+1]!='-') {
               printf("Unknown flag\n");
               eror = 1;
            }
            else {
                flag = flag_check(input, kount_str+1);
                 while(input[kount_str] != ' '){
                 kount_str++;
                }
                kount_str++;
            }
        }
    clon_count_file = check_count_file(input, kount_str);
    if (eror == 1) {
        clon_count_file = 0;
    }
    for (i = 0; i < clon_count_file; i++) {
        while(input[kount_str]!='\n' && input[kount_str] != ' '&& input[kount_str]!='\0') {
            path[letter] = input[kount_str];
            letter++;
            kount_str++;
        }
        kount_str++;
        path[letter]='\0';
        letter = 0;
        file = fopen(path, "r");
        if (file == NULL) {
            printf("Eror with file number %d(%s)\n",i+1,path);
        }
        else {
            output_file(file, flag);
        }
        fclose(file);
    }
}