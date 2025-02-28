#include "config_builder.h"

#include "gateway/controller_data/controller_data.h"

#include "interface/nvmem/nvmem.h"

nvmem_reader_t reader = 0;
int32_t n_records = 0;

static void simple_cb_reset_fun(void);
static void simple_cb_add_header(struct config_header *h);
static void simple_cb_add_record(void);

const struct config_builder simple_config_builder = {
    simple_cb_reset_fun,
    simple_cb_add_header,
    simple_cb_add_record,
};

const struct config_builder * simple_cb_get(void)
{
    return &simple_config_builder;
}

static void simple_cb_reset_fun(void)
{
    reader = nvmem_reader_get();
    n_records = 0;
}

static void simple_cb_add_header(struct config_header *h)
{
    nvmem_reader_get_next_chunk(&reader, (uint8_t *)h, sizeof(struct config_header));
}

static void simple_cb_add_record(void)
{
    struct config_record record;

    nvmem_reader_get_next_chunk(&reader, (uint8_t *)&record, sizeof(struct config_record));
    cdata_add_record(record.slave, record.fun, record.reg, record.len);
}
