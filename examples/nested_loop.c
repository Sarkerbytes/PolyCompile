#include <stdio.h>

int main() {
  int i, j;
  // Outer loop controls rows
  for (i = 1; i <= 5; i++) {
    // Inner loop controls columns
    for (j = 1; j <= 5; j++) {
      printf("* ");
    }
    // Move to the next line after each row
    printf("\n");
  }
  return 0;
}