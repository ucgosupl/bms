#include "interface/nvmem/nvmem.h"

#include <stdio.h>

static void trigger_save_completed(void);

void nvmem_config_save(const uint8_t *buf, int32_t len)
{
    printf("\nNVMEM MOCK PRINT SAVED CONFIG\n");

    for (int32_t i = 0; i < len; i++)
        printf("0x%02X ", buf[i]);
    
    trigger_save_completed();

}

int32_t nvmem_config_get(uint8_t *buf, int32_t len)
{
    (void) buf;
    (void) len;

    return 0;
}

static on_save_completed_t save_completed_cb = NULL;

void nvmem_save_completed_subscribe(on_save_completed_t c)
{
    save_completed_cb = c;
}

static void trigger_save_completed(void)
{
    if (NULL != save_completed_cb)
        save_completed_cb();
}

