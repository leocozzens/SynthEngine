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

#define NEW_RESULT                  newRes
#define CHECK(_cond, _err)          if(_cond) { errno = _err; return NEW_RESULT; }
#define S_LEN(_str)                 (sizeof(_str) - 1)

#define STANDARD_SUCCESS_MSG        "Operation executed successfully"
#define STANDARD_FAILURE_MSG        "Operation failed"

#define ERROR_BUFFER_SIZE           1024

static char *duplicate_string(const char *restrict src, size_t len);

const Result STANDARD_SUCCESS = { EXIT_SUCCESS, STANDARD_SUCCESS_MSG };
const Result STANDARD_FAILURE = { EXIT_FAILURE, STANDARD_FAILURE_MSG };

Result create_result(int code, const char *msg, ...) {
    va_list fmtArgs;
    va_start(fmtArgs, msg);
    Result NEW_RESULT = vcreate_result(code, msg, fmtArgs);
    va_end(fmtArgs);
    return NEW_RESULT;
}

Result vcreate_result(int code, const char *msg, va_list fmtArgs) {
    Result NEW_RESULT = { code, NULL };
    int length;

    if(msg == NULL) {
        msg = (code == EXIT_SUCCESS) ? STANDARD_SUCCESS_MSG : STANDARD_FAILURE_MSG;
        length = strlen(msg);
    }
    else {
        length = vsnprintf(NULL, 0, msg, fmtArgs);
        CHECK(length < 1, EINVAL);
    }

    NEW_RESULT.msg = malloc(length + 1);
    CHECK(NEW_RESULT.msg == NULL, ENOMEM);

    length = vsnprintf(NEW_RESULT.msg, length + 1, msg, fmtArgs);
    CHECK(length < 1, EINVAL; wipe_result(&NEW_RESULT));
    return NEW_RESULT;
}

Result create_success_result(const char *msg, ...) {
    va_list fmtArgs;
    va_start(fmtArgs, msg);
    Result NEW_RESULT = vcreate_result(EXIT_SUCCESS, msg, fmtArgs);
    va_end(fmtArgs);
    return NEW_RESULT;
}

Result create_error_result(const char *msg, ...) {
    va_list fmtArgs;
    va_start(fmtArgs, msg);
    Result NEW_RESULT = vcreate_result(EXIT_FAILURE, msg, fmtArgs);
    va_end(fmtArgs);
    return NEW_RESULT;
}

Result result_from_errno(void) {
    char errorBuff[ERROR_BUFFER_SIZE];
    strerror_s(errorBuff, ERROR_BUFFER_SIZE, errno);

    Result NEW_RESULT = { errno, duplicate_string(errorBuff, strlen(errorBuff)) };
    return NEW_RESULT;
}

Result result_from_template(const Result *template) {
    Result NEW_RESULT = {
        template->code,
        duplicate_string(template->msg, strlen(template->msg))
    };

    return NEW_RESULT;
}

void wipe_result(Result *target) {
    free(target->msg);
    target->msg = NULL;
}

static char *duplicate_string(const char *restrict src, size_t len) {
    char *new = malloc(len + 1);
    if(new == NULL)
        errno = ENOMEM;
    else {
        memcpy(new, src, len);
        new[len] = '\0';
    }
    return new;
}