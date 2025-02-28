#pragma once

#include <stdint.h>

void nvmem_config_save(const uint8_t *buf, int32_t len);

#define NVMEM_READER_ERROR  -1

typedef int32_t nvmem_reader_t;
nvmem_reader_t nvmem_reader_get(void);
int32_t nvmem_reader_get_next_chunk(nvmem_reader_t *r, uint8_t *buf, int32_t len);

typedef void (*on_save_completed_t)(void);
void nvmem_save_completed_subscribe(on_save_completed_t c);
