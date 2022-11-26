#ifndef _SRC_CAT_S21_CAT
#define _SRC_CAT_S21_CAT

#include <getopt.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_v;
  int flag_E;
  int flag_T;
} flags;

void final_et(flags *flags, char *symb);
void cat(int argc, char **argv, flags *flags);
void get_flags(int argc, char **argv, flags *flags);
void get_files(int argc, char **argv, flags *flags);
void out(FILE *file, flags *flags);

#endif