// C standard headers
#include <stdbool.h>
#include <stddef.h>
// Internal headers
#include <endint.h>

#define TO_OR_FROM_BIG_ENDIAN(_name, _type, _byte)                  \
_type _name(_type target) {                                         \
    _type sample = (_type) _byte;                                   \
    if(*((unsigned char*) &sample) == _byte)                        \
        swap_byte_order((unsigned char *) &target, sizeof(_type))   \
    return target;                                                  \
}

#define TO_OR_FROM_LITTLE_ENDIAN(_name, _type, _byte)               \
_type _name(_type target) {                                         \
    _type sample = (_type) _byte;                                   /*Test this line*/ \
    if(*((unsigned char*) &sample) != _byte)                        \
        swap_byte_order((unsigned char *) &target, sizeof(_type));  \
    return target;                                                  \
}

#define LOCAL_SAMPLE_BYTE 0x11

static void swap_byte_order(unsigned char *data, size_t typeSize);

TO_OR_FROM_LITTLE_ENDIAN(le32_to_h, uint32_t, LOCAL_SAMPLE_BYTE)
TO_OR_FROM_LITTLE_ENDIAN(h_to_le32, uint32_t, LOCAL_SAMPLE_BYTE)

static void swap_byte_order(unsigned char *data, size_t typeSize) {
    for(size_t i = 0; i < typeSize / 2; i++) {
        unsigned char tmp = data[i];
        data[i] = data[typeSize - i - 1];
        data[typeSize - i - 1] = tmp;
    }
}
