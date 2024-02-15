// C standard heders
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// Project headers
#include <DC/stream_info.h>
// Internal headers
#include <fileio.h>

#define BINARY_READ  "rb"

ByteStream io_load_bytes(const char *path) {
    FILE *target = fopen(path, BINARY_READ);
    if(target == NULL) return EMPTY_BYTE_STREAM;
    fprintf(stderr, "Got here\n");
    fseek(target, 0, SEEK_END);

    ByteStream out;
    out.size = ftell(target);
    fseek(target, 0, SEEK_SET);

    out.bytes = malloc(out.size);
    if(out.bytes == NULL) {
        errno = ENOMEM;
        out = EMPTY_BYTE_STREAM;
    }
    else
        fread(out.bytes, out.size, 1, target); // Check fread fail
    fclose(target);
    return out;
}

void io_free_bytes(ByteStream *b) {
    free(b->bytes);
    b->bytes = NULL;
    b->size = 0;
}