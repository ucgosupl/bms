#include "controller_data.h"

#include <string.h>

#define MAX_RECORDS 1024

static struct cdata_record records[MAX_RECORDS];
static uint32_t n;

void cdata_init(void)
{
    n = 0;
}

void cdata_add_record(modbus_slave_t s,
    modbus_fun_t f,
    modbus_reg_t r,
    modbus_len_t l,
    uint8_t *v)
{
    records[n].slave = s;
    records[n].fun = f;
    records[n].reg = r;
    records[n].len = l;
    records[n].val = v;

    n++;
}

const struct cdata_record * cdata_get_record(uint32_t i)
{
    return &records[i];
}

uint32_t cdata_records_cnt(void)
{
    return n;
}
