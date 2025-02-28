#include "interface/server_protocol/server_protocol.h"

#include <stdlib.h>

uint8_t * scp_new_frame(void)
{
    return NULL;
}

void scp_update_records(const uint8_t *frame, int32_t n)
{
    (void) frame;
    (void) n;
}

void scp_modify_subscribe(on_modify_t c)
{
    (void) c;
}

void scp_config_subscribe(on_config_t c)
{
    (void) c;
}
