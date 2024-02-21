// C standard headers
#include <stdio.h>
#include <string.h>
// Project headers
#include <SE/player.h>
#include <SE/fmt.h>
#include <stdlib.h>

#define PLAYER_ERR_FMT              "ENGINE ERROR #%d: %s%s\n"
#define RESULT_ERR                  "Failed to create error message - "

#define IF_OK(_res)                 if(IS_SUCCESS(_res))
#define CYCLE_IF_OK(_proc, _res)    IF_OK(procRes) CYCLE_RESULT(_proc, _res)
#define PRINT_ERR(_res)             fprintf(                                            \
                                        stderr, PLAYER_ERR_FMT, (_res).code,            \
                                        (NO_MESSAGE(_res)) ? RESULT_ERR : (_res).msg,   \
                                        (NO_MESSAGE(_res)) ? strerror(errno) : ""       \
                                    )                                                   \

static union {
    struct {
        bool playerInit;
    };
    bool flags[1];
} cleanupFlags;

int main(int argc, char **argv) {
    Result procRes = STANDARD_EMPTY;
    CYCLE_IF_OK(se_init_player(), procRes), cleanupFlags.playerInit = true;
    CYCLE_IF_OK(se_set_player_device(NULL), procRes);

    IF_OK(procRes) printf("%s - Default\n", procRes.msg);
    CYCLE_IF_OK(se_player_run(), procRes);

    SoundStream *s;
    CYCLE_IF_OK(se_load_file("../assets/wav/test.wav", WAV_FMT, &s), procRes);
    CYCLE_IF_OK(se_terminate_player(), procRes), cleanupFlags.playerInit = false;

    // Error diagnostic
    if(IS_FAILURE(procRes)) PRINT_ERR(procRes);
    // Cleanup
    if(cleanupFlags.playerInit)
        se_terminate_player();
    wipe_result(&procRes);
    
    return procRes.code;
}