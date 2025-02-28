#pragma once

#include <stdint.h>

void scp_mock_print_bin(void);
void scp_mock_print_txt(void);
void scp_mock_trigger_modify(uint8_t *frame, int32_t n);
void scp_mock_trigger_config(uint8_t *frame, int32_t n);
