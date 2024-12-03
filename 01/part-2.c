#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"
#define LOCATION_PAIRS 1000

int main() {
  int score = 0;
  int l[LOCATION_PAIRS], r[LOCATION_PAIRS];
  int counts[99999] = {0};

  FILE *input = fopen(INPUT_FILE, "r");
  if (input == NULL) {
    printf("Error: '%s' not found\n", INPUT_FILE);
    return 1;
  }

  // Parse input into two arrays of ints
  for (size_t i = 0; i < LOCATION_PAIRS; i++) {
    fscanf(input, "%d   %d\n", &l[i], &r[i]);
  }

  fclose(input);

  // Create count lookup for the locations in the right array
  for (size_t i = 0; i < LOCATION_PAIRS; i++) {
    counts[r[i]] += 1;
  }

  // Calculate the score
  for (size_t i = 0; i < LOCATION_PAIRS; i++) {
    int loc = l[i];
    int count = counts[loc];
    score += loc * count;
  }

  printf("%d\n", score);

  return 0;
}
