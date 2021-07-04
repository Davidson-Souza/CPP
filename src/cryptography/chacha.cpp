#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <stdio.h>
// 0010 0000 0000 0000 0000 0010 0000 0000
// 0000 0000 0000 0001 0000 0000 0001 0000
// 

// 0001 
// 0101
// ----
// 0100
#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b,  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b,  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))
#define ROUNDS 20
 
void chacha_block(uint32_t out[16], uint32_t const in[16])
{
	int i;
	uint32_t x[16];

	for (i = 0; i < 16; ++i)	
		x[i] = in[i];
	// 10 loops × 2 rounds/loop = 20 rounds
	for (i = 0; i < ROUNDS; i += 2) {
		// Odd round
		QR(x[0], x[4], x[ 8], x[12]); // column 0
		QR(x[1], x[5], x[ 9], x[13]); // column 1
		QR(x[2], x[6], x[10], x[14]); // column 2
		QR(x[3], x[7], x[11], x[15]); // column 3
		// Even round
		QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
		QR(x[1], x[6], x[11], x[12]); // diagonal 2
		QR(x[2], x[7], x[ 8], x[13]); // diagonal 3
		QR(x[3], x[4], x[ 9], x[14]); // diagonal 4
	}
	for (i = 0; i < 16; ++i)
		out[i] = x[i] + in[i];
}

void chacha(char *cipherText, const char *rawText, const size_t inSize, const char key[32])
{
    const char constantWords[] = "expand 32-byte k";
    uint64_t pos, nonce;
    uint32_t *input = new uint32_t[16];
    uint32_t *output = new uint32_t[16];
    uint32_t *block = new uint32_t[16];
    nonce = 9;

    for (pos = 0; pos <= (int) inSize/(16 * sizeof(uint32_t)); pos++)
    {        
        memset(input, 0, 16*sizeof(uint32_t));
        memcpy(input, constantWords, 4*sizeof(uint32_t));
        memcpy(input + 4*sizeof(uint32_t), key, 32);
        memcpy(input + 12*sizeof(uint32_t), &pos, sizeof(uint64_t));
        memcpy(input + 14*sizeof(uint32_t), &nonce, sizeof(uint64_t));

        chacha_block(output, input);
        
        memcpy(block, rawText + (16*sizeof(uint32_t) * pos), 16*sizeof(uint32_t));
        

        for(unsigned register int i = 0; i<16; i++)
            block[i] = output[i] ^ block[i];

        memcpy(cipherText + (16 * sizeof(uint32_t) * pos), block, inSize);
    }
}

int main()
{
    /*std::string input;
    std::cin >> input;
    const uint8_t size = input.size();
    char *cipherText =(char *) malloc(size);
    memset(cipherText, 0, size);

    chacha(cipherText, input.c_str(), size, key);
    for(unsigned register int i = 0; i < size; i++)
        printf("%02x", cipherText[i]);
    
    const char key[] = "Correct horse battery staple   ";

    unsigned char txtPre[] = {0x05, 0xdc, 0x8c, 0xc6, 0xd3};
    char txt[5];
    memcpy(txt, txtPre, 5);
    for(unsigned register int i = 0; i < 5; i++)
        printf("%c", txt[i]);
    chacha(txt, txt, 5, key);
    printf("\n");

    for(unsigned register int i = 0; i < 5; i++)
        printf("%c", txt[i]);
    
    printf("\n");*/
    // a = 5(00000101), b = 9(00001001) 
    unsigned char a = 5, b = 9; 
  
    // The result is 00000001 
    printf("a = %d, b = %d\n", a, b); 
    printf("a&b = %d\n", a & b); 
  
    // The result is 00001101 
    printf("a|b = %d\n", a | b); 
  
    // The result is 00001100 
    printf("a^b = %d\n", a ^ b); 
  
    // The result is 11111010 
    printf("~a = %d\n", a = ~a); 
  
    // The result is 00010010 
    printf("b<<1 = %d\n", b << 1); 
  
    // The result is 00000100 
    printf("b>>1 = %d\n", b >> 1); 
  
    return 0; 
}