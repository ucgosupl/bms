#pragma once

void updater_init(void);
void updater_cycle(void);

typedef void (*on_update_t)(void);

void updater_subscribe(on_update_t f);
