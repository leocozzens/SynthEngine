#ifndef PLAYER_H
#define PLAYER_H

struct Result;

struct Result init_player(void);
struct Result terminate_player(void);
Result set_player_device(const char *deviceName);
Result player_run(void);

#endif