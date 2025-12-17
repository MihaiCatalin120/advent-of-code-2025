#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

long long getJoltage(char fileContents[]) {
  char result[200];
  int resultLen = 0, removals;
  char *cursor = fileContents;

  removals = strlen(fileContents) - 1 - 12;
  // printf("Removals: %d\n", removals);
  //

  while (isdigit(*cursor) == 1) {
    // printf("reading %c\n", *cursor);
    if (resultLen == 0 || *cursor <= result[resultLen - 1] || removals == 0) {
      result[resultLen++] = *cursor;
      // printf("Pushed %c, stack size is now %d\n", *cursor, resultLen);
    } else {
      while (*cursor > result[resultLen - 1] && removals > 0 && resultLen > 0) {
        // printf("Popped %c", result[resultLen - 1]);
        resultLen--;
        // printf(", stack size is now %d\n", result[resultLen - 1]);
        removals--;
      }
      result[resultLen++] = *cursor;
      // printf("Pushed %c, stack size is now %d\n", *cursor, resultLen);
    }

    cursor++;
  }

  result[12] = ' ';
  printf("Result is %s\n", result);
  return strtoll(result, NULL, 10);
}

int main() {
  // FILE *f = fopen("3_in.txt", "r");
  FILE *f = fopen("3_test_in.txt", "r");
  char fileContents[200];
  unsigned long total = 0;

  assert(f != NULL);

  while (fgets(fileContents, 200, f) != NULL) {
    printf("Read %s", fileContents);
    long long result = getJoltage(fileContents);
    printf("Got %lld joltage for %s", result, fileContents);
    total += result;
    printf("Subtotal: %lu\n", total);
  }

  printf("\nTotal: %lu\n", total);

  fclose(f);
  return 0;
}
