/**
 * @file input.c
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 * Implementation file for the input component.
 *
 */
#include "input.h"

char *readLine(FILE *fp)
{
    int cap = INITIAL_CAP;
    int len = 0;
    char *line = (char *)malloc(cap * sizeof(char));

    char cur = fgetc(fp);

    if (cur == EOF)
    {
        free(line);
        return NULL;
    }

    while (cur != '\n' && cur != EOF)
    {
        if (len >= cap)
        {
            cap = cap * 2;
            char *temp = (char *)realloc(line, cap * sizeof(char));
            if (NULL == temp)
            {
                free(temp);
            }
            else
            {
                line = temp;
            }
        }

        line[len++] = cur;

        cur = fgetc(fp);
    }
    line[len] = '\0';

    return line;
}
