/**
 * @file main.c 
 * @author Simone Cosimo (simosx4@gmail.com)
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 * Writes a program in C that, using the OpenSSL library, computes the hash of the content of a file, 
 * passed as first parameter from the command line, using the algorithm passed as second parameter.
 * HINT: check the EVP_get_digestbyname function or the EVP_MD_fetch 
 * if you are using OpenSSL 3.0+ https://www.openssl.org/docs/man3.0/man7/crypto.html).
 * 
 */

#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define MAXBUF 1024

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int main(int argc, char** argv) {

    if(argc != 3) {
        printf("Wrong usage: specify filename and algorithm to be used\n");
        exit(-1);
    }

    FILE *f;
    if((f = fopen(argv[1], "r")) == NULL) {
        printf("Could not open file %s\n", argv[1]);
        exit(-1);
    }

    // load strings and add algorithms for the openssl libraries
    ERR_load_CRYPTO_strings();
    OpenSSL_add_all_algorithms();

    // declare and create new context (MD as Message Digest) -- TO BE FREED AT THE END
    EVP_MD_CTX *md = EVP_MD_CTX_new();

    // init context
    const EVP_MD *alg = EVP_get_digestbyname(argv[2]);
    if(alg == NULL) 
        handle_errors();

    if(!EVP_DigestInit(md, alg)) 
        handle_errors();

    // update digest passing context, data and length
    int n_read;
    unsigned char buffer[MAXBUF];
    while((n_read = fread(buffer, 1, MAXBUF, f)) > 0) {
        // i need to pass the actual byte read, so n_read
        // the restult from the fread 
        if(!EVP_DigestUpdate(md, buffer, n_read))
            handle_errors();
    }

    // finalize context, generated hash and len
    unsigned char md_value[EVP_MD_size(EVP_sha256())];
    int md_len;

    if(!EVP_DigestFinal(md, md_value, &md_len))
        handle_errors();

    EVP_MD_CTX_free(md);

    printf("Digest is: ");
    for(int i = 0; i < md_len; i++) 
        printf("%02x", md_value[i]);
    printf("\n");

    // freeing strings and algo added at the beginning
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();

    return 0;
}