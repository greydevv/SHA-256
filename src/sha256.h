#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>

/* -------------------------------- TYPEDEFS -------------------------------- */

typedef uint8_t byte_t;
typedef uint32_t word_t;
typedef struct SHA256_CTX_STRUCT
{
    byte_t data[64];
    uint8_t datalen;
    uint64_t bitlen;
    word_t state[8];
} sha256_ctx;

/* ---------------------------- AUXILIARY MACROS ---------------------------- */

#define ROTR32(x, n) (((x >> n) | (x << (32-n))))
#define CH(x, y, z) ((e & f) ^ (~x & z))
#define MAJ(x, y, z) (((a & b) ^ (a & c)) ^ (b & c))
#define LSIGMA0(x) (ROTR32(x, 7) ^ ROTR32(x, 18) ^ (x >> 3))
#define LSIGMA1(x) (ROTR32(x, 17) ^ ROTR32(x, 19) ^ (x >> 10))
#define USIGMA0(x) (ROTR32(x, 2) ^ ROTR32(x, 13) ^ ROTR32(x, 22))
#define USIGMA1(x) (ROTR32(x, 6) ^ ROTR32(x, 11) ^ ROTR32(x, 25))

/* ------------------------------ FUNCTION DEFS ----------------------------- */

void init_sha256(sha256_ctx* ctx);
void update_sha256(sha256_ctx* ctx, const char* msg, uint64_t msglen, char* buf);
void transform_sha256(sha256_ctx* ctx);

#endif