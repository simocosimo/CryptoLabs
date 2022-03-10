/**
 * @file main.c
 * @author Simone Cosimo (s303333@studenti.polito.it)
 * @brief studenti.polito.it
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 * Writes a program in C that, using the OpenSSL library, generates randomly the private key 
 * to be used for encrypting data with AES128 in CBC and the needed IV. 
 * Pay attention to select the proper PRNG.
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

    unsigned char key[MAX];
    unsigned char IV[MAX];

    if(RAND_load_file("/dev/random", 64) != 64)
        handle_errors();

    // Generating string1
    if(RAND_bytes(key, MAX) != 1)
        handle_errors();

    // Generating string2
    if(RAND_bytes(IV, MAX) != 1)
        handle_errors();

    // xoring the strings and printing the result
    for(int i = 0; i < MAX; i++) {
        
    }

    return 0;
}