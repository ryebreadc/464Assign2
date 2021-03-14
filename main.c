#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_and_print(char* filename, char* output) {
  
  //Opening the passed file
  FILE *f = fopen(filename, "r");
  if(f == NULL) {
    fprintf(stderr, "Error opening file '%s'\n", filename);
    exit(1);
  }
  //Holds lines of file
  char *buffer;
  //Length of line in bytes
  size_t length = 0;
  //Total length in bytes of all lines
  size_t total_length = 0;
  //Number of characters on the line
  ssize_t line_size = 0;
  //Total number of characters
  ssize_t total_size = 0;
  //Total number of lines
  int total_lines = 0;

  line_size = getline(&buffer, &length, f);
  //Reading through input to get above variables
  while(line_size>= 0) {
    line_size = getline(&buffer, &length, f);
    total_size += line_size;
    total_length += length;
    total_lines++;
  }
  free(buffer);
  buffer = NULL;
  fclose(f);

  //Reopening f after the close
  f = fopen(filename, "r+");
  if(f == NULL) {
    fprintf(stderr, "Error opening file '%s'\n", filename);
  }
  //Opening g for the output file
  FILE *g = fopen(output, "w+");
  if(g == NULL) {
    fprintf(stderr, "Error writing to file '%s'\n", output);
  }

  line_size = getline(&buffer, &length, f);

  //Doubly nested char* to store lines
  char **deliverable = (char **)calloc(total_lines, sizeof(char));
  for(int i = 0; i < total_lines; i++) {
    deliverable[i] = (char *)calloc(total_length, sizeof(char));
  }
  //

  int tick = 0;
  while(line_size>= 0) {

    //For loop assigning buffer values to final deliverable 
    for(int i = 0; i < line_size; i++) {
      deliverable[tick][i] = buffer[i];
      printf("%c", buffer[i]);
    }
    line_size = getline(&buffer, &length, f);
    tick++;
  }
  fclose(f);
  //Actual reversing function, and printing to output
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
