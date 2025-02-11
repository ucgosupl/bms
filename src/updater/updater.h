#pragma once

#include <stdint.h>

typedef void (*update_fun_t)(void);

void updater_completed_subscribe(update_fun_t f);
void updater_cycle(void);
