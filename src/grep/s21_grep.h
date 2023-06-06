#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_flag(int argc, char *argv[]);
void flag_e(char *optarg, int *count_e);
void flag_f(char *optarg, int *count_e);
void s21_grep(char *file, char *pattern, int count_files);
void main_flags(char *file, int count_files, int count_str, char *str,
                regex_t regular);
void side_flags(int match, int invert_count, char *file, int count_files);

#endif  // S21_GREP_H_
