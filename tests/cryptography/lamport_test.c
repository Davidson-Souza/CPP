#include "cryptography/lamport.c"

int main()
{
    FILE *arq;
    unsigned char priv_key[512][32], pub_key[512][32], sig[256][32] = {0};
    struct sha_ctx ctx;
    int fVerified;

    // Generating a private key
    gen_priv_key(ctx, "123", priv_key);
    printf("Printing the private key: \n");
    arq = fopen("priv", "w");
    for(unsigned register int i = 0; i<512; i++)
    {
        for(unsigned register int j = 0; j<32; j++)
            fprintf(arq, "%02x", priv_key[i][j]);
        fprintf(arq, "\n");
    }
    fclose(arq);

    // Derivating a public one from the private key
    printf("Deriving a public key...\n");
    derive_key(ctx, priv_key, pub_key);
    arq = fopen("pub", "w");
    for(unsigned register int i = 0; i<512; i++)
    {
        for(unsigned register int j = 0; j<32; j++)
            fprintf(arq, "%02x", pub_key[i][j]);
        fprintf(arq, "\n");
    }
    fclose(arq);

    // Sign to a message
    printf("Signing...\n");
    sign(ctx, priv_key, "u", (unsigned char **)sig);
    arq = fopen("sig", "w");
    for(unsigned register int i = 0; i<256; i++)
    {
        for(unsigned register int j = 0; j<32; j++)
            fprintf(arq, "%02x", priv_key[i][j]);
        fprintf(arq, "\n");
    }
    fclose(arq);

    // Verify the signature
    verify(ctx, "u", pub_key, (unsigned char **)sig, &fVerified);
    printf("The sig %s valid\n", fVerified?"is": "is not");
}
