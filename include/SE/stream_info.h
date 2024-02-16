#ifndef DC_STREAM_INFO_H
#define DC_STREAM_INFO_H

#include <stddef.h>

typedef unsigned char Byte;

typedef struct ByteStream {
    Byte *bytes;
    size_t size;
} ByteStream;

typedef struct SoundStream {
    int channels;
    int sampleRate;
} SoundStream;

extern const ByteStream EMPTY_BYTE_STREAM;

#endif