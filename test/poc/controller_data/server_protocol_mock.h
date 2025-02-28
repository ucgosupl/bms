#pragma once

#include <stdint.h>

extern void scp_mock_print_bin(void);
extern void scp_mock_print_txt(void);
extern void scp_mock_trigger_modify(uint8_t *frame, int32_t n);
