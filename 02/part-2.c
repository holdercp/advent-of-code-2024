#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define SAFE_JUMP 3
#define MAX_LEVELS_PER_LINE 8
#define MAX_LINE_BYTES 25

int parse_line_to_record(const char *line, int record[MAX_LEVELS_PER_LINE])
{
    int len = 0;
    int cursor = 0;
    int digits_scanned;
    int level;

    while (len < MAX_LEVELS_PER_LINE &&
           sscanf(line + cursor, "%d%n", &level, &digits_scanned) == 1)
    {
        record[len++] = level;
        cursor += digits_scanned + 1; // move forward the number of digits in the level + the space separator
    }

    return len;
}

int count_violations(int *record, int record_len)
{
    int violations = 0;
    char dir = 'u';

    for (size_t i = 1; i < record_len; i++)
    {
        if (dir == 'u') // If this is the first pass we determine the direction
        {
            if (record[i] < record[i - 1])
                dir = 'd';
            else if (record[i] > record[i - 1])
                dir = 'i';
        }

        if ((abs(record[i] - record[i - 1]) > SAFE_JUMP) || (record[i] == record[i - 1]) || (record[i] > record[i - 1] && dir == 'd') || (record[i] < record[i - 1] && dir == 'i'))
        {
            violations++;
        }
    }

    return violations;
}

int is_record_safe(int record[MAX_LEVELS_PER_LINE], int record_len)
{
    int violations = count_violations(record, record_len);
    if (violations == 0)
        return 1;

    // If we have violationa, remove each element and check if one permutation has no violations
    for (int i = 0; i < record_len; i++)
    {
        int temp = record[i];
        // Shift elements to fill the gap
        for (size_t j = i; j < record_len - 1; j++)
        {
            record[j] = record[j + 1];
        }

        violations = count_violations(record, record_len - 1);

        // Restore the record
        for (size_t j = record_len - 1; j > i; j--)
        {
            record[j] = record[j - 1];
        }
        record[i] = temp;

        if (violations == 0)
            return 1;
    }

    return 0;
}

int main()
{
    FILE *input = fopen("input.txt", "r");
    if (!input)
        return 1;

    char line[MAX_LINE_BYTES];
    int record[MAX_LEVELS_PER_LINE];
    int safe_count = 0;

    while (fgets(line, sizeof(line), input))
    {
        int record_len = parse_line_to_record(line, record);
        if (is_record_safe(record, record_len))
        {
            safe_count++;
        }
    }

    fclose(input);

    printf("%d\n", safe_count);
    return 0;
}
