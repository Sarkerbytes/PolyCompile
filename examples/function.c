#include <stdio.h>

// Function declaration
int add(int a, int b);

int main() {
  // Function call
  int result = add(5, 10);
  printf("Sum: %d\n", result);
  return 0;
}

// Function definition
int add(int a, int b) { return a + b; }