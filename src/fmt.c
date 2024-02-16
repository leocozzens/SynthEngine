// C standard headers
#include <errno.h>
// Project headers
#include <DC/fmt.h>
// Internal headers
#include <fio.h>
#include <serializer.h>

static AudioFormat determine_fmt(ByteStream *target);

static const Result UNKNOWN_FAILURE = { FMT(INVALID), "Unknown audio format" };

Result *dc_load_file(const char *path, AudioFormat fmt, SoundStream **newSound) {
    Result *res;

    ByteStream *fileBytes;
    res = fio_load_bytes(path, &fileBytes);
    if(IS_FAILURE(*res)) return res;

    res = dc_load_from_mem(fileBytes, fmt, newSound);
    fio_free_bytes(&fileBytes);
    return res;
}

Result *dc_load_from_mem(ByteStream *in, AudioFormat userFmt, SoundStream **newSound) {
    if(in == NULL || newSound == NULL) {
        errno = EINVAL;
        return result_from_errno();
    }

    switch(userFmt) {
        default:
        case FMT(INVALID):
            return result_from_template(&UNKNOWN_FAILURE);

        case FMT(AUTO):
            return dc_load_from_mem(in, determine_fmt(in), newSound);

        case FMT(WAV):
            return deserialize_wav(in, newSound);
    }
}

static AudioFormat determine_fmt(ByteStream *target) {
    return FMT(INVALID);
}