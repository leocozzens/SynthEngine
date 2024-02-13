#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>

#define SUCCESS_RESULT(_msg)    { 0, _msg };
#define ERROR_RESULT(_msg)      { 1, _msg };

typedef struct Result {
    int code;
    const char *msg;
} Result;

Result create_result(int retCode, const char *msg);
Result create_success_result(const char *msg);
Result create_error_result(const char *msg);
bool result_is_error(Result target);

// Standard results
extern const Result STANDARD_SUCCESS;
extern const Result STANDARD_FAILURE;

#endif