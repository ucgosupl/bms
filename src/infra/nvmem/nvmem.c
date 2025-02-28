#include "interface/nvmem/nvmem.h"

void nvmem_config_save(const uint8_t *buf, int32_t len)
{
    (void) buf;
    (void) len;
}

nvmem_reader_t nvmem_reader_get(void)
{
    return 0;
}

int32_t nvmem_reader_get_next_chunk(nvmem_reader_t *r, uint8_t *buf, int32_t len)
{
    (void) r;
    (void) buf;
    (void) len;
    
    return 0;
}

void nvmem_save_completed_subscribe(on_save_completed_t c)
{
    (void) c;
}
