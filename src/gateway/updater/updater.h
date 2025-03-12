#pragma once

void updater_init(void);
void updater_cycle(void);

typedef void (*update_t)(void);

void updater_subscribe(update_t u);
