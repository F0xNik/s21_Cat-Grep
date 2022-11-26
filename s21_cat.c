#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Too few arguments");
  } else {
    flags flags = {0};
    cat(argc, argv, &flags);
  }
  return 0;
}

void cat(int argc, char **argv, flags *flags) {
  get_flags(argc, argv, flags);
  get_files(argc, argv, flags);
}

void get_flags(int argc, char **argv, flags *flags) {
  const char *get_opt_flags = "ebnstv";
  const struct option Gnu_flags[] = {
      {"number-nonblank", no_argument, &flags->flag_b, 1},
      {"number", no_argument, &flags->flag_n, 2},
      {"squeeze-blank", no_argument, &flags->flag_s, 3},
      {NULL, 0, NULL, 0}};
  int check = 0;
  while ((check = getopt_long(argc, argv, get_opt_flags, Gnu_flags, NULL)) !=
         -1) {
    switch (check) {
      case 'e':
        flags->flag_e++;
        break;
      case 'b':
        flags->flag_b++;
        break;
      case 'n':
        flags->flag_n++;
        break;
      case 's':
        flags->flag_s++;
        break;
      case 't':
        flags->flag_t++;
        break;
      case 'v':
        flags->flag_v++;
        break;
      case 'E':
        flags->flag_E++;
        break;
      case 'T':
        flags->flag_T++;
        break;
    }
  }
  if (flags->flag_b != 0 && flags->flag_n != 0) flags->flag_n = 0;
  if (flags->flag_E != 0 && flags->flag_v != 0) {
    flags->flag_E = 0;
    flags->flag_v = 0;
    flags->flag_e = 0;
  }
  if (flags->flag_T != 0 && flags->flag_v != 0) {
    flags->flag_T = 0;
    flags->flag_v = 0;
    flags->flag_t = 0;
  }
}

void get_files(int argc, char **argv, flags *flags) {
  for (int ar = 1; ar < argc; ar++) {
    if (argv[ar][0] != '-') {
      FILE *file;
      if ((file = fopen(argv[ar], "r")) == NULL) {
        fprintf(stderr, "cat: %s: No such gile or directory\n", argv[ar]);
      } else
        out(file, flags);
    }
  }
}

void out(FILE *file, flags *flags) {
  char symb;
  int str_count = 1;
  char prev_char = '\0';
  char upper_prev_char = '\0';
  while ((symb = fgetc(file)) != EOF) {
    int out_s = 1;
    if (flags->flag_n != 0) {
      if (str_count == 1) {
        printf("%6d\t", str_count);
        str_count++;
      }
    }
    if (flags->flag_b != 0 && symb != '\n' && str_count == 1) {
      printf("%6d\t", str_count);
      str_count++;
    }
    if (flags->flag_s != 0) {
      if (symb == '\n' && prev_char == '\n' && upper_prev_char == '\n') {
        out_s = 0;
      } else if (str_count == 2 && symb == '\n' && prev_char == '\n')
        out_s = 0;
    }
    if (out_s == 1) {
      if (prev_char == '\n' && flags->flag_n != 0) {
        printf("%6d\t", str_count);
        str_count++;
      }
      if (prev_char == '\n' && symb != '\n' && flags->flag_b != 0) {
        printf("%6d\t", str_count);
        str_count++;
      }
      final_et(flags, &symb);
    }
    upper_prev_char = prev_char;
    prev_char = symb;
  }
}
void final_et(flags *flags, char *symb) {
  if (flags->flag_E != 0 || flags->flag_e != 0 || flags->flag_v != 0 ||
      flags->flag_t != 0 || flags->flag_T != 0) {
    if ((flags->flag_E != 0 || flags->flag_e != 0) && *symb == '\n') {
      printf("$\n");
    } else if ((flags->flag_T != 0 || flags->flag_t != 0) && *symb == '\t')
      printf("^I");
    else if (flags->flag_v != 0 || flags->flag_e != 0 || flags->flag_t != 0) {
      if ((*symb < 33 && *symb != 9 && *symb != 10 && *symb != 13 &&
           *symb != 32 && *symb != '\n') ||
          *symb == 127) {
        if (*symb == 127)
          printf("%c", 63);
        else
          printf("^%c", *symb + 64);
      } else
        printf("%c", *symb);
    }
  } else
    printf("%c", *symb);
}