#ifndef DC_FILEIO_H
#define DC_FILEIO_H

struct ByteStream;

struct ByteStream io_load_bytes(const char *path);
void io_free_bytes(struct ByteStream *b);

#endif