#pragma once

#include <stdint.h>

void nvmem_config_save(const uint8_t *buf, int32_t len);
int32_t nvmem_config_get(uint8_t *buf, int32_t len);

typedef void (*on_save_completed_t)(void);
void nvmem_save_completed_subscribe(on_save_completed_t c);
