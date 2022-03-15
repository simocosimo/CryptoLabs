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

// 32 bit numbers
#define MAX 4

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {

    unsigned char num1[MAX];
    unsigned char num2[MAX];

    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int res = 0;
    unsigned int res2 = 0;

    // the base of the mod operation
    unsigned long base = (1UL << (MAX * 8));

    if(RAND_load_file("/dev/random", 64) != 64)
        handle_errors();

    // Generating the two numbers
    if(RAND_bytes(num1, MAX) != 1)
        handle_errors();

    if(RAND_bytes(num2, MAX) != 1)
        handle_errors();

    // printing the two numbers in hex
    printf("(hex)\na: ");
    for(int i = 0; i < MAX; i++) printf("%02x", num1[i]);
    printf("\tb: ");
    for(int i = 0; i < MAX; i++) printf("%02x", num2[i]);
    
    // building the int number from previous generated sequences
    for(int i = 0; i < MAX; i++) {
        a += (unsigned int)(num1[i] << ((MAX - 1 - i) * 8));
        b += (unsigned int)(num2[i] << ((MAX - 1 - i) * 8));
    }

    // printing the int numbers converted
    printf("\n(int)\na: %lu\tb: %lu", a, b);

    // calculating and printing the result
    res = (a * b) % base;
    res2 = (a % base) * (b % base);
    printf("\n\n(a*b) mod 2^32\nres1: %u (mod 2^32)", res);
    printf("\n(a mod 2^32) * (b mod 2^32)\nres2: %u (mod 2^32)", res2);

    return 0;
}