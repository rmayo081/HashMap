/**
 * @file input.h
 * @author your name (you@domain.com)
 * Central header file, contains prototype functions for input.c, and all nessacary includes and macros for input.c
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef INPUT_H
#define INPUT_H

/**
 * The number of characters allowed in a name or assignment.
 */
#define NAME_LENGTH 15
/**
 * The number of characters required in an id
 */
#define ID_LENGTH 4
/**
 * Initial capacity of the dynamically allocated array of characters used in readLine.
 */
#define INITIAL_CAP 40

/**
 * Reads a line from a file by dyanimcally allocating space for it.
 * The function caller is responsible for freeing the returned pointer.
 * @param fp the open file stream
 * @return The line string as a pointer to heap memory, or NULL if the given stream has hit EOF
 */
char *readLine(FILE *fp);

#endif
