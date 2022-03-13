/**
 * @file main.c
 * @author Simone Cosimo (s303333@studenti.polito.it)
 * @brief studenti.polito.it
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 * Using OpenSSL, generate two 32 bit integers (int), 
 * multiply them (modulo 2^32) and print the result.
 * 
 */

#include <stdio.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/bn.h>
#include <math.h>

// 32 bit numbers
#define MAX 32

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {

    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *r = BN_new();

    if(RAND_load_file("/dev/random", 64) != 64)
        handle_errors();

    // Generating 32 bit random numbers
    if(BN_rand(a, MAX, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY) != 1)
        handle_errors();

    if(BN_rand(b, MAX, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY) != 1)
        handle_errors();

    unsigned int res = ((unsigned int)a * (unsigned int)b) % (unsigned int)pow(2, 32);
    printf("a: %d - b: %d\nMoltiplication modulo 2^32: %u", a, b, res);

    return 0;
}