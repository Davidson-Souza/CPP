/**
 * @brief: This code implements a Feistel cypher using sha256 as the F funcion. Please
 * refer to Mike's explanations for more detais: https://www.youtube.com/watch?v=FGhj3CGxl8I&pp=ugMICgJwdBABGAE%3D
 * @author: Davidson Souza
 * @license: MIT
 * @date: November, 2021
*/
// This is my implementation of sha256, avaliable at: https://github.com/Davidson-Souza/CPP/blob/master/src/cryptography/sha2.c
// But it really don't metter which implementation is being used, just change the invocation code
#include "sha2.c"
#define ROUND(x)   getRoundKey(roundKey, key, x);\
                   FeistelRound(r, l, &sha, key);
/** 
 * @brief: Each block runs over multiple rounds until it's finnished
 * @param R: The Right side of the text, a 32-byte array
 * @param L: The Left side of the text, a 32-byte array
 * @param hash: This is a context to a sha256 element that must be allocated upfront
 * @param key: A key, this key isn't the main key, but a round key. An unsigned 20-byte array 
*/
void FeistelRound(char R[32], char L[32], struct sha_ctx *hash, unsigned char key[20]) {
  char r[32], l[32], inner[32 + 20];
  unsigned char digest[32];

  //Li+1 = Ri  
  memcpy(l, R, 32);
  // Computes F(R_i, K_i), witch is sha256(R_i, K_i)
  sha_init(hash);
  memcpy(inner, R, 32);
  memcpy(inner + 32, key, 20);
  sha_update(hash, (const unsigned char *)inner, 32 + 20);
  sha_finalize(hash, digest);
  // Ri+1 = Li ^ F(R_i, K_i), where ^ means xor, and K_i is the round key.
  for (unsigned int i = 0; i < 32; i++) {
    r[i] = L[i] ^ digest[i];
  }

  memcpy(L, l, 32);
  memcpy(R, r, 32);
}
/** 
 * @brief: This function computes a round function. Needs be improved
*/
void getRoundKey(char roundKey[20], unsigned char key[20], int round) {
  for (unsigned int i = 0; i < 20; i++)
    roundKey[i] ^= ((i << round) ^ key[i]);
}

/**
 * @brief: Works through a block, return it but encrypted 
 * @param in: A 64-byte array containing some data
 * @param out: Another 64-byte array, will grab the output
 * @param key: A 20-byte array with the encryption key
 */
void FeistelBlockEncrypt(char in[64], char out[64], unsigned char key[20]) {
  char r[32], l[32], roundKey[20] = {0};
  struct sha_ctx sha;
  memcpy(r, in, 32);
  memcpy(l, in + 32, 32);

  sha_init(&sha);

  // 20 rounds
  ROUND(0)  ROUND(1)  ROUND(2)  ROUND(3)  ROUND(4)
  ROUND(5)  ROUND(6)  ROUND(7)  ROUND(8)  ROUND(9)
  ROUND(10) ROUND(11) ROUND(12) ROUND(13) ROUND(14)
  ROUND(15) ROUND(16) ROUND(17) ROUND(18) ROUND(19)

  // At the end, swap R and L
  memcpy(out, l, 32);
  memcpy(out + 32, r, 32);
}
/**
 * @brief: The part of the API responsible for encrypting some block of data with arbitrary size
 * @param out: Where we must return the encrypted data, must be a valid pointer with proper space allocated
 * @param msg: The data we are trying to encrypt
 * @param key: The key for encryption
*/
void FeistelEncrypt(char *out, char *msg, size_t len, unsigned char key[20]) {
  char block[64];
  int blocks = (((len)/64));

  for (unsigned int i = 0; i <= blocks; i++) {
    // This is for padding, if a block isn't multiple of 64 bytes
    memset(block, 0, 64);
    if (i == blocks)
      memcpy(block, msg + (64 * i), (len % 64));
    else
      memcpy(block, msg + (64 * i), 64);
    FeistelBlockEncrypt(block, out + (64 * i), key);
  }
}
/**
 * @brief: The part of the API responsible for decrypting some block of data with arbitrary size
 * @param out: Where we must return the encrypted data, must be a valid pointer with proper space allocated
 * @param msg: The data we are trying to encrypt
 * @param key: The key for decryption
*/
// Though they have the same logically, decryption requires no padding,
// so it is different functions
void FeistelDecrypt(char *out, char *msg, size_t len, unsigned char key[20]) {
  char block[64];
  int blocks = (((len)/64));  //This assumes a block that have been padded BEFORE encryption

  for (unsigned int i = 0; i < blocks; i++) {
    memcpy(block, msg + (64 * i), 64);
    FeistelBlockEncrypt(block, out + (64 * i), key);
  }
}
#ifdef MAIN

int main() {
  char msg[] = "A purely peer-to-peer version of electronic cash would allow online \
payments to be sent directly from one party to another without going through a \
financial institution. Digital signatures provide part of the solution, but the main \
benefits are lost if a trusted third party is still required to prevent double-spending. \
We propose a solution to the double-spending problem using a peer-to-peer network. \
The network timestamps transactions by hashing them into an ongoing chain of \
hash-based proof-of-work, forming a record that cannot be changed without redoing \
the proof-of-work. The longest chain not only serves as proof of the sequence of \
events witnessed, but proof that it came from the largest pool of CPU power. As \
long as a majority of CPU power is controlled by nodes that are not cooperating to \
attack the network, they'll generate the longest chain and outpace attackers. The \
network itself requires minimal structure. Messages are broadcast on a best effort \
basis, and nodes can leave and rejoin the network at will, accepting the longest \
proof-of-work chain as proof of what happened while they were gone.";

  char passphrase[] = "correct horse battery staple";
  char out[3000] = {0}, key[20] = {0}, hashedPassphrase[32];

  struct sha_ctx hash;

  // get the private key from our passphrase
  sha_init(&hash);
  sha_update(&hash, passphrase, strlen(passphrase));
  sha_finalize(&hash, (unsigned char *)hashedPassphrase);
  memcpy(key, hashedPassphrase, 20);

  const int n = strlen(msg);
  const int len = n + (64 - (n % 64));

  // encrypt
  FeistelEncrypt(out, msg, n, key);

//  for (unsigned int i = 0; i < len; i++){
//    printf("%hhx", out[i]);
//  }
//  printf("\n");
  // decrypt
  char decOut[3000] = {0};
  FeistelDecrypt(decOut, out, len, key);

  printf("%s\n", decOut);
}

#endif