#pragma once

#include "interface/datetime/datetime.h"
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

typedef void (*cb_reset_fun_t)(void);
typedef void (*cb_add_header_fun_t)(struct config_header *h);
typedef void (*cb_add_record_fun_t)(void);

struct config_builder
{
    cb_reset_fun_t reset;
    cb_add_header_fun_t add_header;
    cb_add_record_fun_t add_record;
};

const struct config_builder * simple_cb_get(void);
