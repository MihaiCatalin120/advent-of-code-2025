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
  // https://stackoverflow.com/a/32819876
  int length = snprintf(NULL, 0, "%llu", id);
  char *idString = malloc(length + 1);
  snprintf(idString, length + 1, "%llu", id);
  int substringLength = 1, i = 0;
  int startIndex = 0;
  // printf("\n\nChecking ID for %llu...\n", id);

  while (substringLength <= length / 2) {
    for (startIndex = 0; startIndex < substringLength; startIndex++) {

      // printf("Checking for substring length %d\n", substringLength);
      for (i = startIndex; i < length - substringLength; i += substringLength) {
        // printf("Step %d - Comparing %c to %c\n", substringLength,
        // idString[i],
        //        idString[i + substringLength]);
        if (idString[i] != idString[i + substringLength]) {
          // no need to check further for this substring length
          startIndex = substringLength + 1;
          break;
        }
      }
    }
    if (startIndex == substringLength) {
      free(idString);
      printf("Found invalid id: %llu\n", id);
      return false;
    }

    substringLength++;
  }

  free(idString);
  return true;
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
