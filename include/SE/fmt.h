#ifndef DC_FMT_H
#define DC_FMT_H

#include "result.h"
#include "stream_info.h"

// File formats
#define FMTS \
    X(WAV)

// Enum format
#define FMT(_name) _name ## _FMT

typedef enum {
    FMT(INVALID)=-2,
    FMT(AUTO),
    #define X(_name) FMT(_name),
    FMTS
    #undef X
} AudioFormat;

Result *se_load_file(const char *path, AudioFormat fmt, SoundStream **newSound);
Result *se_load_from_mem(ByteStream *in, AudioFormat userFmt, SoundStream **newSound);

#endif