/**
 * @file main.c
 * @author Simone Cosimo (s303333@studenti.polito.it)
 * @brief studenti.polito.it
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 * Write a program in C that, using the OpenSSL library, generates two 128 bit random strings. 
 * Then, it XOR them (bitwise) and prints the result on the standard output as an hex string.
 * 
 */

#include <stdio.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#define MAX 128

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {

    unsigned char string1[MAX];
    unsigned char string2[MAX];
    unsigned char xored[MAX];

    if(RAND_load_file("/dev/random", 64) != 64)
        handle_errors();

    // Generating string1
    if(RAND_bytes(string1, MAX) != 1)
        handle_errors();

    // Generating string2
    if(RAND_bytes(string2, MAX) != 1)
        handle_errors();

    // printf("String1: %02x - String2: %02x \n", string1[0], string2[0]);

    // xoring the strings and printing the result
    printf("string1 xor string2: ");
    for(int i = 0; i < MAX; i++) {
        xored[i] = string1[i] ^ string2[i];
        printf("%02x ", xored[i]);
    }

    return 0;
}