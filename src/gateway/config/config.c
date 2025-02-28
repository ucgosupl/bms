#include "config.h"

#include "gateway/controller_data/controller_data.h"

#include "interface/datetime/datetime.h"
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

#include "interface/modbus/modbus_define.h"

struct config_header
{
    int32_t n_records;
    struct datetime last_modified;
    char author[256 - sizeof(struct datetime) - 4];
};

struct config_record
{
   modbus_slave_t slave;
   modbus_fun_t fun;
   modbus_reg_t reg;
   modbus_len_t len;
};

static struct config_header header = {0};
static struct config_record record = {0};

static uint8_t buf[8192];
static int32_t buf_offset = 0;

static uint8_t * allocate(int32_t size)
{
    int32_t start = buf_offset;

    buf_offset += size;

    return buf + start;
}

#include <stdlib.h>

void config_load(void)
{
    nvmem_reader_t reader = nvmem_reader_get();

    nvmem_reader_get_next_chunk(&reader, (uint8_t *)&header, sizeof(struct config_header));

    for (int32_t i = 0; i < header.n_records; i++)
    {
        nvmem_reader_get_next_chunk(&reader, (uint8_t *)&record, sizeof(struct config_record));

        uint8_t *val = malloc(record.len * 2);
        cdata_add_record(record.slave, record.fun, record.reg, record.len, val);
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
