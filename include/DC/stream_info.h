#ifndef DC_STREAM_INFO_H
#define DC_STREAM_INFO_H

typedef unsigned char Byte;

typedef struct ByteStream {
    Byte *bytes;
    long size;
} ByteStream;

typedef struct SoundStream {
    int channels;
    int sampleRate;
} SoundStream;

extern const ByteStream EMPTY_BYTE_STREAM;

#endif