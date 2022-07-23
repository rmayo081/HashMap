/**
    @file integer.c
    @author CSC 230
    Implementation of the Integer VType.
*/

#include "integer.h"
#include <stdlib.h>
#include <stdio.h>

/** print method for Integer.
 * @param v By convention, this parameter should be the same VType pointer that was used to call this function
 */
static void print(VType const *v)
{
    // Convert the VType pointer to a more specific type.
    Integer const *this = (Integer const *)v;
    printf("%d", this->val);
}

/** equals method for Integer.
 * @param a By convention, this parameter should be the same VType pointer that was used to call this function
 * @param b A pointer to another VType to compare to.
 */
static bool equals(VType const *a, VType const *b)
{
    // Make sure the b object is also an Integer.
    // (i.e., it uses the same print funtion)
    if (b->print != print)
        return false;

    // Compare the val fields inside a and b.
    Integer const *this = (Integer const *)a;
    Integer const *that = (Integer const *)b;

    return this->val == that->val;
}

/** hash method for Integer.  It hashes to the int value it contains,
 * with negative values overflowing to positive. 
 * @param v By convention, this parameter should be the same VType pointer that was used to call this function
 */
static unsigned int hash(VType const *v)
{
    // Convert the VType pointer to a more specific type.
    Integer const *this = (Integer const *)v;
    // This will overflow negative values to large positive ones.
    return this->val;
}

/** destroy method for Integer.
 * @param v By convention, this parameter should be the same VType pointer that was used to call this function
 */
static void destroy(VType *v)
{
    // Integer is just one block of heap memory.
    free(v);
}

VType *parseInteger(char const *init, int *n)
{
    // Make sure the string is in the right format.
    int val, len;
    if (sscanf(init, "%d%n", &val, &len) != 1)
    {
        return NULL;
    }

    // Fill in the end pointer, if the caller asked for it.
    if (n)
        *n = len;

    // Allocate an Integer on the heap and fill in its fields.
    Integer *this = (Integer *)malloc(sizeof(Integer));
    this->val = val;
    this->print = print;
    this->equals = equals;
    this->hash = hash;
    this->destroy = destroy;

    // Return it as a poitner to the superclass.
    return (VType *)this;
}
