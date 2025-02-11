#pragma once

#include "modbus/modbus_define.h"

typedef uint32_t records_iterator_t;

struct record
{
    modbus_slave_t slave;
    modbus_fun_t fun;
    modbus_reg_t reg;
    modbus_len_t len;
    uint8_t *val;
};

void records_init(void);
void records_add(modbus_slave_t slave, modbus_fun_t fun, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
records_iterator_t records_iterator_create(void);
const struct record * records_get_next(records_iterator_t *i);