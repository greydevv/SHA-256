#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

// int pass(char* s0, char* s1)
// {
//     while (*s0 != '\0' && *s1 != '\0')
//     {
//         if (*s0 != *s1)
//         {
//             return 1;
//         }
//         s0++;
//         s1++;
//     }
//     return 0;
// }

int main(int argc, const char* argv[])
{
    // char* vectors[] = {
    //     "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
    //     "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1",
    //     "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1",
    // };

    // char* inputs[] = {
    //     "abc",
    //     "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
    //     "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
    // };
    // sha256_ctx* ctx = malloc(sizeof *ctx);
    // // sha256_ctx ctx;
    // for (int i = 0; i < 3; i++)
    // {
    //     init_sha256(ctx);
    //     char buf[65];
    //     update_sha256(ctx, inputs[i], strlen(inputs[i]), buf);

    //     // printf("HASH: %s\n", buf);
    //     // int result = pass(buf, "ackjhbaskjhsr");
    //     // printf("%d\n", result);
    //     // printf("SUCCESS : %d\n", pass(buf, vectors[i]));
    //     // printf("SUCCESS : %d\n", memcmp(buf, vectors[i], 65));
    //     // printf("EXPECTED: %p\n", vectors[i]);
    //     // printf("EXPECTED: %s\n", vectors[i]);
    //     // printf("OUTPUT  : %s\n", buf);
    // }
    // free(ctx);

    // STACKOVERFLOW
    char* vectors[] = {
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
        "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1",
        "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1",
    };

    char* inputs[] = {
        "abc",
        "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
        "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
    };

    sha256_ctx* ctx = malloc(sizeof *ctx);
    for (int i = 0; i < 3; i++)
    {
        init_sha256(ctx);
        char buf[65];
        update_sha256(ctx, inputs[i], strlen(inputs[i]), buf);

        printf("SUCCESS : %d\n", memcmp(buf, vectors[i], 65));
        printf("EXPECTED: %s\n", vectors[i]);
        printf("OUTPUT  : %s\n", buf);
    }
    free(ctx);
}