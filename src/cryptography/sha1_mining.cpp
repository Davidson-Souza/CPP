#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <math.h>
/**
 * This file is just a few tests on hashcash PoW, using SHA-1 (updating with SHA-2 is a todo, I guess)
*/
// I don't remember were this diff comes from, but a block's difficulty needs be lesser than this
// Notice that it's just the 64 first bytes, since we don't use the lending
#define MIN_DIFF 0x00000377ae000000

#define ROTL(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))
#define ROTR(value, bits) (((value) >> (bits)) | ((value) << (32 - (bits))))

#define T(i)\
            temp = (ROTL(a, 5) + f + e + k + w[i]);\
            e = d;  \
            d = c;  \
            c = ROTL(b, 30);\
            b = a;\
            a = temp;
// This is my dummy block, note that this block is more like a token, it don't contains a reference
// to the previous block, nor a set of txs
typedef struct Block
{
    int height;
    int nonce;
    time_t timestamp;
} block;
// SHA-1 stuff, see the specs for details
#define S(t) w[t] = ROTL(w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16], 1);
#define F1(i) f = (b & c) | ((~b) & d);k = 0x5A827999; T(i);
#define F2(i) f = b ^ c ^ d; k = 0x6ED9EBA1; T(i);
#define F3(i) f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; T(i);
#define F4(i) f = b ^ c ^ d; k = 0xCA62C1D6; T(i);

unsigned int h0 = 0x67452301;
unsigned int h1 = 0xEFCDAB89;
unsigned int h2 = 0x98BADCFE;
unsigned int h3 = 0x10325476;
unsigned int h4 = 0xC3D2E1F0;
unsigned int W[16] = {0x0};


unsigned int a = h0, b = h1, c = h2, d = h3, e = h4, f = 0, temp = 0, k = 0, i = 0;
unsigned int w[80];
unsigned long target = MIN_DIFF;
unsigned long hash;

Block& mine(unsigned int *blk, char *dgst)
{
while(1)
{
    memcpy(w, blk, 16 * sizeof(int));
    // unwrap booth message schedule and compression main loop, this avoids using costly operations
    // like jmps and comparations
    S(16) S(17) S(18) S(19)
    S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
    S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
    S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
    S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59) 
    S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69)
    S(70) S(71) S(72) S(73) S(74) S(75) S(76) S(77) S(78) S(79)

    F1(0 ) F1(1 ) F1(2 ) F1(3 ) F1(4 ) F1(5 ) F1(6 ) F1(7 ) F1(8 ) F1(9 )
    F1(10) F1(11) F1(12) F1(13) F1(14) F1(15) F1(16) F1(17) F1(18) F1(19)
    F2(20) F2(21) F2(22) F2(23) F2(24) F2(25) F2(26) F2(27) F2(28) F2(29)
    F2(30) F2(31) F2(32) F2(33) F2(34) F2(35) F2(36) F2(37) F2(38) F2(39)
    F3(40) F3(41) F3(42) F3(43) F3(44) F3(45) F3(46) F3(47) F3(48) F3(49)
    F3(50) F3(51) F3(52) F3(53) F3(54) F3(55) F3(56) F3(57) F3(58) F3(59)
    F4(60) F4(61) F4(62) F4(63) F4(64) F4(65) F4(66) F4(67) F4(68) F4(69)
    F4(70) F4(71) F4(72) F4(73) F4(74) F4(75) F4(76) F4(77) F4(78) F4(79)
    
    h0 = h0 + a;
    h1 = h1 + b;
    h2 = h2 + c;
    h3 = h3 + d;
    h4 = h4 + e;
    
    // This script only verifyes to the fist 64 bits of the sha-1
    hash = ((unsigned long)h0 << 32) | h1;
    
    if(hash <= target)
    {
        sprintf(dgst, "%08x%08x%08x%08x%08x", h0, h1, h2, h3, h4);
        return *((Block *) blk);
    }
    ((Block *)blk)->nonce++;    // is this memory safe? haha
}

}
#define BLOCK_SPAN 60 * 10


Block& createBlock(int height) 
{
    Block &blk = *(new Block);
    blk.height = height;
    blk.nonce = 0;
    blk.timestamp = time(NULL);
    return blk;
}
int main()
{
    int epochFirst = time(NULL), height = 0;
    auto blk = createBlock(height);
    
    // The size of the content is always this
    W[15] = sizeof(Block);

    char dgst[32] = {0};

    // Few nice info
    printf("Mining with %16lx diff\n", 0xFFFFFFFFFFFFFFFF/target);

loop:
    // Retarget after 2016 solutions, expected time between blocks is BLOCK_SPAN (10 min default).
    if((height % 2016) == 0 && height != 0) 
    {
        int actual = blk.timestamp - epochFirst;
        target *= actual;
        target /= BLOCK_SPAN * 2016;
        if(target > MIN_DIFF)
        {
            target = MIN_DIFF;
        }
        epochFirst = time(NULL);
        printf("Mining with %16lx diff - Timespan: %d - blk: %d - hashrate: %f h/s\n", MIN_DIFF/target, actual, i, (1/((float)target/0xFFFFFFFFFFFFFFFF))/BLOCK_SPAN);
    }
    // Copy the block data to the sha block, at this point, it's just a template and the nonce is 0
    // our goal is find the correct nonce.
    memcpy(W, &blk, sizeof(Block));

    // Roll the nonces until find a proper solution
    blk = mine(W, dgst);
    // Show what we have found
    printf("%04d %s %d\n", blk.height, dgst, blk.nonce);
    height++;
    blk = createBlock(height);
goto loop;

    return 0;

}
