#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "sha256.h"

#define NUM_TESTS 3

void test()
{
    const char *vectors[] = {
        "abc",
        "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
        "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
    };

    const char *outputs[] = {
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
        "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1",
        "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1",
    };

    int success = 1;
    char* buf = calloc(65, sizeof *buf);
    sha256_ctx* ctx = calloc(1, sizeof *ctx);
    for (int i = 0; i < NUM_TESTS; i++)
    {
        init_sha256(ctx);
        update_sha256(ctx, vectors[i], strlen(vectors[i]), buf);
        if (strcmp(buf, outputs[i]) != 0)
        {
            success = 1;
            printf("[ Failure ]\n  Expected: <%.64s>\n  Received: <%.64s>\n", outputs[i], buf);
        }
    }
    if (success)
    {
        printf("[ All Tests Passed ]\n");
    }
}

int main(int argc, const char* argv[])
{
    test();
}