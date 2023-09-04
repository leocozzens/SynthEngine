// Riff chunk
#define CHUNK_ID "RIFF"
#define FORMAT "WAVE"

// FMT sub-chunk
#define SUBCHUNK1_ID "fmt " 
#define SUBCHUNK1_SIZE 16
#define AUDIO_FORMAT 1
#define NUM_CHANNELS 2
#define SAMPLE_RATE 44100
#define BYTE_RATE (SAMPLE_RATE * NUM_CHANNELS * (SUBCHUNK1_SIZE / 8))
#define BLOCK_ALIGN (NUM_CHANNELS * (SUBCHUNK1_SIZE / 8))
#define BITS_PER_SAMPLE 16

// Data sub-chunk
#define SUBCHUNK2_ID "data"

int main(void) {
    char chunkSize[4];
    char subChunk2Size[4];

    return 0;
}