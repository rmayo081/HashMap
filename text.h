/**
 * @file text.h
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 * Header file for the Text VType subclass.
 * Contains the struct declaration for the Text subclass and its function pointers.
 * 
 */

#include "vtype.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#ifndef TEXT_H
#define TEXT_H

/**Defines an initial capacity for a dynamic array of characters as ten.*/
#define INITIAL_TEXT_CAP 10

/** Subclass of VType for storing text. */
typedef struct {
  /** Inherited from VType */
  void (*print)( struct VTypeStruct const *v );

  /** Inherited from VType */
  bool (*equals)( struct VTypeStruct const *a,
                  struct VTypeStruct const *b );

  /** Inherited from VType */
  unsigned int (*hash)( struct VTypeStruct const *b );

  /** Inherited from VType */
  void (*destroy)( struct VTypeStruct *v );

  /** Value stored by this text. */
  char *val;

  /**Length of the text string in this VType*/
  int strLen;
} Text;

/**
 * Parses a given string by storing the substring between two quotation marks. Creates a VType with the resulting substring value.
 * 
 * @param str The string to be parsed
 * @param n A container for the number of characters read by parseText. Will only read characters until a second quotation mark is hit.
 * @return A heap memory pointer to the new VType instance, or NULL if a string could not be parsed.
 */
VType *parseText(const char *str, int *n);

#endif
