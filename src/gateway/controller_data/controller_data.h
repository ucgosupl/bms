#pragma once

#include "interface/modbus/modbus_define.h"

#include <stddef.h>

struct cdata_record
{
    modbus_slave_t slave;
    modbus_fun_t fun;
    modbus_reg_t reg;
    modbus_len_t len;
    uint8_t *val;
};

typedef void * (*allocator_t)(size_t size);

void cdata_init(allocator_t a);
void cdata_add_record(modbus_slave_t s, modbus_fun_t f, modbus_reg_t r, modbus_len_t l);

typedef int cdata_iterator_t;

cdata_iterator_t cdata_get_iterator(void);
const struct cdata_record * cdata_get_next(cdata_iterator_t *i);
