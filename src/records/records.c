#include "records.h"

#include <string.h>

#define MAX_RECORDS 1024

static struct record records[MAX_RECORDS];
static uint32_t used;

void records_init(void)
{
    memset(records, 0xFF, sizeof(records));
    used = 0;
}

void records_add(modbus_slave_t slave, modbus_fun_t fun, modbus_reg_t reg, modbus_len_t len, uint8_t *val)
{
    records[used].slave = slave;
    records[used].fun = fun;
    records[used].reg = reg;
    records[used].len = len;
    records[used].val = val;
    used++;
}

records_iterator_t records_iterator_create(void)
{
    return 0;
}

const struct record * records_get_next(records_iterator_t *i)
{
    if (*i >= used)
        return NULL;

    return &records[(*i)++];
}



