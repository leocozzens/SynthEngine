#include <stdio.h>

// General
#define WAV_OUT "test.wav"

// Riff chunk
#define CHUNK_ID "RIFF"
#define FORMAT "WAVE"

// FMT sub-chunk
#define SUBCHUNK1_ID "fmt "

// Data sub-chunk
#define SUBCHUNK2_ID "data"

int main(void) {
    char chunkSize[4] = "----";

    int subchunk1Size = 16;
    int audioFormat = 1;
    int numChannels = 2;
    int sampleRate = 44100;
    int byteRate = sampleRate * numChannels * (subchunk1Size / 8);
    int blockAlign = numChannels * (subchunk1Size / 8);
    int bitsPerSample = 16;

    char subChunk2Size[4] = "----";

    FILE *wav = fopen(WAV_OUT, "w");
    if(wav == NULL) {
        perror("fopen");
        return 1;
    }

    fwrite(&CHUNK_ID, 1, strlen(CHUNK_ID), wav);
    fwrite(&chunkSize, 1, sizeof(chunkSize), wav);

    return 0;
}