// C standard headers
#include <string.h>
// Project headers
#include <SE/fmt.h>
// Internal headers
#include <endint.h>
#include <serializer.h>

// General macros
#define S_LEN(_str)             (sizeof(_str) - 1)
#define INTERPRET_AS(_t, _ptr)  (*((_t*)&(_ptr)))

// Identifier macros
#define STR_ID(_tag, _id)       static const char _tag[] = _id
#define ID_TAG(_name, _tag)     _name ## _tag
#define FILE_ID(_name)          ID_TAG(_name, FileID)
#define FMT_ID(_name)           ID_TAG(_name, formatID)

// Operation macros
#define OPERATION_LENGTH        opLen
#define CHECK_SIZE(_raw, _curr) if((_curr) + (OPERATION_LENGTH) > (_raw).size) return result_from_template(&FORMAT_FAILURE)
#define ADD_OPERATION(_curr)    _curr += OPERATION_LENGTH; 

// Results
static const Result FORMAT_FAILURE = { FMT(INVALID), "Invalid audio data format" };
// static const Result SIZE_FAILURE = { FMT(INVALID), "Invalid file size: %zu. Expected file size: %zu" }

// Identifiers
STR_ID(FILE_ID(WAV), "RIFF");
STR_ID(FMT_ID(WAV), "WAVE");
// TMP
#include <stdio.h>

// TODO: Descriptive expected file size
// static size_t check_size(ByteStream *raw, size_t tracker, size_t opSize) {
//     return raw->bytes - (tracker + opSize);
// }

// static bool parse_segment(ByteStream *raw, Byte *segment, size_t *tracker, size_t opSize) {
//     if(*tracker + opSize > raw->size) return false;

//     int comparison = memcmp(raw->bytes + tracker, segment, opSize);
//     *tracker += opSize;
//     return (comparison == 0) ? true : false;
// }

Result *deserialize_wav(ByteStream *raw, SoundStream **newSound) {
    size_t tracker = 0;
    size_t OPERATION_LENGTH;

    OPERATION_LENGTH = S_LEN(FILE_ID(WAV));
    CHECK_SIZE(*raw, tracker);

    if(memcmp(&raw->bytes[tracker], FILE_ID(WAV), OPERATION_LENGTH) != 0) return result_from_template(&FORMAT_FAILURE);
    ADD_OPERATION(tracker);

    OPERATION_LENGTH = sizeof(uint32_t);
    CHECK_SIZE(*raw, tracker);

    uint32_t chunkSize = le32_to_h(INTERPRET_AS(uint32_t, raw->bytes[tracker]));
    ADD_OPERATION(tracker);

    if(chunkSize != raw->size - tracker) return result_from_template(&FORMAT_FAILURE);
    
    OPERATION_LENGTH = S_LEN(FMT_ID(WAV));
    if(memcmp(&raw->bytes[tracker], FMT_ID(WAV), OPERATION_LENGTH) != 0) return result_from_template(&FORMAT_FAILURE);
    ADD_OPERATION(tracker);


    fprintf(stderr, "WAV format data - FILE ID = %s, Chunk size = %u, FMT ID = %s\n",
    FILE_ID(WAV),
    chunkSize,
    FMT_ID(WAV));

    return result_from_template(&FORMAT_FAILURE);
}


// General
// #define WAV_OUT "test.wav"

// Riff chunk
// #define FORMAT "WAVE"

// FMT sub-chunk
// #define SUBCHUNK1_ID "fmt "

// Data sub-chunk
// #define SUBCHUNK2_ID "data"

// int subchunk1Size = 16;
// int audioFormat = 1;
// int numChannels = 2;
// int sampleRate = 44100;
// int byteRate = sampleRate * numChannels * (subchunk1Size / 8);
// int blockAlign = numChannels * (subchunk1Size / 8);
// int bitsPerSample = 16;


// fwrite(&CHUNK_ID, 1, strlen(CHUNK_ID), wav);
// fwrite(&chunkSize, 1, sizeof(chunkSize), wav);
