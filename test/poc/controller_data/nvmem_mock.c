#include "interface/nvmem/nvmem.h"

#include <string.h>
#include <stdio.h>

static void trigger_save_completed(void);

static uint8_t *saved_config = NULL;

void nvmem_config_save(const uint8_t *buf, int32_t len)
{
    printf("\nNVMEM MOCK PRINT SAVED CONFIG\n");

    for (int32_t i = 0; i < len; i++)
        printf("0x%02X ", buf[i]);
    
    trigger_save_completed();

}

nvmem_reader_t nvmem_reader_get(void)
{
    return 0;
}

int32_t nvmem_reader_get_next_chunk(nvmem_reader_t *r, uint8_t *buf, int32_t len)
{
    memcpy(buf, saved_config +*r, len);

    *r += len;
    
    return 0;
}

static on_save_completed_t save_completed_cb = NULL;

void nvmem_save_completed_subscribe(on_save_completed_t c)
{
    save_completed_cb = c;
}

void nvmem_mock_saved_config_set(uint8_t *buf)
{
    saved_config = buf;
}

static void trigger_save_completed(void)
{
    if (NULL != save_completed_cb)
        save_completed_cb();
}

