#include <iostream>
#include <gmp.h>
using namespace std;

unsigned int dexp(unsigned int base, unsigned int exp, unsigned int mod) {
    // Precompute powers
    unsigned int powers[7]; // To store 35^1, 35^2, ..., 35^64 (mod mod)
    powers[0] = base % mod;       // 35^1 mod 83
    for (int i = 1; i < 7; i++) {
        powers[i] = (powers[i - 1] * powers[i - 1]) % mod; // Square the previous value
    }

    // Combine terms for 77 = 64 + 8 + 4 + 1
    unsigned long long result = 1;
    if (exp & 64) result = (result * powers[6]) % mod; // Add 35^64
    if (exp & 8) result = (result * powers[3]) % mod;  // Add 35^8
    if (exp & 4) result = (result * powers[2]) % mod;  // Add 35^4
    if (exp & 1) result = (result * powers[0]) % mod;  // Add 35^1

    return result;
}

int main() {
    //unsigned int base = 35, exp = 77, mod = 83;
    //cout << "(35^77) % 83 = " << dexp(base, exp, mod) << endl;
    //return 0;


}
