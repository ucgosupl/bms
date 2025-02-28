#pragma once

#include <stdint.h>

uint8_t * scp_new_frame(void);
void scp_update_records(const uint8_t *frame, int32_t n);

typedef void (*on_modify_t)(const uint8_t *frame, int32_t n);
void scp_modify_subscribe(on_modify_t c);
