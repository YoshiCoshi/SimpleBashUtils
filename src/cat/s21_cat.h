#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void cat_no_arg();
void find_flag(int argc, char *argv[]);
void cat_arg(char *argv[]);

#endif  // S21_CAT_H_