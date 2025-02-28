#include "interface/modbus/modbus.h"

static uint8_t seed;

void modbus_init(void)
{
    seed = 0;
}

int modbus_read_coil(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS READ COIL SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X\n", slave, reg, len);

    for (int32_t i = 0; i < (len+7)/8; i++)
    {
        *(val + i) = seed++;
    }

    return 0;
}

int modbus_read_din(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS READ DIN SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X\n", slave, reg, len);

    for (int32_t i = 0; i < (len+7)/8; i++)
    {
        *(val + i) = seed++;
    }

    return 0;
}

int modbus_read_hreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS READ HREG SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X\n", slave, reg, len);

    for (int32_t i = 0; i < len; i++)
    {
        *(val + 2*i) = seed++;
        *(val + 2*i + 1) = seed++;
    }
    
    return 0;
}

int modbus_read_inreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS READ INREG SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X\n", slave, reg, len);

    for (int32_t i = 0; i < len; i++)
    {
        *(val + 2*i) = seed++;
        *(val + 2*i + 1) = seed++;
    }
    
    return 0;
}

int modbus_write_coil(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS WRITE COIL SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X, VAL:", slave, reg, len);

    for (int32_t i = 0; i < (len + 7) / 8; i++)
    {
        printf(" 0x%02X", val[i]);
    }

    printf("\n");

    return 0;
}
int modbus_write_din(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS WRITE DIN SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X, VAL:", slave, reg, len);

    for (int32_t i = 0; i < (len + 7) / 8; i++)
    {
        printf(" 0x%02X", val[i]);
    }

    printf("\n");

    return 0;
}

int modbus_write_hreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS WRITE HREG SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X, VAL:", slave, reg, len);

    for (int32_t i = 0; i < len * 2; i++)
    {
        printf(" 0x%02X", val[i]);
    }

    printf("\n");

    return 0;
}

int modbus_write_inreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    printf("MODBUS WRITE INREG SLAVE: 0x%02X, REG: 0x%04X, LEN: 0x%02X, VAL:", slave, reg, len);

    for (int32_t i = 0; i < len * 2; i++)
    {
        printf(" 0x%02X", val[i]);
    }

    printf("\n");
    
    return 0;
}
