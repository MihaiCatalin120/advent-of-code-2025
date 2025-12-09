#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void makeTurn(int turnDegree, char direction, int *pointer, int *password) {
  int turnDirection = 1;
  if (direction == 'L')
    turnDirection = -1;

  while (turnDegree > 0) {
    *pointer += turnDirection;
    turnDegree--;

    if (*pointer < 0)
      *pointer += 100;
    if (*pointer >= 100)
      *pointer -= 100;
    if (*pointer == 0)
      *password += 1;
  }
}

int main() {
  FILE *f = fopen("1_in.txt", "r");
  char fileContents[100];
  int password = 0, pointer = 50;
  char direction;

  assert(f != NULL);

  while (fgets(fileContents, 100, f) != NULL) {
    printf("Processing turn %s", fileContents);

    direction = fileContents[0];

    // Space is stripped out by strtol
    fileContents[0] = ' ';

    // Alternative for first char replacement
    //  memmove(fileContents, fileContents + 1, strlen(fileContents));

    int turnDegree = strtol(fileContents, NULL, 10);

    printf("Got direction %c with degree %d\n", direction, turnDegree);

    makeTurn(turnDegree, direction, &pointer, &password);

    printf("Pointer now at %d, password is now %d\n\n", pointer, password);
  }

  printf("Final password: %d", password);

  fclose(f);
  return 0;
}
