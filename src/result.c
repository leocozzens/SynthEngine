// Standard C headers
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
// Local headers
#include <SE/result.h>

// TODO: Custom allocator support
// TODO: Make cycle result function/macro
// TODO: Make return result function/macro
#define CHECK(_cond, _err)  if(_cond) { errno = _err; return NULL; }
#define S_LEN(_str)         (sizeof(_str) - 1)

#define STANDARD_SUCCESS_MSG "Operation executed successfully"
#define STANDARD_FAILURE_MSG "Operation failed"

const Result STANDARD_SUCCESS = { EXIT_SUCCESS, STANDARD_SUCCESS_MSG };
const Result STANDARD_FAILURE = { EXIT_FAILURE, STANDARD_FAILURE_MSG };

Result *create_result(int code, const char *msg, ...) {
    va_list fmtArgs;
    va_start(fmtArgs, msg);
    Result *newResult = vcreate_result(code, msg, fmtArgs);
    va_end(fmtArgs);
    return newResult;
}

Result *vcreate_result(int code, const char *msg, va_list fmtArgs) {
    int length;
    if(msg == NULL) {
        msg = (code == EXIT_SUCCESS) ? STANDARD_SUCCESS_MSG : strerror(code);
        length = strlen(msg);
    }
    else {
        length = vsnprintf(NULL, 0, msg, fmtArgs);
        CHECK(length < 1, EINVAL);
    }

    Result *newResult = malloc(sizeof(Result) + length + 1);
    CHECK(newResult == NULL, ENOMEM);
    newResult->code = code;
    newResult->msg = (char*) (newResult + 1);

    length = vsnprintf(newResult->msg, length + 1, msg, fmtArgs);
    CHECK(length < 1, EINVAL; free(newResult));
    return newResult;
}

Result *create_success_result(const char *msg, ...) {
    va_list fmtArgs;
    va_start(fmtArgs, msg);
    Result *newResult = vcreate_result(EXIT_SUCCESS, msg, fmtArgs);
    va_end(fmtArgs);
    return newResult;
}

Result *create_error_result(const char *msg, ...) {
    va_list fmtArgs;
    va_start(fmtArgs, msg);
    Result *newResult = vcreate_result(EXIT_FAILURE, msg, fmtArgs);
    va_end(fmtArgs);
    return newResult;
}

Result *result_from_errno(void) {
    int code = errno;
    size_t length = strlen(strerror(code));
    Result *newResult = malloc(sizeof(Result) + length + 1);
    CHECK(newResult == NULL, ENOMEM);

    newResult->code = code;
    newResult->msg = (char*) (newResult + 1);

    memcpy(newResult->msg, strerror(code), length);
    newResult->msg[length] = '\0'; 
    return newResult;
}

Result *result_from_template(const Result *template) {
    size_t length = strlen(template->msg);
    Result *newResult = malloc(sizeof(Result) + length + 1);
    CHECK(newResult == NULL, ENOMEM);
    newResult->msg = (char*) (newResult + 1);

    newResult->code = template->code;
    memcpy(newResult->msg, template->msg, length);
    newResult->msg[length] = '\0';

    return newResult;
}

void wipe_result(Result **target) {
    free(*target);
    *target = NULL;
}