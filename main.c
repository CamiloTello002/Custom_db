#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dynamic buffer for user input
typedef struct {
  char* buffer; // Pointer to the actual buffer (array of characters) that stores input.
  size_t buffer_length; // Size of allocated memory for 'buffer'
  ssize_t input_length; // Actual length of the input (# of characters entered)
} InputBuffer;

// This dynamically creates and initializes an InputBuffer structure
InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

// This function comes in handy for reading user input
void read_input(InputBuffer* input_buffer){
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0){
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer){
  free(input_buffer->buffer);
  free(input_buffer);
}

void print_prompt() { printf("db > ");}

int main(int argc, char* argv[]){
  InputBuffer* input_buffer = new_input_buffer();
  for(;;){
    // shows the entry
    print_prompt();
    // this function waits for the user to type something
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0){
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}

