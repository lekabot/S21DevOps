#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char pattern[1024] = "\0";
  opt opts = {0};
  parser(argc, argv, &opts, pattern);
  search(argc, argv, &opts, pattern);
  return 0;
}

void parser(int argc, char *argv[], opt *opts, char *pattern) {
  int flag;
  while ((flag = getopt_long(argc, argv, "e:ivclnhsf:o", 0, 0)) != -1) {
    switch (flag) {
      case 'e':
        opts->e = 1;
        e_flag(pattern, optarg);
        break;
      case 'i':
        opts->i = 1;
        break;
      case 'v':
        opts->v = 1;
        break;
      case 'c':
        opts->c = 1;
        break;
      case 'l':
        opts->l = 1;
        break;
      case 'n':
        opts->n = 1;
        break;
      case 'h':
        opts->h = 1;
        break;
      case 's':
        opts->s = 1;
        break;
      case 'f':
        opts->f = 1;
        f_flag(pattern, optarg);
        break;
      case 'o':
        opts->o = 1;
        break;
      default:
        exit(1);
        break;
    }
    kostbil(opts);
  }
}

void search(int argc, char *argv[], opt *opts, char *pattern) {
  FILE *fp = NULL;
  char str[MY_SIZE] = {0};
  regex_t compiled;
  int cflags = REG_EXTENDED;
  if (!(opts->e || opts->f) && argv[optind]) {
    strcpy(pattern, argv[optind]);
    optind++;
  }
  if (opts->i) {
    cflags = REG_ICASE;
  }
  int file_count = 1;
  if ((argc - optind) > 1) {
    file_count++;
  }
  for (int i = optind; i < argc; ++i) {
    if (argv[i][0] != '-') {
      if ((fp = fopen(argv[i], "r")) == NULL) {
        if (!opts->s) {
          fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
          continue;
        }
      }
      if (fp != NULL) {
        regcomp(&compiled, pattern, cflags);
        flags(compiled, opts, str, fp, file_count, argv[i]);
      } else {
        if (!opts->s) {
          fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
        }
      }
    }
    if (fp != NULL) {
      regfree(&compiled);
      fclose(fp);
    }
  }
}

void flags(regex_t compiled, opt *opts, char *str, FILE *fp, int file_count,
           char *filename) {
  regmatch_t pmatch[1];
  int count = 0;
  int line = 0;
  while (fgets(str, MY_SIZE - 1, fp) != NULL) {
    int match = 0;
    count++;
    int success = 0;
    char *begin_search = str;
    while ((success = regexec(&compiled, begin_search, 1, pmatch, 0)) == 0) {
      if (match >= 0 && (file_count > 1) && !opts->h && !opts->l && !opts->c &&
          opts->o) {
        printf("%s:", filename);
      }
      if (match >= 0 && opts->n && opts->o) {
        printf("%d:", count);
      }
      if ((success >= 0) && opts->o) {
        for (long long i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
          printf("%c", begin_search[i]);
        }
        printf("\n");
      }
      match += 1;
      begin_search += pmatch[0].rm_eo;
    }
    if (opts->v) {
      match = !match;
    }
    if (!opts->o) {
      if (match && (file_count > 1) && !opts->h && !opts->l && !opts->c) {
        printf("%s:", filename);
      }
      if (match && opts->n) {
        printf("%d:", count);
      }
    }
    if (match && !opts->c && !opts->l && !opts->o) {
      if (strchr(str, '\n') == NULL) {
        strcat(str, "\n");
      }
      printf("%s", str);
    }
    line += !!match;
  }
  cl_kostbil(opts, line, file_count, filename);
}

void kostbil(opt *opts) {
  if (opts->l) {
    opts->n = 0;
    opts->o = 0;
  }
  if (opts->c) {
    opts->o = 0;
    opts->n = 0;
  }
  if (opts->v) {
    opts->o = 0;
  }
}

void cl_kostbil(opt *opts, int line, int file_count, char *filename) {
  if (opts->l && line > 0 && !opts->c) {
    printf("%s\n", filename);
  }
  if (opts->c && !opts->l && !opts->h) {
    if (file_count > 1) {
      printf("%s:%d\n", filename, line);
    } else {
      printf("%d\n", line);
    }
  } else if (opts->c && !opts->l && opts->h) {
    printf("%d\n", line);
  }
  if (opts->c && opts->l) {
    if (file_count < 2) {
      if (!opts->n && !opts->o) {
        printf("%d\n%s\n", file_count, filename);
      } else {
        printf("%s:%d\n", filename, line);
      }
    } else {
      if (line && !opts->h) {
        printf("%s:%d\n", filename, file_count - 1);
        printf("%s\n", filename);
      } else if (!line && !opts->h) {
        printf("%s:0\n", filename);
      } else if (line && opts->h) {
        printf("%d\n%s\n", file_count - 1, filename);
      } else if (!line && opts->h) {
        printf("0\n");
      }
    }
  }
}

void e_flag(char *pattern, char *str) {
  if (*pattern != '\0') {
    strcat(pattern, "|");
  }
  strcat(pattern, str);
}

void f_flag(char *pattern, char *filename) {
  FILE *fp;
  char strtwo[MY_SIZE] = {0};
  fp = fopen(filename, "r");
  if (fp != NULL) {
    while (fgets(strtwo, MY_SIZE - 1, fp) != NULL) {
      unsigned long p = strlen(strtwo);
      if (strtwo[p - 1] == '\n') {
        strtwo[p - 1] = '\0';
      }
      if (strtwo[0] == '\0') {
        strcpy(strtwo, ".");
      }
      e_flag(pattern, strtwo);
    }
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
  }
  fclose(fp);
}
