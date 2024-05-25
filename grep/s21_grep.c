#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int flag_parser(int argc, char **argv, int *index, char *flags);
void print_file(char *file, char *flags, char *pattern, bool more);
int solve(char *file, char *flags, char *pattern, bool *v, char *line, int *k,
          int *i, bool more);
int solve_1(char *file, char *flags, char *pattern, char *line, int *k,
            bool more);
int flag_case(char **argv, int i, char *flags, int *index);

char *tolowe(char *line);
bool more_files(int argc, char **argv);
void check(char *file, bool more);
bool treatment_f(FILE *ff, char *file, char *flags, bool *v, char *line, int *k,
                 int *i, bool more);
void flag_o(char *file, char *line, char *pattern, char *flags, int *i,
            bool more);

int main(int argc, char **argv) {
  int index = 0, k = 0;

  char flags[11] = "1234567890";
  char *pattern = {0};
  bool more = false;
  k = flag_parser(argc, argv, &index, flags);
  // printf("%s",flags);
  if (index == 0) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '0') {
        pattern = argv[i];
        index++;
        argv[i] = "0";
        break;
      }
    }
  } else {
    pattern = argv[k];
    argv[k] = "0";
  }
  if (more_files(argc, argv) == true) {
    more = true;
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '0') {
      print_file(argv[i], flags, pattern, more);
    }
  }
  return 0;
}

void print_file(char *file, char *flags, char *pattern, bool more) {
  FILE *f = fopen(file, "r");
  FILE *ff = NULL;

  if (strchr(flags, 'f') != NULL) {
    ff = fopen(pattern, "r");
  }

  if (f != NULL && (ff != NULL || strchr(flags, 'f') == NULL)) {
    int k = 0, i = 0;
    char line[1000] = {0};
    bool v = false;
    int f1 = true;
    if (strchr(flags, 'h') != NULL) {
      more = false;
    }
    if (strchr(flags, 'v') != NULL) {
      v = true;
    }
    while (fgets(line, 1000, f) != NULL) {
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = 0;
      }
      if (strchr(flags, 'f') == NULL) {
        f1 = solve(file, flags, pattern, &v, line, &k, &i, more);
      } else {
        f1 = treatment_f(ff, file, flags, &v, line, &k, &i, more);
      }
      if (f1 == 2) {
        break;
      }
    }
    if (strchr(flags, 'c') != NULL && f1 != 2) {
      check(file, more);
      printf("%d\n", k);
    }
    fclose(f);
    if (strchr(flags, 'f') != NULL) {
      fclose(ff);
    }
  } else {
    if (strchr(flags, 's') == NULL) {
      check(file, more);
      printf("No Such file or directory!!!\n");
    }
  }
}

void check(char *file, bool more) {
  if (more == true) {
    printf("%s:", file);
  }
}

char *tolowe(char *line) {
  int end = strlen(line);
  for (int i = 0; i < end; i++) {
    if (line[i] <= 'Z' && line[i] >= 'A') {
      line[i] = line[i] - 'A' + 'a';
    }
  }
  return line;
}

int solve(char *file, char *flags, char *pattern, bool *v, char *line, int *k,
          int *i, bool more) {
  bool flag = false;
  int f = 0;
  if (strchr(flags, 'l') == NULL && strchr(flags, 'c') == NULL) {
    (*i)++;
    if (strstr(line, pattern) != NULL) {
      flag = true;
      // printf("123");
    }
    if (flag == false && strchr(flags, 'i') != NULL) {
      char q[1000] = {0}, pattern_1[1000] = {0};
      strcpy(q, line);
      strcpy(pattern_1, pattern);
      if (strstr(tolowe(q), tolowe(pattern_1)) != NULL) {
        flag = true;
      }
    }
    if (*v == true) {
      flag = !flag;
    }
    // o ??
    // printf("\n123\n");
    if ((strchr(flags, 'o') != NULL && flag == true) && *v != true) {
      flag_o(file, line, pattern, flags, i, more);
      flag = false;
    }

    if (flag == true) {
      check(file, more);
      if (strchr(flags, 'n') != NULL) {
        printf("%d:", *i);
      }
      printf("%s\n", line);
      flag = false;
      f = 1;
    }
  } else {
    f = solve_1(file, flags, pattern, line, k, more);
  }
  return f;
}

