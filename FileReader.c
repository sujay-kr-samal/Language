#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
  FILE *file = fopen(filename, "rb");

  if (file == NULL) {
    perror("Could not open file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = malloc(size + 1);

  if (buffer == NULL) {
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, size, file);
  buffer[bytes_read] = '\0';

  fclose(file);

  return buffer;
}
