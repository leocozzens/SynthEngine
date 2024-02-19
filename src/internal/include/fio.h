#ifndef SE_FIO_H
#define SE_FIO_H

// Forward declarations
struct Result;
struct ByteStream;

struct Result fio_load_bytes(const char *path, struct ByteStream **newBytes);
void fio_free_bytes(struct ByteStream **b);

#endif