#include "controller_data.h"

#include <string.h>

#define MAX_RECORDS 1024

static struct cdata_record records[MAX_RECORDS];
static int32_t n;

void cdata_init(void)
{
    n = 0;
}

void cdata_add_record(modbus_slave_t s, modbus_fun_t f, modbus_reg_t r, modbus_len_t l, uint8_t *v)
{
    records[n].slave = s;
    records[n].fun = f;
    records[n].reg = r;
    records[n].len = l;
    records[n].val = v;

    n++;
}

cdata_iterator_t cdata_get_iterator(void)
{
    return 0;
}

const struct cdata_record * cdata_get_next(cdata_iterator_t *i)
{
    if(n <= *i)
        return NULL;

    return &records[(*i)++];
}
