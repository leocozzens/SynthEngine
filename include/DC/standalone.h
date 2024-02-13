#ifndef DC_STANDALONE_H
#define DC_STANDALONE_H

#include "result.h"

Result dc_init_player(void);
Result dc_terminate_player(void);
Result dc_set_device(const char *deviceName);
Result dc_run_player(void);

#endif