#ifndef RESULT_H
#define RESULT_H

#include <stdbool.h>

#define IS_SUCCESS(_res)        (((_res).code == 0) ? true : false)
#define IS_FAILURE(_res)        (((_res).code != 0) ? true : false)

typedef struct Result {
    int code;
    char *msg;
} Result;

Result create_result(int code, const char *msg, ...);
Result vcreate_result(int code, const char *msg, va_list fmtArgs);
Result create_success_result(const char *msg, ...);
Result create_error_result(const char *msg, ...);
Result result_from_errno(void);
Result result_from_template(const Result *template);
void wipe_result(Result *target);

// Standard results
extern const Result STANDARD_SUCCESS;
extern const Result STANDARD_FAILURE;

#endif