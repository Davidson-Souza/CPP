// The MIT License (MIT)

// Copyright (c) 2022 Davidson Souza

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

/**
 * This is a small implementation of the RSA encryption system in C, it is **not secure**, since
 * keys are small and there is no safety regards. As everything in this repository, this codebase is 
 * only for learning reasons, if you really want to use RSA, there is a bunch of good tools for that.
 * 
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef long long val_t;
typedef __uint128_t u128_t;

//A few primes for a first primarity test
const unsigned int first_primes[] = {
                    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                    31, 37, 41, 43, 47, 53, 59, 61, 67,
                    71, 73, 79, 83, 89, 97, 101, 103,
                    107, 109, 113, 127, 131, 137, 139,
                    149, 151, 157, 163, 167, 173, 179,
                    181, 191, 193, 197, 199, 211, 223,
                    227, 229, 233, 239, 241, 251, 257,
                    263, 269, 271, 277, 281, 283, 293,
                    307, 311, 313, 317, 331, 337, 347, 349
                  };

#define CHECK(X) if (x.res != ok) return;
typedef enum {
  OK,
  INVALID_LENGTH,
  UNKNOW
} results;

typedef struct {
  val_t p;
  val_t q;
  val_t d;
} private_key;

typedef struct {
  val_t e;
  val_t n;
} public_key;

typedef struct {
  val_t c[100];
} cyphertext;

typedef struct {
  val_t m[100];
} plaintext;

typedef struct {
  results res;
  plaintext text;
} result_t;

// C function for extended Euclidean Algorithm
val_t extended_euclidean_algorithm(val_t a, val_t b, val_t* x, val_t* y) {
    // Base Case
  if (a == 0) {
    *x = 0, *y = 1;
    return b;
  }
 
  val_t x1, y1; // To store results of recursive call
  val_t gcd = extended_euclidean_algorithm(b % a, a, &x1, &y1);
 
  // Update x and y using results of recursive
  // call
  *x = y1 - (b / a) * x1;
  *y = x1;
 
  return gcd;
}
val_t mod(val_t a, val_t b) {
  val_t r = a % b;
  return r < 0 ? r + b : r;
}

// Function to find modulo inverse of a
val_t mod_inv(val_t a, val_t m) {
  val_t x, y;
  val_t g = extended_euclidean_algorithm(a, m, &x, &y);

  val_t res = mod(x, m);

  return res;
}
//A lightweight primarity test, test against a few know primes to see if
//any divides our number
int first_test(val_t a) {
  for (unsigned int i = 0; i < 70; ++i) {
    if (a % first_primes[i] == 0) return 0;
  }
  return 1;
}

// Utility function to do modular exponentiation.
// It returns (x^y) % p
val_t mod_pow(val_t x, val_t y, val_t p) {
	val_t res = 1;	 // Initialize result
	x = x % p; // Update x if it is more than or
				// equal to p
	while (y > 0) {
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res*x) % p;

		// y must be even now
		y = y >> 1; // y = y/2
		x = (x*x) % p;
	}
	return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that d*2<sup>r</sup> = n-1
// for some r >= 1
int miillerTest(int d, int n) {
	// Pick a random number in [2..n-2]
	// Corner cases make sure that n > 4
	int a = 2 + rand() % (n - 4);

	// Compute a^d % n
	int x = mod_pow(a, d, n);

	if (x == 1 || x == n-1)
	return 1;

	// Keep squaring x while one of the following doesn't
	// happen
	// (i) d does not reach n-1
	// (ii) (x^2) % n is not 1
	// (iii) (x^2) % n is not n-1
	while (d != n-1) {
		x = (x * x) % n;
		d *= 2;

		if (x == 1)	 return 0;
		if (x == n-1) return 1;
	}

	// Return composite
	return 0;
}

// It returns false if n is composite and returns true if n
// is probably prime. k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
int seccond_test(val_t n, val_t k) {
	// Corner cases
	if (n <= 1 || n == 4) return 0;
	if (n <= 3) return 1;

	// Find r such that n = 2^d * r + 1 for some r >= 1
	val_t d = n - 1;
	while (d % 2 == 0)
		d /= 2;

	// Iterate given number of 'k' times
	for (int i = 0; i < k; i++)
		if (!miillerTest(d, n))
			return 0;

	return 1;
}

//Generate a prime number. This prime is VERY SMALL, not even close to
//cryptographically secure.
val_t generate_prime() {
  while(1) {
    val_t candidate = rand() &0x007FFFFF;
    if (!first_test(candidate)) continue; //Composite, do nothing
    if (seccond_test(candidate, 20)) return candidate;
  }
}

//Make a * b mod(p)
val_t mod_mult(val_t a, val_t b, val_t mod) {
  return ((a * b) % mod);
}
//A private key in RSA consists of 2 primes p and q
//and a number d that will be calculated afterwards, because
//depends on choosen exponent.
private_key rsa_generate_private_key(int seed) {
  private_key priv = {
    .d = 0,
    .p = generate_prime(),
    .q = 255,
  };
  return priv;
}

//Generates an RSA public key from a private one
public_key rsa_generate_public_key(private_key *priv) {
  public_key pub = {
    .e = 0,
    .n = 0
  };
  //The RSA modulus n = p * q
  pub.n = priv->p * priv->q;
  //rho = (p - 1)(q - 1)
  unsigned long long rho = (priv->p - 1) * (priv->q - 1);

  pub.e = (1 << 16) + 1;  //Exponent is always 2^16

  //d is a integer such that ed = 1 (mod rho), and is used for decryption
  priv->d = mod_inv(pub.e, rho);
  return pub;
}
//Encrypt some data using RSA's algorithm
cyphertext rsa_encrypt(plaintext plt, public_key pk) {
  cyphertext cpr;
  for (unsigned int i = 0; i < 100; ++i) {
    cpr.c[i] = mod_pow(plt.m[i], pk.e, pk.n);
  }

  return cpr;
}
//Decrypt some data using RSA's algorithm
plaintext rsa_decrypt(cyphertext cpr, private_key *priv, val_t n) {
  plaintext plt;
  for (unsigned int i = 0; i < 100; ++i) {
    plt.m[i] = mod_pow(cpr.c[i], priv->d, n);
  }
  return plt;
}

result_t rsa_make_plain_text(const char *msg, size_t len) {
  result_t res = {
    .res = UNKNOW,
    .text = {
      .m = {0}
    }
  };
  if (len <= 0 || len >= 100) {
    res.res = INVALID_LENGTH;
  };

  for(int i = 0; i < len; i += 2)
    res.text.m[i] =  msg[i] << 16 | msg[i + 1];
  res.res = res.res == UNKNOW? OK: res.res;
  return res;
}

void rsa_show_plain_text(const plaintext msg, const size_t len) {
  for (unsigned int i = 0; i < len; ++i)
    printf("%c%c", msg.m[i] >> 16, msg.m[i] & 0x000000ff);
}

void rsa_show_hex_cyphertext(const cyphertext msg) {
  for (unsigned int i = 0; i < 100; ++i)
    printf("%04x", msg.c[i]);
}

int main() {
  printf("================= RSA Ecrypt ===================\n");
  printf("==> Enter a message: ");
  char message[100] = {0}, *ptr = message;

  while(*ptr != '\n') {
    scanf("%c", ++ptr);
  }

  private_key p = rsa_generate_private_key(0);
  public_key pk = rsa_generate_public_key(&p);
  
  plaintext txt = rsa_make_plain_text(message, 100).text;

  printf("==> Plaintext: %s\n", message);
  cyphertext cypher = rsa_encrypt(txt, pk);

  printf("==> Cyphertext: ");
  rsa_show_hex_cyphertext(cypher);

  printf("\n==> Plaintext after RSA: ");
  plaintext new_text = rsa_decrypt(cypher, &p, pk.n);
  rsa_show_plain_text(new_text, 100);

  printf("\n================= RSA Ecrypt ===================\n");

}
