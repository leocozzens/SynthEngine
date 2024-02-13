// Project headers
#include <DC/result.h>
// Internal headers
#include <player.h>
#include <stdio.h>

Result dc_init_player(void) {
    return init_player();
}

Result dc_terminate_player(void) {
    return terminate_player();
}

Result dc_set_device(const char *deviceName) {
    return set_player_device(deviceName);
}

Result dc_run_player(void) {
    return player_run();
}