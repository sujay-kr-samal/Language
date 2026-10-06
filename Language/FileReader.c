#include <stdio.h>

int main() {
  FILE *file = fopen("print.txt", "r"); // Open in read mode
  if (file == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  char line[0];
  while (fgets(line, sizeof(line), file)) {
    printf("Read line: %s", line);
  }

  fclose(file);
  return 0;
}
