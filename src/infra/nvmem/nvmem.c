#include "interface/nvmem/nvmem.h"

void nvmem_config_save(const uint8_t *buf, int32_t len)
{
    (void) buf;
    (void) len;
}

int32_t nvmem_config_get(uint8_t *buf, int32_t len)
{
    (void) buf;
    (void) len;

    return 0;
}

void nvmem_save_completed_subscribe(on_save_completed_t c)
{
    (void) c;
}
