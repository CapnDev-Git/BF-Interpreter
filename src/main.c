#include "main.h"

/// @brief Retrieves the program & its size from the provided .bf file
/// @param path Path to the .bf file
/// @param program BF program to evaluate
/// @param size BF program size (in bytes)
void get_program(char *path, char *program, size_t *size) {
  // Initialize the program size & its index
  size_t s;
  char c;

  // Open the file & read its content
  FILE *pfile;
  pfile = fopen(path, "r");
  if (pfile == NULL)
    errx(1, "Provided file can't be opened!");

  // Read BF file (excluding EOF)
  while ((c = fgetc(pfile)) != EOF)
    // Store the character in the program
    program[s++] = c;

  // Close the file & get the program size
  fclose(pfile);
  *size = s;
}

/// @brief Evaluates the provided BF program & prints its output to stdout.
/// @param prog BF program to evaluate
/// @param len BF program size
void evaluate(char *prog, size_t len) {
  // Initialize the memory & its pointers
  char memory[MEMORY_SIZE];
  size_t MC, PC, SS; // Memory Cell, Program Counter, Stack Size

  // Go through the program
  while (PC < len) {
    // Identify the current token
    switch (prog[PC]) {
    case '+':
      // Increase the memory cell content
      memory[MC]++;
      break;

    case '-':
      // Decrease the memory cell content
      memory[MC]--;
      break;

    case '<':
      // Stay within the memory bounds
      if (!MC)
        errx(1, "Out-of-memory access!");

      // Move the memory pointer
      MC--;
      break;

    case '>':
      // Stay within the memory bounds
      if (MC == MEMORY_SIZE - 1)
        errx(1, "Out-of-memory access!");

      // Move the memory pointer
      MC++;
      break;

    case '[':
      // Skip the loop if the memory cell is empty (loop finished)
      if (!memory[MC]) {
        PC++; // Go to the closing bracket

        // Find the closing bracket
        while (SS > 0 || prog[PC] != ']') {
          if (prog[PC] == '[')
            SS++;
          if (prog[PC] == ']')
            SS--;
          PC++;
        }
      }

      break;

    case ']':
      PC--; // Go back to the closing bracket

      // Find the opening bracket
      while (SS > 0 || prog[PC] != '[') {
        if (prog[PC] == '[')
          SS--;
        if (prog[PC] == ']')
          SS++;
        PC--;
      }

      PC--; // Go back to the opening bracket
      break;

    case '.':
      // Forced to use putchar so that the output is not buffered
      putchar(memory[MC]);
      break;

    case ',':
      // Retrieve the entered character (without buffering)
      memory[MC] = getchar();
      break;

    case ' ':
    case '\t':
    case '\n':
      // Characters chosen as empty tokens (to skip, not detected as errors)
      break;

    default:
      // Any other character is considered an error
      errx(1, "Unexpected token detected!");
      break;
    }

    // Increase the program counter
    PC++;
  }

  // Detect any missmatched brackets
  if (SS)
    errx(1, "Missmatched brackets detected!");

  // Print the final \n character
  putchar(10);
}

int main(int argc, char **argv) {
  // Initialize the program size & its output
  size_t size = 0;
  char *program = malloc(MEMORY_SIZE * sizeof(char));

  // Retrieve the program
  get_program(argv[1], program, &size);

  // Print the program & its output
  printf("size: %zu\n", size);
  printf("%s", program);

  // Evaluate the program
  evaluate(program, size);
  return 0;
}