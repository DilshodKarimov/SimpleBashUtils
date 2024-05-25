#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(char *name, char *flags);
void flag_parser(int argc, char **argv, char *flags);
void flag_case(char q[1000], char *flags);
char tolowe(char k);

int main(int argc, char **argv) {
  char flags[6] = "12345";
  flag_parser(argc, argv, flags);
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '0') {
      print_file(argv[i], flags);
    }
  }
  return 0;
}

void print_file(char *name, char *flags) {
  FILE *f = fopen(name, "rt");
  if (f != NULL) {
    int c = fgetc(f);
    int i = 1;
    int q = 0;
    int prev = 0;
    int endline = 0;
    if (strchr(flags, 'b') != NULL) {
      q = 1;
    } else if (strchr(flags, 'n')) {
      q = 2;
    }
    prev = '\n';
    while (c != EOF) {
      if (!(strchr(flags, 's') != NULL && prev == '\n' && c == '\n' &&
            endline == 1)) {
        if (prev == '\n' && c == '\n')
          endline = 1;
        else
          endline = 0;
        if ((q == 1 && c != '\n') && prev == '\n') {
          printf("%6d\t", i);
          i++;
        } else if (q == 2 && prev == '\n') {
          printf("%6d\t", i);
          i++;
        }
        if (strchr(flags, 'e') != NULL && c == '\n') {
          if (q == 1 && prev == '\n') {
            printf("%6s\t$", "");
          } else {
            printf("$");
          }
        }
        if (strchr(flags, 't') != NULL && c == '\t') {
          printf("^");
          c = 64 + '\t';
        }
        printf("%c", c);
      }
      prev = c;
      c = fgetc(f);
    }
    fclose(f);
  }
}

void flag_parser(int argc, char **argv, char *flags) {
  int i = 0;
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[0], "--number-nonblank") == 0) {
      flags[0] = 'b';
      argv[i] = "0";
    } else if (strcmp(argv[i], "-E") == 0) {
      flags[1] = 'e';
      argv[i] = "0";
    } else if (strcmp(argv[i], "-v") == 0) {
      flags[1] = 'e';
      argv[i] = "0";
    } else if (strcmp(argv[i], "--number") == 0) {
      flags[2] = 'n';
      argv[i] = "0";
    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
      flags[3] = 's';
      argv[i] = "0";
    } else if (strcmp(argv[i], "-T") == 0) {
      flags[4] = 't';
      argv[i] = "0";
    } else if (argv[i][0] == '-') {
      flag_case(argv[i], flags);
      argv[i] = "0";
    }
  }
  return;
}

void flag_case(char q[1000], char *flags) {
  int n = strlen(q);
  for (int i = 0; i < n; i++) {
    switch (q[i]) {
      case 'b':
        flags[0] = 'b';
        break;
      case 'e':
        flags[1] = 'e';
        break;
      case 'n':
        flags[2] = 'n';
        break;
      case 's':
        flags[3] = 's';
        break;
      case 't':
        flags[4] = 't';
        break;
    }
  }
}

char tolowe(char k) {
  if (k <= 'Z' && k >= 'A') {
    k = k - 'A' + 'a';
  }
  return k;
}
