#pragma once

#include "interface/modbus/modbus_define.h"

struct cdata_record
{
    modbus_slave_t slave;
    modbus_fun_t fun;
    modbus_reg_t reg;
    modbus_len_t len;
    uint8_t *val;
};

void cdata_init(void);
void cdata_add_record(modbus_slave_t s, modbus_fun_t f, modbus_reg_t r, modbus_len_t l, uint8_t *v);

const struct cdata_record * cdata_get_record(uint32_t i);
uint32_t cdata_records_cnt(void);