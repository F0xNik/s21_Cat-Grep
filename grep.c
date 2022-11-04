#include<stdio.h>
#include<string.h>
#include<getopt.h>
#include <stdlib.h>
struct flags {
    int flag_e;
    int flag_i;
    int flag_v;
    int flag_c;
    int flag_l;
    int flag_n;
};

void parser_flags(int argc, char* argv[], struct flags* flag);
void parser_file(int argc, char* argv[],struct flags* flag);
void find_patern_if_e(char fl_str[],char pattern[]);
void parser_with_e(int argc, char* argv[],struct flags* flag);
void func_out_e(char Buffer[], char Buffer_file[], struct flags* flag);
void func_flag(char *arrFlags, struct flags *flag);
void func_flag_e(char *arrFlags, struct flags* flag);

int main(int argc, char* argv[]){
    struct flags flag;
    flag.flag_e = 0;
    flag.flag_i = 0;
    flag.flag_v = 0;
    flag.flag_c = 0;
    flag.flag_l = 0;
    flag.flag_n = 0;
    char pattern[100];

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] == '-') {
            for(int z = 1; z < strlen(argv[i]); z++) {
                if(argv[i][z] == 'e')
                    flag.flag_e = 1;
            }
        }
    }
    if(flag.flag_e == 1) {
        parser_with_e(argc, argv, &flag);
    } else {
        parser_file(argc, argv, &flag);
    }
    //parser_with_e(argc,argv,flag);
    //parser_file(argc,argv,&flag);
    //parser_file(argc,argv,&flag);
    //find_patern_if_e(argv[1],pattern);
    //printf("%s\n", pattern);
    return 0;
}
void function_out(char fraze[], char path[], struct flags* flag){
    printf("pattern - %s\npath - %s\nflag - i %d, c %d, l %d", fraze, path, flag->flag_i, flag->flag_c, flag->flag_l);
}
void parser_file(int argc, char* argv[],struct flags* flag){
    int iter_flag = 0;
    int iter_fraze = 0;
    // if(flag->flag_e == 1){
    //    parser_with_e(argc,argv,flag);
    // }
    // else {
        for (int i = 0; i < argc; i++){
            //printf("%s",argv[i]);
            if (argv[i][0] == '-'){
                iter_flag = i;
                func_flag(argv[iter_flag],flag);
            }
        }
        for (int i = 1; i < argc; i++){
            if(i != iter_flag && argv[i][0]!='-'){
               iter_fraze = i;
                break;
            }
        }
        for(int i = 1; i < argc; i++){
            if(i != iter_flag && i != iter_fraze && argv[i][0]!='-'){
                    function_out(argv[iter_fraze],argv[i],flag);
            }
        }
    //}
}

void parser_with_e(int argc, char* argv[], struct flags* flag){
    char Buffer[250]="";
    char Buffer_file[250]="";
    char Buffer_flag[50]="";
    char patern[100]="";
    int k=0;
    int i = 0;
    //int eror = 1;
    int count_flag = 0;
    int count_patern = 0;
    for(i = 1; i<argc;i++){
        if (argv[i][0]=='-'){
            for (k=0;argv[i][k]!='e'&&argv[i][k]!='\0';k++){
                Buffer_flag[count_flag] = argv[i][k];
                count_flag++;
                //if (argv[i][k]=='e')
                    //eror = 0;
            }
            func_flag_e(Buffer_flag,flag);
            //if (eror == 1){
            //printf("%c",argv[i][k]);
            if(argv[i][k+1]!='\0'){
                //printf("fdgdfgdfgdfgdfgdfg");
                for(int j = k+1; argv[i][j]!='\0';j++){
                    patern[count_patern]=argv[i][j];
                    count_patern++;
                }
                patern[count_patern]=' ';
                count_patern++;
                //strcat(Buffer,patern);
                //strcat(Buffer," ");
                //memset(patern, 0, sizeof(char));
                //k=0;
            }
            else{
                //printf("dfsdfsdfsdfsdf");
                i++;
                //printf("\n%s\n",argv[i]);
                strcat(Buffer,argv[i]);
                strcat(Buffer," ");
                //printf("\n%s",Buffer);
            }
            //eror = 0;
            //}
        }
        else {
            strcat(Buffer_file,argv[i]);
                strcat(Buffer_file," ");
        }
        
    }
    strcat(Buffer,patern);
    func_out_e(Buffer,Buffer_file,flag);
    //printf("bufer patern - %s\n",Buffer);
    //printf("bufer file - %s",Buffer_file);
}
void func_out_e(char Buffer[], char Buffer_file[], struct flags* flag){
    printf("PAttern - %s\npath - %s\nflag - i %d, c %d, l %d", Buffer, Buffer_file, flag->flag_i, flag->flag_c, flag->flag_l);
}
// void parser_flags(int argc, char* argv[], struct flags* flag){
//     for(int i = 0; argv[i] != '\0'; i++) {

//     }
// }
// void function_out(char* fraze, char* path, struct flags* flag){

// }
void func_flag(char *arrFlags, struct flags* flag) {
    // if(strchr(arrFlags, 'e') != NULL)
    //     flag->flag_e = 1;
    //printf("dsfsdf");
    int checker = 0;
    if(strchr(arrFlags, 'i') != NULL)
        flag->flag_i = 1;
    if(strchr(arrFlags, 'v') != NULL)
        flag->flag_v = 1;
    if(strchr(arrFlags, 'c') != NULL) {
        checker = 1;
        flag->flag_c = 1;
    }
    if(strchr(arrFlags, 'l') != NULL)
        flag->flag_l = 1;
    if(strchr(arrFlags, 'n') != NULL)
        flag->flag_n = 1;
}
void func_flag_e(char *arrFlags, struct flags* flag){
    for (int i = 0; i< strlen(arrFlags); i++){
        if (arrFlags[i]=='e'){
            break;
        }
        else {
            switch (arrFlags[i]){
                case 'i':
                    flag->flag_i = 1;
                    break;
                case 'v':
                    flag->flag_v = 1;
                    break;
                case 'c':
                    flag->flag_c = 1;
                    break;
                case 'l':
                    flag->flag_l = 1;
                    break;
                case 'n':
                    flag->flag_n = 1;
                    break;
            }
        }
    }
}