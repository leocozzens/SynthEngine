// C standard headers
#include <stdio.h>
// Project headers
#include <DC/standalone.h>


#define CHECK_ERR(_res, _fmt)   if(result_is_error(_res)) { \
                                    fprintf(stderr, _fmt, _res.code, _res.msg); \
                                    return _res.code; \
                                }

#define PLAYER_ERR_FMT          "PLAYER ERROR %d: %s\n"

int main(int argc, char **argv) {
    Result procRes;
    procRes = dc_init_player();
    CHECK_ERR(procRes, PLAYER_ERR_FMT);


    procRes = dc_set_device(NULL);
    CHECK_ERR(procRes, PLAYER_ERR_FMT);
    printf("%s - Default\n", procRes.msg);

    procRes = dc_run_player();
    CHECK_ERR(procRes, PLAYER_ERR_FMT);

    procRes = dc_terminate_player();
    CHECK_ERR(procRes, PLAYER_ERR_FMT);
    return 0;
}