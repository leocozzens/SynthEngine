#ifndef PLAYER_H
#define PLAYER_H

#include "result.h"

Result se_init_player(void);
Result se_terminate_player(void);
Result se_set_player_device(const char *deviceName);
Result se_player_run(void);

#endif