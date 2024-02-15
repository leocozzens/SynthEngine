#ifndef DC_SERIALIZER_H
#define DC_SERIALIZER_H

struct ByteStream;
struct SoundStream;

Result deserialize_wav(struct ByteStream raw, struct SoundStream **newSound);

extern const Result FORMAT_FAILURE;

#endif