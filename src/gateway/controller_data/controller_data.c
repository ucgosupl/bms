#include "controller_data.h"

#include <string.h>

#define MAX_RECORDS 1024

static struct cdata_record records[MAX_RECORDS];
static int32_t n;

static allocator_t allocator = NULL;

void cdata_init(allocator_t a)
{
    n = 0;
    allocator = a;
}

void cdata_add_record(modbus_slave_t s, modbus_fun_t f, modbus_reg_t r, modbus_len_t l)
{
    records[n].slave = s;
    records[n].fun = f;
    records[n].reg = r;
    records[n].len = l;
    records[n].val = allocator(l * 2);

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
