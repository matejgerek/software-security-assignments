#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Computes the hash value of a given string.
 *
 * This function uses the djb2 hash algorithm to compute the hash value of
 * the given string. The hash value is an unsigned long integer that can be
 * used to uniquely identify the input string.
 *
 * @param str The string to hash.
 *
 * @return The hash value of the input string.
 */
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}



int main(void) {
    char *password = "mypassword";
    unsigned long hashed_password = hash(password);

    printf("%lu", hashed_password);

    return 0;
}
