
#ifndef LAMPORT_H
#define LAMPORT_H
#include <stdio.h>
#include <math.h>
#ifndef SHA_2
#include <sha2.h>
#endif
#include <stdlib.h>

int gen_priv_key(struct sha_ctx ctx, const unsigned char *entropy, unsigned char priv_key[512][32]);
int verify(struct sha_ctx ctx, unsigned char *msg, unsigned char pub_key[512][32], unsigned char **sig, int *ret);
int sign(struct sha_ctx ctx, unsigned char priv_key[512][32], const unsigned char *msg, unsigned char **sig);
int derive_key(struct sha_ctx ctx, const unsigned char priv_key[512][32], unsigned char pub_key[512][32]);

#endif