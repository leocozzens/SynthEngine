// C standard heders
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// Project headers
#include <DC/result.h>
#include <DC/stream_info.h>
// Internal headers
#include <fio.h>

#define BINARY_READ  "rb"

#define CHECK_SERVICE(_serv, _file) if((_serv) == -1) { fclose(_file); return result_from_errno(); }

Result *fio_load_bytes(const char *path, ByteStream **newBytes) {
    // TODO: switch to lower level open/close OS calls for file support above 2G
    *newBytes = NULL;
    FILE *target = fopen(path, BINARY_READ);
    if(target == NULL) return result_from_errno();

    CHECK_SERVICE(fseek(target, 0, SEEK_END), target);
    long fSize = ftell(target);
    CHECK_SERVICE(fSize, target);
    CHECK_SERVICE(fseek(target, 0, SEEK_SET), target);

    *newBytes = malloc(sizeof(ByteStream) + fSize);
    if(*newBytes == NULL) {
        errno = ENOMEM;
        fclose(target);
        return result_from_errno();
    }

    (*newBytes)->bytes = (Byte*) ((*newBytes) + 1);
    (*newBytes)->size = fSize;

    size_t bytesRead = fread((*newBytes)->bytes, 1, (*newBytes)->size, target);
    if(bytesRead < (*newBytes)->size) {
        if(ferror(target) != 0) {
            fio_free_bytes(newBytes);
            fclose(target);
            clearerr(target);
            return create_error_result("Failed to read file");
        }
        else
            (*newBytes)->size = bytesRead;
    }
    fclose(target);
    return create_success_result("Succesfully read file into byte stream");
}

void fio_free_bytes(ByteStream **b) {
    free(*b);
    *b = NULL;
}