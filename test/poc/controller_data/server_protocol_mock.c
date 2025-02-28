#include "interface/server_protocol/server_protocol.h"

#include <stdio.h>

static uint8_t frame[1024];

uint8_t * scp_new_frame(void)
{
    return frame;
}

void scp_update_records(const uint8_t *frame, int32_t n)
{
    for (int32_t i = 0; i < n; i++)
    {
        printf("0x%02X\n", frame[i]);
    }
}
