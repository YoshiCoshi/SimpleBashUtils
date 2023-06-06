#include "s21_grep.h"

struct flag {
  int e_pattern;
  int i_ignor_reg;
  int v_invert_search;
  int c_count_str;
  int l_print_match_files;
  int n_number_str;
  int h_print_match_str;
  int s_no_error;
  int f_file_pattern;
  int o_match_part_str;
  char pattern[1024];
} flags;

int main(int argc, char *argv[]) {
  if (argc >= 3) {
    flags.pattern[0] = '\0';
    find_flag(argc, argv);
    if (!flags.e_pattern && !flags.f_file_pattern) {
      if (*argv[optind] == 0) {
        argv[optind] = ".";
      }
      strcat(flags.pattern, argv[optind]);
      optind++;
    }
    int count_files = argc - optind;
    char *pattern = flags.pattern;
    for (int i = optind; i < argc; i++) {
      if (argv[i][0] != '-') {
        char *file = argv[i];
        s21_grep(file, pattern, count_files);
      }
    }
  }
  return 0;
}

void find_flag(int argc, char *argv[]) {
  char symbol;
  int count_e = 0;
  while ((symbol = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (symbol) {
      case 'e':
        flags.e_pattern = 1;
        flag_e(optarg, &count_e);
        break;
      case 'i':
        flags.i_ignor_reg = 1;
        break;
      case 'v':
        flags.v_invert_search = 1;
        break;
      case 'c':
        flags.c_count_str = 1;
        break;
      case 'l':
        flags.l_print_match_files = 1;
        break;
      case 'n':
        flags.n_number_str = 1;
        break;
      case 'h':
        flags.h_print_match_str = 1;
        break;
      case 's':
        flags.s_no_error = 1;
        break;
      case 'f':
        flags.f_file_pattern = 1;
        flag_f(optarg, &count_e);
        break;
      case 'o':
        flags.o_match_part_str = 1;
        break;
    }
  }
}

void flag_e(char *optarg, int *count_e) {
  if (*count_e != 0) {
    strcat(flags.pattern, "|");
  }
  if (*optarg == 0) {
    optarg = ".";
  }
  strcat(flags.pattern, optarg);
  *count_e += 1;
}

void flag_f(char *optarg, int *count_e) {
  FILE *fp = NULL;
  char str[1024] = {0};
  if ((fp = fopen(optarg, "r")) == NULL) {
    printf("grep: %s: No such file or directory\n", optarg);
  } else {
    while (fgets(str, 1024, fp) != NULL) {
      if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = 0;
      }
      if (*count_e > 0) {
        strcat(flags.pattern, "|");
      }
      if (*str == '\0') {
        strcat(flags.pattern, ".");
      } else {
        strcat(flags.pattern, str);
      }
    }
    fclose(fp);
  }
}

void s21_grep(char *file, char *pattern, int count_files) {
  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    if (!flags.s_no_error) {
      fprintf(stderr, "grep: %s: No such file or directory\n", file);
    }
  } else {
    char str[4096];
    int result = 0;
    int count_str = 1;
    int match = 0;
    int invert_count = 0;
    int cflag;
    if (flags.i_ignor_reg) {
      cflag = REG_ICASE;
    } else {
      cflag = REG_EXTENDED;
    }
    regex_t regular;
    regmatch_t pmatch[1];
    regcomp(&regular, pattern, cflag);
    while (fgets(str, 4096, fp)) {
      result = regexec(&regular, str, 1, pmatch, 0);
      if (!strchr(str, '\n')) {
        strcat(str, "\n");
      }
      if (result == 0) {
        match++;
        if (flags.c_count_str || flags.l_print_match_files) {
          continue;
        }
        if (!flags.v_invert_search) {
          main_flags(file, count_files, count_str, str, regular);
        }
      } else if (result != 0 && flags.v_invert_search) {
        invert_count++;
        if (flags.c_count_str || flags.l_print_match_files) {
          continue;
        }
        main_flags(file, count_files, count_str, str, regular);
      }
      count_str++;
    }
    side_flags(match, invert_count, file, count_files);
    regfree(&regular);
  }
  fclose(fp);
}

void main_flags(char *file, int count_files, int count_str, char *str,
                regex_t regular) {
  if (!flags.h_print_match_str && count_files > 1) {
    printf("%s:", file);
  }
  if (flags.n_number_str) {
    printf("%d:", count_str);
  }
  if (flags.o_match_part_str && !flags.v_invert_search) {
    regmatch_t pmatch[1];
    int res = regexec(&regular, str, 1, pmatch, 0);
    char *ptr = str;
    while (res == 0) {
      if (pmatch[0].rm_eo == pmatch[0].rm_so) {
        break;
      }
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             ptr + pmatch[0].rm_so);
      ptr += pmatch[0].rm_eo;
      res = regexec(&regular, ptr, 1, pmatch, 0);
    }
  } else {
    printf("%s", str);
  }
}

void side_flags(int match, int invert_count, char *file, int count_files) {
  int count = 0;
  if (flags.v_invert_search) {
    count = invert_count;
  } else {
    count = match;
  }
  if (flags.l_print_match_files && flags.c_count_str) {
    if (count) {
      count = 1;
    } else {
      count = 0;
    }
    if (!flags.h_print_match_str && count_files > 1) {
      printf("%s:%d\n", file, count);
    } else {
      printf("%d\n", count);
    }
  }
  if (flags.c_count_str && !flags.l_print_match_files) {
    if (!flags.h_print_match_str && count_files > 1) {
      printf("%s:%d\n", file, count);
    } else {
      printf("%d\n", count);
    }
  }
  if (flags.l_print_match_files && count != 0) {
    printf("%s\n", file);
  }
}
