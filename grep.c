#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<regex.h>

struct flags {
    int flag_e;
    int flag_i;
    int flag_v;
    int flag_c;
    int flag_l;
    int flag_n;
    int flag_h;
    int flag_s;
    int flag_f;
    int flag_o;
};

regex_t re;
regmatch_t pmatch[2];

//void parser_file(int argc, char* argv[],struct flags* flag);
void find_patern_if_e(char fl_str[],char pattern[]);
void parser(int argc, char* argv[],struct flags* flag);
void Unpacker(char Buffer[], char Buffer_file[], struct flags* flag);
void func_flag(char *arrFlags, struct flags *flag);
void File_out(char Buffer[], char File_name[], struct flags* flag, int sum_file);
void flag_f_out (char Buffer[], char File_name[], struct flags* flag);

int main(int argc, char* argv[]){
    struct flags flag;
    flag.flag_e = 0;
    flag.flag_i = 0;
    flag.flag_v = 0;
    flag.flag_c = 0;
    flag.flag_l = 0;
    flag.flag_n = 0;
    flag.flag_h = 0;
    flag.flag_s = 0;
    flag.flag_f = 0;
    flag.flag_o = 0;
    char pattern[100];
    parser(argc, argv, &flag);
    return 0;
}

// void parser_file(int argc, char* argv[],struct flags* flag){
//     int iter_flag = 0;
//     int iter_fraze = 0;
//         for (int i = 0; i < argc; i++){
//             if (argv[i][0] == '-'){
//                 iter_flag = i;
//                 func_flag(argv[iter_flag],flag);
//             }
//         }
//         for (int i = 1; i < argc; i++){
//             if(i != iter_flag && argv[i][0]!='-'){
//                iter_fraze = i;
//                 break;
//             }
//         }
//         for(int i = 1; i < argc; i++){
//             if(i != iter_flag && i != iter_fraze && argv[i][0]!='-'){
//                    Unpacker(argv[iter_fraze],argv[i],flag);
//             }
//         }
// }

void parser(int argc, char* argv[], struct flags* flag){
    char Buffer[250]="";
    char Buffer_file[250]="";
    char Buffer_flag[50]="";
    char patern[100]="";
    int k=0;
    int i = 0;
    int count_flag = 0;
    int count_patern = 0;
    int count_for_stick = 0;
    int switch_buf = 0;
        for(i = 1; i<argc;i++){
            //printf("!!!!%s!!!\n",argv[i]);
        if (argv[i][0]=='-'){
            switch_buf = 0;
            for (k=0;argv[i][k]!='\0'&&argv[i][k]!='\0';k++){
                Buffer_flag[count_flag] = argv[i][k];
                count_flag++;
                if (argv[i][k]=='e')
                    break;
            }
            func_flag(Buffer_flag,flag);
            //printf("\n!!(%c)(%c)!!\n",argv[i][k+1],argv[i][k]);
            if(argv[i][k+1]!='\0' && argv[i][k]=='e'){
                switch_buf = 1;
                for(int j = k+1; argv[i][j]!='\0'&&argv[i][j]!=' ';j++){
                    patern[count_patern]=argv[i][j];
                    count_patern++;
                }
                count_patern++;
            }
            else{
                //printf("ALOHAAAA%s",argv[i+1]);
                switch_buf=1;
                i++;
                if(count_for_stick>0)
                    strcat(Buffer,"|");
                strcat(Buffer,argv[i]);
                count_for_stick++;
                //printf("ALOHAAAA%s",argv[i+1]);
            }
        }
        else {
            if (switch_buf==0){
                switch_buf = 1;
            if(count_for_stick>0)
                    strcat(Buffer,"|");
                strcat(Buffer,argv[i]);
            }
            else{
                strcat(Buffer_file,argv[i]);
                strcat(Buffer_file," ");
            }
        }
        if (count_patern > 0){
            if(count_for_stick>0)
                strcat(Buffer,"|");
            strcat(Buffer,patern);
        count_patern = 0;
        count_for_stick++;
        memset(patern, '\0', sizeof(char));
    }
    }
    Unpacker(Buffer,Buffer_file,flag);
}
                                    // printf("pattern - %s\npath - %s\n", Buffer, Buffer_file);
                                    // printf("FLAGS: e - %d, i - %d, v - %d, c - %d, l - %d, n - %d, h - %d, s - %d, f - %d, o - %d...",
                                     // flag->flag_e, flag->flag_i, flag->flag_v, flag->flag_c, flag->flag_l, flag->flag_n,
                                    // flag->flag_h, flag->flag_s, flag->flag_f,flag->flag_o);

