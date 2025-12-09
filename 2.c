#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://stackoverflow.com/questions/32496497/standard-function-to-replace-character-or-substring-in-a-char-array
char *replace_char(char *str, char find, char replace) {
  char *current_pos = strchr(str, find);
  while (current_pos) {
    *current_pos = replace;
    current_pos = strchr(current_pos, find);
  }
  return str;
}

bool checkID(unsigned long long id) {
  // printf("Checking id %llu:", id);
  int noDigits = log10(id) + 1;

  if (noDigits % 2 != 0) {
    // printf("Valid\n");
    return true;
  }

  unsigned long long upper, inner;
  upper = id / (int)pow(10, (int)(noDigits / 2));
  inner = id % (int)pow(10, (int)(noDigits / 2));

  // precision loss is fine, we work with whole numbers here
  if (upper != inner) {
    // printf("Valid\n");
    return true;
  }

  // printf("Invalid\n");
  return false;
}

void addFromRange(char *range, unsigned long long *sum) {
  char boundaries[50];
  unsigned long long start = 0, end = 0, id;
  char *splitEnd;

  replace_char(range, '-', ' ');

  start = strtol(range, &splitEnd, 10);
  range = splitEnd + 1;
  end = strtol(range, &splitEnd, 10);

  for (id = start; id <= end; id++) {
    if (!checkID(id))
      *sum += id;
  }
}

int main() {
  // FILE *f = fopen("2_test_in.txt", "r");
  FILE *f = fopen("2_in.txt", "r");
  assert(f != NULL);

  char currentChar;
  int idRangesIndex = 0, currentIDRangeIndex = 0;
  char **idRanges;
  char *temp;

  idRanges = malloc(100 * sizeof(*idRanges));
  temp = malloc(100 * 100 * sizeof(idRanges[0]));

  for (int i = 0; i < 100; i++) {
    idRanges[i] = temp + i * 100;
  }

  while ((currentChar = fgetc(f)) != EOF) {
    idRanges[idRangesIndex][currentIDRangeIndex] = currentChar;
    currentIDRangeIndex++;

    if (currentChar == ',') {
      // printf("\n");
      idRangesIndex++;
      currentIDRangeIndex = 0;
    }
  }

  idRangesIndex++;
  currentIDRangeIndex = 0;

  unsigned long long total = 0;
  for (int i = 0; i < idRangesIndex; i++) {
    printf("\n==========================\n");
    printf("Processing id range: %s\n", idRanges[i]);
    addFromRange(idRanges[i], &total);
    printf("Partial Total: %llu\n", total);
  }

  printf("\n\nTotal: %llu", total);

  fclose(f);
  free(temp);
  free(idRanges);

  return 0;
}
