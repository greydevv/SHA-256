#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "sha256.h"

static const word_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

void init_sha256(sha256_ctx* ctx)
{
    // memset(ctx->data, 0, sizeof ctx->data);
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
}

void update_sha256(sha256_ctx* ctx, const char* msg, size_t msglen, char* buf)
{
    for (int i = 0; i < msglen; i++)
    {
        ctx->data[ctx->datalen++] = msg[i];
        if (ctx->datalen == 64)
        {
            transform_sha256(ctx);
        }
    }
    // separate message and padding with a '1' bit
    ctx->data[ctx->datalen++] = 0x80;
    if (ctx->datalen > 56)
    {
        // current block will not be able to fit 64 bits on the end, so there needs to be another 512-bit block
        while (ctx->datalen < 64)
        {
            ctx->data[ctx->datalen++] = 0x00;
        }
        transform_sha256(ctx);
    }
    // pad the message up to 448 bits
    while (ctx->datalen < 56)
    {
        ctx->data[ctx->datalen++] = 0x00;
    }
    // here, 'ctx->data' is 448 bits long (56 bytes). This leaves 64 bits (8 bytes) for the message length
    // total length should now be 512 bits.
    uint64_t msgbitlen = msglen*8;
    for (int i = 0; i < 8; i++)
    {
        // replace the last 64 bits (8 bytes) with the length of the original message in bits
        ctx->data[63-i] = msgbitlen >> (i*8);
        ctx->datalen++;
    }

    transform_sha256(ctx);

    // convert words into their hexadecimal representation
    for (int i = 0; i < 8; i++)
    {
        buf += snprintf(buf, 9, "%08" PRIx32, ctx->state[i]);
    }
}

void transform_sha256(sha256_ctx* ctx)
{
    word_t chunks[64];
    int i,j;
    // i corresponds to the 'chunks' index
    // j corresponds to the 'ctx->data' index
    // elements of 'chunks' should be the first 16 words of 'ctx->data'
    for (i = 0, j = 0; i < 16; i++, j+=4)
    {
        // this is good
        chunks[i] = (ctx->data[j] << 24) | (ctx->data[j+1] << 16) | (ctx->data[j+2] << 8) | (ctx->data[j+3]);
    }
    for (; i < 64; i++)
    {
        chunks[i] = LSIGMA1(chunks[i-2]) + chunks[i-7] + LSIGMA0(chunks[i-15]) + chunks[i-16];
    }

    // state register compression
    word_t a = ctx->state[0];
    word_t b = ctx->state[1];
    word_t c = ctx->state[2];
    word_t d = ctx->state[3];
    word_t e = ctx->state[4];
    word_t f = ctx->state[5];
    word_t g = ctx->state[6];
    word_t h = ctx->state[7];

    for (int z = 0; z < 64; z++)
    {
        word_t t1 = USIGMA1(e) + CH(e, f, g) + h + K[z] + chunks[z];
        word_t t2 = USIGMA0(a) + MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;

    // increment bitlen to blocksize
    ctx->bitlen += 512;
    // reset for possibility of following 512-bit block
    ctx->datalen = 0;
}