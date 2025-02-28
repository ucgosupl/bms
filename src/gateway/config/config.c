#include "config.h"

#include "interface/nvmem/nvmem.h"
#include "interface/server_protocol/server_protocol.h"
#include "interface/system/system.h"

static void on_config(const uint8_t *frame, int32_t n);
static void on_save_completed(void);

void config_init(void)
{
    scp_config_subscribe(on_config);
    nvmem_save_completed_subscribe(on_save_completed);
}

static void on_config(const uint8_t *frame, int32_t n)
{
    nvmem_config_save(frame, n);
}

static void on_save_completed(void)
{
    system_trigger_reset();
}
