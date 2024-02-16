#ifndef DC_SERIALIZER_H
#define DC_SERIALIZER_H

// Forward declarations
struct Result;
struct ByteStream;
struct SoundStream;

struct Result *deserialize_wav(struct ByteStream *raw, struct SoundStream **newSound);

#endif