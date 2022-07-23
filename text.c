/**
 * @file text.c
 * @author Ramon Mayo (rmmayo@ncsu.edu)
 *
 * Implementation of the functions declared in text.h
 * Functions define the VTpe superclass and Text subclass header, including printing, destruction, and hashing.
 *
 */

#include "text.h"
/**
 * Prints the contents of the val in the given VType as a string.
 * Assumes the given VType to be of subtype Text.
 * @param v the VType to be read from.
 */
static void print(VType const *v)
{
    Text const *this = (Text const *)v;
    char *str = this->val;
    int i = 0;
    putchar('\"');
    while(str[i]) {
        //Handle escape characters
        if(str[i] == '\\' && str[i + 1]) {
            if(str[i + 1] == '\\') {
                putchar('\\');
                i++;
            }
            else if(str[i + 1] == 't') {
                putchar('\t');
                i++;
            }
            else if(str[i + 1] == 'n') {
                putchar('\n');
                i++;
            }
            else if(str[i + 1] == '\"') {
                putchar('\"');
                i++;
            }
        }
        else
            putchar(str[i]);

        i++;
    }
    putchar('\"');
    
}

/**
 * Compares "this" Text VType with another Vtype.
 *
 * @param a VType pointer, by convention should be the same Text Vtype that was used to call this function.
 * @param b Another Vtype pointer to compare to.
 * @return true if the two Vtype parameters both use the same Text print function pointer, and are evaluated as equivalent by strcmp.
 * @return false otherwise.
 */
static bool equals(VType const *a, VType const *b)
{
    if (b->print != print) {
        return false;
    }

    Text const *this = (Text const *)a;
    Text const *that = (Text const *)b;

    return strcmp(this->val, that->val) == 0;
}

/**
 * Hash function to convert a Text subtype into a 32 bit integer.
 * Implemented based on the Jenkins 32-bit hash function defined on the Wikipedia page: https://en.wikipedia.org/wiki/Jenkins_hash_function
 * @param v By convention, this parameter should be the same VType pointer that was used to call this function
 * @return The hash of this Text subtype as a 32 bit integer.
 */
static unsigned int hash(VType const *v)
{
    unsigned int hash = 0;
    size_t i = 0;

    Text *key = (Text *)v;
    const char *value = key->val;

    int length = key->strLen;
    while (i != length) {
        hash += value[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

/**Frees the memory of the subtype*/
static void destroy(VType *v)
{

    Text *text = (Text *)v;
    free(text->val);

    free(v);
}

VType *parseText(const char *str, int *n)
{
    if (!str[0])
    {
        return NULL;
    }
    int len = 0;
    int cap = INITIAL_TEXT_CAP;
    char *s = (char *)malloc(cap * sizeof(char));
    int size = 0;
    

    int i = 0;

    while (str[len] != '\"')
    {
        len++;
        if (!str[len])
        {
            free(s);
            return NULL;
        }
    }

    len++;
    bool valid = true;
    while (valid)
    {
        if(str[len] == '\"' && str[len - 1] != '\\') {
            break;
        }

        if (!str[len])
        {
            free(s);
            return NULL;
        }

        if (size >= cap)
        {
            cap *= 2;
            s = (char *)realloc(s, cap * sizeof(char));
        }

        s[i++] = str[len++];
        size++;
    }
    s[i] = '\0';
    len++;

    if (n)
        *n = len;

    Text *this = (Text *)malloc(sizeof(Text));

    this->val = s;
    this->strLen = i;
    this->print = print;
    this->equals = equals;
    this->hash = hash;
    this->destroy = destroy;

    return (VType *)this;
}
