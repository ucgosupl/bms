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

//cdata_init
//cdata_add_record