void Unpacker(char Buffer[], char Buffer_file[], struct flags* flag){
    //printf("pattern - %s\npath - (%s)\n\n\n", Buffer, Buffer_file);
    char file[50]="";
    int count_buf = 0, count_file = 0;
    int sum_file = 0; //kount_file=0;
    while (Buffer_file[count_buf]!='\0'){
       if(Buffer_file[count_buf]==' ')
            sum_file++;
        count_buf++;
    }
    count_buf = 0;
    if (flag->flag_f==1){
        flag_f_out(Buffer, Buffer_file, flag);
    }
    // else if (flag->flag_e==1){

    // }
    else{
        while (Buffer_file[count_buf]!='\0'){
            while (Buffer_file[count_buf]!=' '&&Buffer_file[count_buf]!='\0'){
                file[count_file] = Buffer_file[count_buf];
                count_file++;
                count_buf++;
            }
            //printf("(%d),(%d))\n",kount_file,sum_file);
            //kount_file++;
            File_out(Buffer,file,flag,sum_file);
            // if (kount_file==sum_file)
            //     printf("\n");

            //  printf("FLAGS: e - %d, i - %d, v - %d, c - %d, l - %d, n - %d, h - %d, s - %d, f - %d, o - %d...",
            //                           flag->flag_e, flag->flag_i, flag->flag_v, flag->flag_c, flag->flag_l, flag->flag_n,
            //                          flag->flag_h, flag->flag_s, flag->flag_f,flag->flag_o);
            if(Buffer_file[count_buf]!='\0')
                count_buf++;
            memset(file,0,strlen(file));
            
            count_file = 0;
        }
    }
}

void flag_f_out (char Buffer[], char File_name[], struct flags* flag){

}

void File_out(char Buffer[], char File_name[], struct flags* flag, int sum_file){
    //printf("pattern - %s\npath - %s\n\n\n", Buffer, File_name);
    FILE *file;
    char line_file[100]="";
    int res;
    int cflags = REG_EXTENDED + REG_NEWLINE;
    int SUM_flag_c = 0;
    int Number_line = 0;
    int check_flag_l=0;
    if (flag->flag_i==1)
        cflags=+ REG_ICASE;
    file = fopen(File_name,"r");
    if(file != NULL) {
        regcomp(&re, Buffer, cflags);
        while(!feof(file)) {
            fgets(line_file, 250, file);
            //printf("kf%d-sf%d",kount_file,sum_file);
            // if (kount_file==sum_file&&line_file[0] != '\n'){
            //     //strcat(line_file,"\n");
            //     printf("\n");
            // }
            Number_line++;
            res = regexec(&re, line_file, 250, pmatch, 0);
                if((res == 0 && flag->flag_v == 0) || (res != 0 && flag->flag_v == 1)){
                    SUM_flag_c++;
                    check_flag_l = 1;
                    if (flag->flag_l == 0 && flag->flag_c==0){
                        //printf("!%d!",sum_file);
                        if (sum_file<2||flag->flag_h==1){
                            if (flag->flag_n==1){
                                printf("%d:",Number_line);
                            }
                            printf("%s", line_file);
                        }
                        else{
                            if (flag->flag_n==1){
                                printf("%s:%d:%s\n",File_name,Number_line,line_file);
                            }
                            else {
                                printf("%s:%s",File_name,line_file);
                            }
                        }
                    }
                    if (feof(file))
                        printf("\n");
                }
                //else {
                //}
        }
        if (flag->flag_c==1&&flag->flag_l==0)
            printf("%s:%d\n", File_name, SUM_flag_c);
        if (flag->flag_l==1&&check_flag_l==1 && flag->flag_c==0)
            printf("%s",File_name);
        if (flag->flag_l==1&&check_flag_l==1 && flag->flag_c==1)
            printf("%s:1\n%s",File_name,File_name);
        // if (flag->flag_c==1)
        //     printf("%s:%d\n", File_name, SUM_flag_c);
        // if (flag -> flag_c == 1)
        //     printf("%d",SUM_flag_c);
        // if (feof(file))
        //     printf("\n");
    }
    else {
        if (flag->flag_s==0)
            printf("grep: %s: No such file or directory\n",file);
    }
}

void func_flag(char *arrFlags, struct flags* flag) {
    int checker = 0;
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
                case 'h':
                    flag->flag_h = 1;
                    break;
                case 's':
                    flag->flag_s = 1;
                    break;
                case 'f':
                    flag->flag_f = 1;
                    break;
                case 'o':
                    flag->flag_o = 1;
                    break;
            }
        }
    }
}
