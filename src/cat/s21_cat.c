#include "s21_cat.h"

struct flag {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int err;
} flags;

const struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                      {"number", 0, NULL, 'n'},
                                      {"squeeze-blank", 0, NULL, 's'},
                                      {NULL, 0, NULL, 0}};

int main(int argc, char *argv[]) {
  if (argc == 1) {
    cat_no_arg();
  } else if (argc == 2) {
    argv++;
    cat_arg(argv);
  } else {
    find_flag(argc, argv);
    if (flags.err == 1) {
      return 1;
    } else {
      while (optind < argc) {
        cat_arg(&argv[optind]);
        optind++;
      }
    }
  }
  return 0;
}

void cat_no_arg() {
  int input = STDIN_FILENO;
  char list[4096];
  int size_input;
  size_input = read(input, list, 4096);
  while (input != -1) {
    printf("%.*s", size_input, list);
    size_input = read(input, list, 4096);
  }
}

void find_flag(int argc, char *argv[]) {
  int fl = 0;
  while ((fl = getopt_long(argc, argv, "+beEnstTv?", long_options, NULL)) !=
         -1) {
    switch (fl) {
      case 'b':
        flags.b = 1;
        break;
      case 'e':
        flags.e = 1;
        flags.v = 1;
        break;
      case 'E':
        flags.e = 1;
        break;
      case 'n':
        flags.n = 1;
        break;
      case 's':
        flags.s = 1;
        break;
      case 't':
        flags.t = 1;
        flags.v = 1;
        break;
      case 'T':
        flags.t = 1;
        break;
      case 'v':
        flags.v = 1;
        break;
      case '?':
        flags.err = 1;
        break;
    }
  }
}

void cat_arg(char *argv[]) {
  FILE *fp = NULL;
  fp = fopen(*argv, "r");
  if (fp == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", *argv);
  } else {
    int count = 1;
    int empty = 0;
    char ch = ' ';
    char last = '\n';
    while ((ch = fgetc(fp)) != EOF) {
      if (flags.s && ch == '\n' && last == '\n') {
        if (empty) {
          continue;
        }
        empty++;
      } else {
        empty = 0;
      }
      if (flags.b && last == '\n' && ch != '\n') {
        printf("%6d\t", count);
        count++;
      }
      if (flags.n && !flags.b && last == '\n') {
        printf("%6d\t", count);
        count++;
      }
      if (flags.t && ch == '\t') {
        printf("^");
        ch = 'I';
      }
      if (flags.e && ch == '\n') {
        printf("$");
      }
      if (flags.v) {
        if ((ch >= 0 && ch <= 31) && ch != '\t' && ch != '\n') {
          printf("^");
          ch = ch + 64;
        } else if (ch == 127) {
          printf("^");
          ch = ch - 64;
        }
      }
      printf("%c", ch);
      last = ch;
    }
  }
  fclose(fp);
}
