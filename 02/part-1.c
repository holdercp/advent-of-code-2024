/*
Goal: Find the number of "safe" reports
- Parse the input line by line
- For each line, go char by char
  - Compare the current char with the previous char
  - If they are increasing or decresing and within the threshold of three,
continue
  - If they switch directions or are more than three apart, break
  - When a newline is reached, increment the safe reports counter
*/

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"
#define SAFE_JUMP 3

int main()
{
  int safe_reports = 0;
  int i = 0;
  int unsafe = 0;
  int level;
  int prev_level;
  char sep;
  char dir = '\0';

  FILE *input = fopen(INPUT_FILE, "r");
  if (input == NULL)
  {
    printf("Error: '%s' not found\n", INPUT_FILE);
    return 1;
  }

  while (fscanf(input, "%d%c", &level, &sep) == 2)
  {
    // We're past the first level
    if (i && !unsafe)
    {
      if (abs(level - prev_level) > SAFE_JUMP || level == prev_level)
      {
        unsafe = 1;
      }

      // We're on the second level, so determine the direction
      if (i == 1)
      {
        if (prev_level < level)
        {
          dir = 'i';
        }
        else if (prev_level > level)
        {
          dir = 'd';
        }
      }
      else if ((dir == 'i' && prev_level > level) ||
               (dir == 'd' && prev_level < level))
      {
        unsafe = 1;
      }
    }

    i++;
    prev_level = level;

    // We're at the end of the line so reset
    if (sep == '\n')
    {
      if (!unsafe)
      {
        safe_reports++;
      }

      dir = '\0';
      i = 0;
      unsafe = 0;
    }
  }

  fclose(input);

  printf("%d\n", safe_reports);

  return 0;
}
