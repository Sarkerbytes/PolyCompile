#include <stdio.h>

int main() {
  int number;
  printf("Enter an integer: ");
  scanf("%d", &number);

  // Check if the number is even or odd
  if (number % 2 == 0) {
    printf("%d is an even integer.\n", number);
  } else {
    printf("%d is an odd integer.\n", number);
  }

  return 0;
}