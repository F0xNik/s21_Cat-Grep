#include "./s21_grep.h"

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "To few arguments\n");
  } else {
    char Buff_paterns[BUFFSIZE] = {0};
    flags flags = {0};
    get_flags(argc, argv, &flags, Buff_paterns);
    if (flags.count_for_stick == 0) {
      word_to_patern(argv, Buff_paterns);
    }
    output(argc, argv, &flags, Buff_paterns);
  }
  return 0;
}

void get_flags(int argc, char *argv[], flags *flags, char *Buff_paterns) {
  const char *get_opt_flags = "e:f:ivclnhso";
  int ch = 0;
  while ((ch = getopt_long(argc, argv, get_opt_flags, NULL, NULL)) != -1) {
    switch (ch) {
      case 'i':
        flags->flag_i++;
        break;
      case 'v':
        flags->flag_v++;
        break;
      case 'c':
        flags->flag_c++;
        break;
      case 'l':
        flags->flag_l++;
        break;
      case 'n':
        flags->flag_n++;
        break;
      case 'h':
        flags->flag_h++;
        break;
      case 's':
        flags->flag_s++;
        break;
      case 'o':
        flags->flag_o++;
        break;
      case 'e':
        flags->flag_e++;
        E_plus_patern(Buff_paterns, flags);
        flags->count_for_stick++;
        break;
      case 'f':
        flags->flag_f++;
        F_plus_patern(Buff_paterns, flags);
        flags->count_for_stick++;
        break;
      default:
        break;
    }
  }
}

void E_plus_patern(char *Buff_paterns, flags *flags) {
  if (flags->count_for_stick) {
    strcat(Buff_paterns, "|");
  }
  strcat(Buff_paterns, optarg);
}

void F_plus_patern(char *Buff_paterns, flags *flags) {
  FILE *file;
  if ((file = fopen(optarg, "r")) == NULL) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", optarg);
    exit(1);
  } else {
    char StrPat_file[BUFFSIZE] = {0};
    while ((fgets(StrPat_file, BUFFSIZE, file)) != NULL) {
      if (StrPat_file[0] == '\n') {
        if (flags->count_for_stick != 0) strcat(Buff_paterns, "|");
        strcat(Buff_paterns, "\n");
      }
      if (flags->count_for_stick != 0 && StrPat_file[0] != '\n') {
        strcat(Buff_paterns, "|");
      }
      if (strlen(StrPat_file) > 0 &&
          StrPat_file[strlen(StrPat_file) - 1] == '\n')
        StrPat_file[strlen(StrPat_file) - 1] = '\0';
      strcat(Buff_paterns, StrPat_file);
      flags->count_for_stick++;
    }
    fclose(file);
  }
}

void word_to_patern(char **argv, char *Buff_paterns) {
  strcat(Buff_paterns, argv[optind]);
  optind++;
}

void output(int argc, char **argv, flags *flags, char *Buff_paterns) {
  int I_flags = REG_EXTENDED;
  if (flags->flag_i != 0) I_flags = REG_ICASE;
  int Eror_REG = regcomp(&reg_comp, Buff_paterns, I_flags);
  if (Eror_REG != 0) {
    fprintf(stderr, "incorrect regular expresion");
    exit(5);
  } else {
    int count_file = argc - optind;
    for (; optind < argc; optind++) {
      FILE *file;
      if ((file = fopen(argv[optind], "r")) == NULL) {
        if (flags->flag_s == 0) {
          fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                  argv[optind]);
        }
      } else {
        // int status = 0;
        char str[BUFFSIZE] = {0};
        int count_matched_str = 0;
        int str_num = 0;
        int last_matched_str = 0;
        const size_t nmatch = 1;
        while ((fgets(str, BUFFSIZE, file)) != NULL) {
          if (flags->flag_v != 0 && flags->flag_o != 0) {
            if (flags->flag_c != 0 || flags->flag_l != 0)
              flags->flag_o = 0;
            else
              break;
          }
          str_num++;
          int status = regexec(&reg_comp, str, nmatch, struct_reg, 0);
          if (flags->flag_c == 0 && flags->flag_l == 0) {
            if (flags->flag_o == 0)
              O_Out(str, flags, status, count_file, argv[optind],
                    &count_matched_str, str_num, &last_matched_str);
            else {
              char *copy_str = str;
              while ((status == 0 && flags->flag_v == 0) ||
                     (status == REG_NOMATCH && flags->flag_v != 0)) {
                O_Out(copy_str, flags, status, count_file, argv[optind],
                      &count_matched_str, str_num, &last_matched_str);
                for (int i = struct_reg[0].rm_so; i < struct_reg[0].rm_eo;
                     i++) {
                  putchar(copy_str[i]);
                }
                printf("\n");
                copy_str = copy_str + struct_reg[0].rm_eo;
                status = regexec(&reg_comp, copy_str, nmatch, struct_reg, 0);
              }
            }
          } else {
            if ((status == 0 && flags->flag_v == 0) ||
                (status != 0 && flags->flag_v != 0))
              count_matched_str++;
          }
        }
        if (flags->flag_c != 0) {
          if (count_file > 1 && flags->flag_h == 0) printf("%s:", argv[optind]);
          if (flags->flag_l != 0) {
            if (count_matched_str != 0)
              printf("1\n");
            else
              printf("0\n");
          } else
            printf("%d\n", count_matched_str);
        }
        if (flags->flag_l != 0) {
          if (count_matched_str != 0) printf("%s\n", argv[optind]);
        }
        if (last_matched_str == str_num &&
            (flags->flag_c == 0 || flags->flag_l == 0) &&
            str[strlen(str) - 1] != '\n')
          printf("\n");
      }
      if (file != NULL) fclose(file);
    }
  }
  regfree(&reg_comp);
}

void O_Out(char *str, flags *flags, int status, int count_file, char *file_name,
           int *count_matched_str, int str_num, int *last_matched_str) {
  if ((status == 0 && flags->flag_v == 0) ||
      (status == REG_NOMATCH && flags->flag_v != 0)) {
    *count_matched_str = +1;
    if (count_file > 1 && flags->flag_h == 0) printf("%s:", file_name);
    if (flags->flag_n != 0) printf("%d:", str_num);
    if (flags->flag_o == 0) {
      printf("%s", str);
      *last_matched_str = str_num;
    }
  }
}
