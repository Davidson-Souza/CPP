#ifndef LAMPORT_C
#define LAMPORT_C
#include "lamport.h"

int sign
(
    struct sha_ctx ctx,
    unsigned char priv_key[512][32],
    const unsigned char *msg,
    unsigned char **sig
)
{
    // Signing
    // First she hashes the message to a 256-bit hash sum. 
    unsigned char dgst[32] = {0};

    sha_init(&ctx);
    sha_update(&ctx, (char *) msg, strlen(msg));
    sha_finalize(&ctx, (char *)dgst);
    //Then, for each bit in the hash, based on the value of the bit, she picks one number
    // from the corresponding pairs of numbers that make up her private key 
    // (i.e., if the bit is 0, the first number is chosen, and if the bit is 1, the second
    // is chosen). 
    for(unsigned register int i = 0; i < 256; i++)
    {
        sig[i] = dgst[(int)i/8] & (0x01 << (i % 8)) ? priv_key[(2 * i)] : priv_key[(2 * i) + 1];
    }
}

int verify
(
    struct sha_ctx ctx,
    unsigned char *msg, 
    unsigned char pub_key[512][32], 
    unsigned char **sig, 
    int *fVerified
)
{
    unsigned char dgst[32];
    unsigned char *sig_ver[256] = {0};  

    sha_init(&ctx);
    sha_update(&ctx, (char *) msg, strlen(msg));
    sha_finalize(&ctx, (char *)dgst);

    // then he uses the bits in the hash sum to pick out 256 of the hashes in Alice's public key.
    for(unsigned register int i = 0; i < 256; i++)
    {
        sig_ver[i] = dgst[(int)i / 8] & (0x01 << (i % 8)) ? pub_key[(2 * i)] : pub_key[(2 * i) + 1];
        //dgst[(int)i/32] >>= 1;
    }
    // Then Bob hashes each of the 256 random numbers in Alice's signature
    unsigned char sig_ver_final[256][32] = {0};
    for(unsigned register int i = 0; i<256; i++)
    {
        sha_init(&ctx);
        sha_update(&ctx, (char *) sig[i], 32);
        sha_finalize(&ctx, sig_ver_final[i]);
    }
    
    *fVerified = 1;
    for(unsigned register int i = 0; i<256; i++)
    {
        for(unsigned register int j = 0; j<32; j++)
        {
            if(sig_ver[i][j] != sig_ver_final[i][j])
            {
                *fVerified = 0;
                return -1;
            }
        }
    }
}

int derive_key
(
    struct sha_ctx ctx,
    const unsigned char priv_key[512][32], 
    unsigned char pub_key[512][32]
)
{
    //To create the public key she hashes each of the 512 random numbers in the private key,
    // thus creating 512 hashes, each 256 bits in size.
    // (Also 128 Kbits in total.) These 512 numbers form her public key, which she will share
    // with the world. 
    for(unsigned register int i = 0; i<512; i++)
    {
        sha_init(&ctx);
        sha_update(&ctx, (char *) priv_key[i], 32);
        sha_finalize(&ctx, pub_key[i]);
    }
}

int gen_priv_key
(
    struct sha_ctx ctx, 
    const unsigned char *entropy, 
    unsigned char priv_key[512][32]
)
{
    //To create the private key Alice uses the random number generator to produce 256 pairs
    // of random numbers (2×256 numbers in total), each number being 256 bits in size,
    // that is, a total of 2×256×256 bits = 128 Kibit in total.
    // This is her private key and she will store it away in a secure place for later use. 

    //This script will create the keys in a deterministic way, using the prior key and the
    // index. The very first keypair is derived using *entropy* as an initiation vector.
    unsigned int i = 0;

    // Unroll the fist iteraction
    sha_init(&ctx);
    sha_update(&ctx, entropy, 32);
    sha_update(&ctx, (char *) &i, sizeof(int));
    sha_finalize(&ctx, priv_key[i]);
    i++;
    for(; i<512; i++)
    {
        sha_init(&ctx);
        sha_update(&ctx, priv_key[i - 1], 32);
        sha_update(&ctx, (char *) &i, sizeof(int));
        sha_finalize(&ctx, priv_key[i]);
    }
}

#endif