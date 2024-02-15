#ifndef PLAYER_H
#define PLAYER_H

#include "result.h"

Result dc_init_player(void);
Result dc_terminate_player(void);
Result dc_set_player_device(const char *deviceName);
Result dc_player_run(void);

#endif