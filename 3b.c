#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long getJoltage(char fileContents[]) {
  char result[12], max;
  int neededChars = 12, digit = 9;
  char *maxPointer = NULL;

  while (neededChars > 0) {

    while (digit > 0) {
      maxPointer = strchr(maxPointer == NULL ? fileContents : maxPointer + 1,
                          digit + '0');
      printf("Strlen %lu\n", strlen(fileContents));
      if (maxPointer - fileContents + 1 < strlen(fileContents) - neededChars) {
        max = *maxPointer;
        goto found;
      }

      digit--;
    }

    assert(digit > 0);

  found:
    result[12 - neededChars] = max;
    neededChars--;
    digit = 9;
  }

  return strtol(result, NULL, 10);
}

int main() {
  FILE *f = fopen("3_in.txt", "r");
  // FILE *f = fopen("3_test_in.txt", "r");
  char fileContents[200];
  unsigned long total = 0;

  assert(f != NULL);

  while (fgets(fileContents, 200, f) != NULL) {
    printf("Got %lu joltage for %s", getJoltage(fileContents), fileContents);
    total += getJoltage(fileContents);
    printf("Subtotal: %lu\n", total);
  }

  printf("\nTotal: %lu\n", total);

  fclose(f);
  return 0;
}
