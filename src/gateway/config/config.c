#include "config.h"
#include "config_builder.h"

#include "interface/datetime/datetime.h"
#include "interface/nvmem/nvmem.h"
#include "interface/server_protocol/server_protocol.h"
#include "interface/system/system.h"

static struct config_header header = {0};

static void on_config(const uint8_t *frame, int32_t n);
static void on_save_completed(void);

void config_init(void)
{
    scp_config_subscribe(on_config);
    nvmem_save_completed_subscribe(on_save_completed);
}

void config_load(void)
{
    const struct config_builder * b = simple_cb_get();

    b->add_header(&header);

    for (int32_t i = 0; i < header.n_records; i++)
    {
        b->add_record();
    }
}

static void on_config(const uint8_t *frame, int32_t n)
{
    nvmem_config_save(frame, n);
}

static void on_save_completed(void)
{
    system_trigger_reset();
}
