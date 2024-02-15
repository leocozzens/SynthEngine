// C standard headers
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define SAMPLE_VAL  1

static bool big_endian(uint32_t sample) {
    return (*((char*)&sample)) ? true : false;
}

uint32_t h_to_le32(uint32_t h) {
    return 0;
}


// Create per type macro
uint32_t le32_to_h(uint32_t le) {
    if(big_endian(SAMPLE_VAL)) return le;

    unsigned char *data = ((unsigned char*) &le);
    for(size_t i = 0; i < sizeof(uint32_t) / 2; i++) {
        uint32_t tmp = data[i];
        data[i] = data[sizeof(uint32_t) - i - 1];
        data[sizeof(uint32_t) - i - 1] = tmp;
    }
    
    return le;
}