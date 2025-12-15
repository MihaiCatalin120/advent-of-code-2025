#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getJoltage(char fileContents[]) {
  int firstDigit = 9, secondDigit = 9;

  while (firstDigit > 0) {
    // printf("Searching for first digit %d in %s\n", firstDigit, fileContents);
    char *firstDigitPointer = strchr(fileContents, firstDigit + '0');

    if (firstDigitPointer != NULL) {
      // printf("Found first digit %d\n", firstDigit);
      while (secondDigit > 0) {
        // printf("Searching for second digit %d\n", secondDigit);
        char *secondDigitPointer =
            strchr(firstDigitPointer + 1, secondDigit + '0');

        if (secondDigitPointer != NULL) {
          // printf("Found second digit %d\n", secondDigit);
          return firstDigit * 10 + secondDigit;
        }

        secondDigit--;
      }
    }

    firstDigit--;
    secondDigit = 9;
  }

  return 0;
}

int main() {
  FILE *f = fopen("3_test_in.txt", "r");
  char fileContents[200];
  int total = 0;

  assert(f != NULL);

  while (fgets(fileContents, 200, f) != NULL) {
    printf("Got %d joltage for %s\n", getJoltage(fileContents), fileContents);
    total += getJoltage(fileContents);
    printf("Subtotal: %d\n", total);
  }

  printf("\nTotal: %d\n", total);

  fclose(f);
  return 0;
}
