#include "modbus.h"

static uint8_t seed;

void modbus_init(void)
{
    seed = 0;
}

int modbus_read_coil(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    for (int32_t i = 0; i < (len+7)/8; i++)
    {
        *(val + i) = seed++;
    }

    return 0;
}

int modbus_read_din(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    for (int32_t i = 0; i < (len+7)/8; i++)
    {
        *(val + i) = seed++;
    }

    return 0;
}

int modbus_read_hreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    for (int32_t i = 0; i < len; i++)
    {
        *(val + 2*i) = seed++;
        *(val + 2*i + 1) = seed++;
    }
    
    return 0;
}

int modbus_read_inreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    for (int32_t i = 0; i < len*2; i++)
    {
        *(val + 2*i) = seed++;
        *(val + 2*i + 1) = seed++;
    }
    
    return 0;
}

int modbus_write_coil(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    return 0;
}
int modbus_write_din(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    return 0;
}

int modbus_write_hreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    return 0;
}

int modbus_write_inreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    return 0;
}
