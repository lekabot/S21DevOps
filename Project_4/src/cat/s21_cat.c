#include "s21_cat.h"

void start_point(int argc, char **argv) {
  Options options = {0};
  parser(argc, argv, &options);
  int current_file_position = optind;
  FILE *file_name;
  int file_count = count_files(argc, argv, optind);
  if (file_count == 0) {
    while (1) {
      reader(&options, stdin);
    }
  } else {
    while (current_file_position != argc) {
      if ((file_name = fopen(argv[current_file_position], "r"))) {
        if (file_name) {
          reader(&options, file_name);
        }
        fclose(file_name);
      } else {
        fprintf(stderr, "cat: %s: No such file or directory\n",
                argv[current_file_position]);
      }
      current_file_position++;
    }
  }
}

void parser(int argc, char *argv[], Options *options) {
  int opt;
  int option_index = 0;
  optind = 1;
#ifdef __unix__
  char *opt_str = "bvnseEtT";
#else
  char *opt_str = "+bvnseEtT";
#endif
  while ((opt = getopt_long(argc, argv, opt_str, long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'E':
        options->e = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->v = 1;
        options->t = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      default:
        printf("error key");
        break;
    }
  }
}

void reader(Options *options, FILE *file_name) {
  char cur;
  char prev = ' ';
  char preprev = ' ';
  int line_count = 0;
  int line_number_signal = 0;
  int empty_line_flag = 0;
  while ((cur = fgetc(file_name)) != EOF) {
    int s_flag = 0;
    int str_flag_0 = 0;
    int str_flag_1 = 0;
    int tv_flag = 0;
    option_s(&s_flag, cur, prev, preprev, options, empty_line_flag, str_flag_0,
             str_flag_1);
    option_b(&s_flag, cur, options, &line_number_signal, &line_count);
    option_n(&s_flag, cur, prev, options, &line_number_signal, &line_count);
    option_e(&s_flag, prev, cur, options, line_count);
    option_v(&tv_flag, cur, options);
    option_t(&tv_flag, cur, options);
    if (tv_flag == 0 && s_flag == 0) {
      printf("%c", cur);
    }
    preprev = prev;
    prev = cur;
    if (cur == '\n') {
      if (str_flag_0 == 1) {
        str_flag_1 = 0;
      }
      str_flag_0 = 1;
      empty_line_flag++;
    }
  }
}

void option_s(int *s_flag, char cur, char prev, char preprev, Options *options,
              int str_flag, int str_flag_0, int str_flag_1) {
  if (options->s) {
    if (cur == '\n' && prev == '\n' &&
        (preprev == '\n' ||
         (str_flag < 2 && str_flag_0 == 1 && str_flag_1 == 1))) {
      *s_flag = 1;
    }
  }
}

void option_e(int *s_flag, char prev, char cur, Options *options,
              int str_count) {
  if (options->e && *s_flag == 0) {
    if (cur == '\n') {
      if ((str_count == 0 || prev == '\n') && options->b) {
        printf("      \t");
      }
      printf("$");
    }
  }
}

void option_t(int *tv_flag, char cur, Options *options) {
  if (options->t) {
    if (cur == '\t') {
      printf("^I");
      *tv_flag = 1;
    }
  }
}

void option_b(int *s_flag, char cur, Options *options, int *counter,
              int *str_count) {
  if (options->b && *s_flag == 0) {
    if (cur != '\n') {
      if (*counter == 0) {
        printf("%6d\t", *str_count = *str_count + 1);
        *counter = 1;
      }
    } else {
      *counter = 0;
    }
  }
}

void option_n(int *s_flag, char cur, char prev, Options *options, int *counter,
              int *str_count) {
  if (options->n && options->b == 0 && *s_flag == 0) {
    if (cur != '\n') {
      if (*counter == 0) {
        printf("%6d\t", *str_count = *str_count + 1);
        *counter = 1;
      }
    } else {
      if (prev == '\n') {
        printf("%6d\t", *str_count = *str_count + 1);
      } else if (*str_count == 0 && cur == '\n') {
        printf("%6d\t", *str_count = *str_count + 1);
      }
      *counter = 0;
    }
  }
}

void option_v(int *tv_flag, char cur, Options *options) {
  if (options->v) {
    if ((cur < 32) && (cur != '\n') && (cur != '\t')) {
      printf("^%c", cur + 64);
      *tv_flag = 1;
    } else if (cur == 127) {
      printf("^?");
      *tv_flag = 1;
    }
  }
}

int count_files(int argc, char *argv[], int ind) {
  int IS_FILE = 0;
  while (ind != argc && IS_FILE == 0) {
    FILE *file_name;
    if ((file_name = fopen(argv[ind], "r")) == NULL) {
      IS_FILE = -1;
    } else {
      IS_FILE = 1;
      fclose(file_name);
    }
    ind++;
  }
  return IS_FILE;
}

int main(int argc, char **argv) {
  start_point(argc, argv);
  return 0;
}
