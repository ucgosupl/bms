#pragma once

#include <stdint.h>

typedef uint8_t modbus_slave_t;
typedef uint8_t modbus_fun_t;
typedef uint16_t modbus_reg_t;
typedef uint16_t modbus_len_t;

void modbus_init(void);

int modbus_read_coil(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
int modbus_read_din(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
int modbus_read_hreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
int modbus_read_inreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);

int modbus_write_coil(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
int modbus_write_din(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
int modbus_write_hreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
int modbus_write_inreg(modbus_slave_t slave, modbus_reg_t reg, modbus_len_t len, uint8_t *val);
