// C standard headers
#include <stdio.h>
// Project headers
#include <SE/player.h>
#include <SE/fmt.h>

#define PROC_RESULT     (PROC_RESULT)
#define PLAYER_ERR_FMT  "PLAYER ERROR %d: %s\n"
#define ERR_AND_DIE     fprintf(stderr, PLAYER_ERR_FMT, PROC_RESULT.code, PROC_RESULT.msg);     \
                        wipe_result(&PROC_RESULT);                                              \
                        return PROC_RESULT.code;

int main(int argc, char **argv) {
    Result PROC_RESULT = STANDARD_EMPTY;
    VALIDATE_RESULT(
        se_init_player(),
        PROC_RESULT,
        ERR_AND_DIE
    );

    VALIDATE_RESULT(
        se_set_player_device(NULL),
        PROC_RESULT,
        ERR_AND_DIE
    );
    printf("%s - Default\n", PROC_RESULT.msg);

    VALIDATE_RESULT(
        se_player_run(),
        PROC_RESULT, 
        ERR_AND_DIE
    );

    SoundStream *s;
    VALIDATE_RESULT(
        se_load_file("../assets/wav/test.wav", WAV_FMT, &s),
        PROC_RESULT, 
        ERR_AND_DIE
    );

    VALIDATE_RESULT(
        se_terminate_player(),
        PROC_RESULT,
        ERR_AND_DIE
    );

    wipe_result(&PROC_RESULT);
    return 0;
}