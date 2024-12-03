#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"
#define LOCATION_PAIRS 1000

int sortasc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {
  int tot_distance = 0;
  int l[LOCATION_PAIRS], r[LOCATION_PAIRS];

  FILE *input = fopen(INPUT_FILE, "r");
  if (input == NULL) {
    printf("Error: '%s' not found\n", INPUT_FILE);
    return 1;
  }

  // Parse input into two arrays of ints
  for (size_t i = 0; i < LOCATION_PAIRS; i++) {
    fscanf(input, "%d   %d\n", &l[i], &r[i]);
  }

  // Sort the arrays
  qsort(l, LOCATION_PAIRS, sizeof(int), sortasc);
  qsort(r, LOCATION_PAIRS, sizeof(int), sortasc);

  // Sum the distance between each pair of locations
  for (size_t i = 0; i < LOCATION_PAIRS; i++) {
    tot_distance += abs(l[i] - r[i]);
  }

  printf("%d\n", tot_distance);

  return 0;
}
