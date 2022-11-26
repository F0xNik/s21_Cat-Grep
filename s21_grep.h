#ifndef SRC_GREP_S21_GREP_H
#define SRC_GREP_S21_GREP_H

#include <getopt.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<regex.h>

#define BUFFSIZE 2000

regex_t reg_comp;
regmatch_t struct_reg[1] = {0};

typedef struct flags {
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
    int count_for_stick;
} flags;

void get_flags(int argc, char* argv[], flags *flags, char* Buff_paterns);
void E_plus_patern(char* Buff_paterns, flags *flags);
void F_plus_patern(char* Buff_paterns, flags *flags);
void word_to_patern(char** argv, char* Buff_paterns);
void output(int argc, char **argv, flags * flags, char* Buff_paterns);
void O_Out ( char* str, flags *flags, int status, int count_file,
                        char * file_name, int *count_matched_str, int str_num, int* last_matched_str);


#endif