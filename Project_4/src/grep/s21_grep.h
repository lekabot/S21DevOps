#ifndef s21_grep_h
#define s21_grep_h

#define MY_SIZE 4096

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} opt;
void search_file(FILE *fp, char *pattern, opt *opts, regex_t *compiled);
void parser(int argc, char *argv[], opt *opts, char *pattern);
void search(int argc, char *argv[], opt *opts, char *pattern);
void flags(regex_t compiled, opt *opts, char *str, FILE *fp, int file_count,
           char *filename);
void e_flag(char *pattern, char *str);
void f_flag(char *pattern, char *filename);
void kostbil(opt *opts);
void cl_kostbil(opt *opts, int line, int file_count, char *filename);

#endif  // s21_grep_h