int flag_parser(int argc, char **argv, int *index, char *flags) {
  int i = 0, k = 0;
  for (i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      k = flag_case(argv, i, flags, index);
      argv[i] = "0";
    }
  }
  return k;
}

int solve_1(char *file, char *flags, char *pattern, char *line, int *k,
            bool more) {
  int f = 0;
  bool flag = false;
  if (strstr(line, pattern) != NULL) {
    flag = true;
  }
  if (flag == false && strchr(flags, 'i') != NULL) {
    char q[1000] = {0}, pattern_1[1000] = {0};
    strcpy(q, line);
    strcpy(pattern_1, pattern);
    if (strstr(tolowe(q), tolowe(pattern_1)) != NULL) {
      flag = true;
    }
  }
  if (strchr(flags, 'v') != NULL) {
    flag = !flag;
  }
  // return 0;
  if (flag == true) {
    (*k)++;
  }
  if (*k == 1 && strchr(flags, 'l') != NULL) {
    if (strchr(flags, 'c') != NULL) {
      check(file, more);
      printf("1\n");
    }
    printf("%s\n", file);
    f = 2;
  }
  // printf("%d",f);
  return f;
}

int flag_case(char **argv, int i, char *flags, int *index) {
  int q = strlen(argv[i]);
  int k = -1;
  for (int j = 1; j < q; j++) {
    if (argv[i][j] != '-') {
      switch (argv[i][j]) {
        case 'i':
          flags[0] = 'i';
          break;
        case 'v':
          flags[1] = 'v';
          break;
        case 'c':
          flags[2] = 'c';
          break;
        case 'l':
          flags[3] = 'l';
          break;
        case 'n':
          flags[4] = 'n';
          break;
        case 'h':
          flags[5] = 'h';
          break;
        case 's':
          flags[6] = 's';
          break;
        case 'f':
          flags[7] = 'f';
          i++;
          (*index)++;
          k = i;
          break;
        case 'o':
          flags[8] = 'o';
          break;
        case 'e':
          flags[9] = 'e';
          i++;
          (*index)++;
          k = i;
          break;
      }
    }
  }
  return k;
}

bool treatment_f(FILE *ff, char *file, char *flags, bool *v, char *line, int *k,
                 int *i, bool more) {
  char q[1000] = {0};
  int f = true;
  while (fgets(q, 1000, ff) != NULL) {
    // printf("%s",q);
    if (q[strlen(q) - 1] == '\n') {
      q[strlen(q) - 1] = 0;
    }
    f = solve(file, flags, q, v, line, k, i, more);
    if (f == 1 || f == 2) {
      break;
    }
  }
  fseek(ff, 0, SEEK_SET);
  return f;
}

bool more_files(int argc, char **argv) {
  int more = 0;
  bool f = false;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '0') {
      more++;
    }
  }
  if (more > 1) {
    f = true;
  }
  return f;
}

void flag_o(char *file, char *line, char *pattern, char *flags, int *p,
            bool more) {
  char q[1000] = {0}, pattern_1[1000] = {0};
  int j = 0, end1 = strlen(line), end2 = strlen(pattern);
  char out[1000] = {0};
  strcpy(q, line);
  strcpy(pattern_1, pattern);
  tolowe(q);
  tolowe(pattern_1);

  for (int i = 0; i < end1; i++) {
    if (j == end2) {
      check(file, more);
      if (strchr(flags, 'n') != NULL) {
        printf("%d:", (*p));
      }
      printf("%s\n", out);
      out[0] = '\0';
      j = 0;
    }
    if (line[i] == pattern[j] ||
        (strchr(flags, 'i') != NULL && q[i] == pattern_1[j])) {
      out[j] = line[i];
      j++;
    } else {
      j = 0;
      if (line[i] == pattern[j] ||
          (strchr(flags, 'i') != NULL && q[i] == pattern_1[j])) {
        out[j] = line[i];
        j++;
      }
    }
  }
  if (j == end2) {
    check(file, more);
    if (strchr(flags, 'n') != NULL) {
      printf("%d:", (*p));
    }
    printf("%s\n", out);
    out[0] = '\0';
    j = 0;
  }
  return;
}

// 492