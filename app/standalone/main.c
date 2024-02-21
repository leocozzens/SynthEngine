// C standard headers
#include <stdio.h>
#include <string.h>
// Project headers
#include <SE/player.h>
#include <SE/fmt.h>
#include <stdlib.h>

#define PLAYER_ERR_FMT      "ENGINE ERROR #%d: %s%s\n"
#define RESULT_ERR          "Failed to create error message - "
#define ERR_AND_DIE(_res)   fprintf(stderr, PLAYER_ERR_FMT, (_res).code,        \
                                (NO_MESSAGE(_res)) ? RESULT_ERR : (_res).msg,   \
                                (NO_MESSAGE(_res)) ? strerror(errno) : " ");    \
                            wipe_result(&(_res));                               \
                            return (_res).code

int main(int argc, char **argv) {
    Result procRes = STANDARD_EMPTY;
    VALIDATE_RESULT(
        se_init_player(),
        procRes,
        ERR_AND_DIE(procRes)
    );

    VALIDATE_RESULT(
        se_set_player_device(NULL),
        procRes,
        ignore_result(se_terminate_player());
        ERR_AND_DIE(procRes)
    );
    printf("%s - Default\n", procRes.msg);

    VALIDATE_RESULT(
        se_player_run(),
        procRes,
        ignore_result(se_terminate_player());
        ERR_AND_DIE(procRes)
    );

    SoundStream *s;
    VALIDATE_RESULT(
        se_load_file("../assets/wav/test.wav", WAV_FMT, &s),
        procRes,
        ignore_result(se_terminate_player());
        ERR_AND_DIE(procRes)
    );

    VALIDATE_RESULT(
        se_terminate_player(),
        procRes,
        ERR_AND_DIE(procRes)
    );

    wipe_result(&procRes);
    return 0;
}