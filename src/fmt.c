// C standard headers
#include <string.h>
// Project headers
#include <DC/fmt.h>
// Internal headers
#include <fileio.h>
#include <serializer.h>

static AudioFormat determine_fmt(ByteStream target);

Result dc_load_file(const char *path, AudioFormat fmt, SoundStream **newSound) {
    ByteStream in = io_load_bytes(path);
    if(memcmp(&in, &EMPTY_BYTE_STREAM, sizeof(ByteStream)) == 0) return result_from_errno();

    Result res = dc_load_from_mem(in, fmt, newSound);
    io_free_bytes(&in);
    return res;
}

Result dc_load_from_mem(ByteStream in, AudioFormat userFmt, SoundStream **newSound) {
    if(memcmp(&in, &EMPTY_BYTE_STREAM, sizeof(ByteStream) == 0) || newSound == NULL) userFmt = FMT(INVALID);
    // Add new result errval
    switch(userFmt) {
        default:
        case FMT(INVALID):
            return FORMAT_FAILURE;

        case FMT(AUTO):
            return dc_load_from_mem(in, determine_fmt(in), newSound);

        case FMT(WAV):
            return deserialize_wav(in, newSound);
    }
}


static AudioFormat determine_fmt(ByteStream target) {
    return FMT(INVALID);
}