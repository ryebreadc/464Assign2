#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_and_print(char* filename, char* output) {
  
  FILE *f = fopen(filename, "r");
  if(f == NULL) {
    fprintf(stderr, "Error opening file '%s'\n", filename);
    exit(1);
  }
  char *buffer;
  size_t length = 0;
  size_t total_length = 0;
  ssize_t line_size = 0;
  ssize_t total_size = 0;
  int total_lines = 0;
  line_size = getline(&buffer, &length, f);

  while(line_size>= 0) {
    line_size = getline(&buffer, &length, f);
    total_size += line_size;
    total_length += length;
    total_lines++;
  }
  free(buffer);
  buffer = NULL;
  fclose(f);

  f = fopen(filename, "r+");
  if(f == NULL) {
    fprintf(stderr, "Error opening file '%s'\n", filename);
  }
  FILE *g = fopen(output, "w+");
  if(g == NULL) {
    fprintf(stderr, "Error writing to file '%s'\n", output);
  }

  line_size = getline(&buffer, &length, f);

  char **deliverable = (char **)calloc(total_lines, sizeof(char));
  for(int i = 0; i < total_lines; i++) {
    deliverable[i] = (char *)calloc(total_length, sizeof(char));
  }
  
  ssize_t next_size = 0;
  ssize_t next_ceil = 0;
  int tick = 0;
  while(line_size>= 0) {
    next_size += line_size;
    next_ceil = next_size - line_size;
    for(int i = 0; i < line_size; i++) {
      deliverable[tick][i] = buffer[i];
      printf("%c", buffer[i]);
    }
    line_size = getline(&buffer, &length, f);
    tick++;
  }
  fclose(f);
  for(int i = total_lines - 1; i >= 0; i--) {
    fprintf(g, "\n%s", deliverable[i]);
  }
}

int main(int argc, char *argv[]) {
  
  //Just running the program, no input/output file.
  if(argc == 1) {
    char* f = "input.txt";
    char* g = "output.txt";
    read_and_print(f, g);
  } 
  //Running the program with just the input file.
  else if(argc == 2) {
    char* g = "output.txt";
    read_and_print(argv[1], g);
  } 
  //Running the program with both the input and output file.
  else if(argc == 3) {
    read_and_print(argv[1], argv[2]);
  }
  //Too many command line arguements.
  else {
    printf("%s", "Entered too many arguements,\nusage: reverse <input> <output>");
    exit(1);
  }

  return 0;
}
