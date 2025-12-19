
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int isAccessible(int row, int column, char fileContents[140][140],
                 int rowLength, int columnLength) {
  int adjacentPaperNumber = 0;

  assert(row >= 0 && column >= 0 && row < rowLength && column < columnLength);
  // top
  if (row > 0) {
    row--;
    printf("Top is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  // top right
  if (column < columnLength - 1) {
    column++;
    printf("Top right is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  // right
  if (row < rowLength - 1) {
    row++;
    printf("Right is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  // bottom right
  if (row < rowLength - 1) {
    row++;
    printf("Bottom right is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  // bottom
  if (column > 0) {
    column--;
    printf("Bottom is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  // bottom left
  if (column > 0) {
    column--;
    printf("Bottom left is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  // left
  if (row > 0) {
    row--;
    printf("Left is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  // top left
  if (row > 0) {
    row--;
    printf("Top left is %d\n", fileContents[row][column] == '@');
    adjacentPaperNumber += fileContents[row][column] == '@';
  }

  if (adjacentPaperNumber < 4) {
    printf("Valid\n");
  } else
    printf("Invalid\n");

  return adjacentPaperNumber < 4 ? 1 : 0;
}

int main() {
  FILE *f = fopen("4_in.txt", "r");
  // FILE *f = fopen("4_test_in.txt", "r");
  char fileContents[140][140];
  int rows = 0, count = 0;

  assert(f != NULL);

  while (fgets(fileContents[rows++], 200, f) != NULL) {
    printf("Row %d: %s", rows - 1, fileContents[rows - 1]);
  }

  for (int row = 0; row < rows; row++) {
    // int rowLength = 140;
    int rowLength = 11;
    // int rowLength = strlen(fileContents[row]);
    for (int column = 0; column < rowLength; column++) {
      printf("Call is accessible: row[%d] column[%d], rowLength[%d], "
             "columnLength[%d]\n",
             row, column, rowLength, rows);
      count += isAccessible(row, column, fileContents, rowLength, rows);
    }
  }

  printf("Total accessible: %d", count);

  fclose(f);
  return 0;
}
