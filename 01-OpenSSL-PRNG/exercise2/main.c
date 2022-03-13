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

// AES128 so 128 bit key and 128 bit block size
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

    // Generating key with private PRNG
    if(RAND_priv_bytes(key, MAX) != 1)
        handle_errors();

    // Generating IV: Do I need private PRNG here?
    if(RAND_bytes(IV, MAX) != 1)
        handle_errors();

    // printing key and IV
    printf("Key: ");
    for(int i = 0; i < MAX; i++) {
        printf("%02x ", key[i]);
    }

    printf("\nIV: ");
    for(int i = 0; i < MAX; i++) {
        printf("%02x ", IV[i]);
    }

    return 0;
}