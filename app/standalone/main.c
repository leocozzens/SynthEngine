// C standard headers
#include <stdio.h>
// Project headers
#include <DC/player.h>
#include <DC/fmt.h>


#define CHECK_ERR(_res, _fmt)   if(IS_FAILURE(*_res)) {                                 \
                                    fprintf(stderr, _fmt, (_res)->code, (_res)->msg);   \
                                    int code = (_res)->code;                            \
                                    return code;                                        \
                                }

#define PLAYER_ERR_FMT          "PLAYER ERROR %d: %s\n"

int main(int argc, char **argv) {
    Result *procRes;
    procRes = dc_init_player();
    CHECK_ERR(procRes, PLAYER_ERR_FMT);

    procRes = dc_set_player_device(NULL);
    char *tmp = procRes->msg;
    CHECK_ERR(procRes, PLAYER_ERR_FMT);
    printf("%s - Default\n", tmp);

    procRes = dc_player_run();
    CHECK_ERR(procRes, PLAYER_ERR_FMT);

    SoundStream *s;
    procRes = dc_load_file("../assets/wav/test.wav", WAV_FMT, &s);
    CHECK_ERR(procRes, PLAYER_ERR_FMT);

    procRes = dc_terminate_player();
    CHECK_ERR(procRes, PLAYER_ERR_FMT);
    return 0;
}