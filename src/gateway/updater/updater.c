#include "updater.h"

#include "gateway/controller_data/controller_data.h"
#include "interface/modbus/modbus.h"

#include <stdlib.h>

#define MAX_SUBSCRIBERS  16

static update_fun_t subscribers[MAX_SUBSCRIBERS];
static int32_t subs_cnt;

static void notify(void);

void updater_init(void)
{
    modbus_init();
}

void updater_cycle(void)
{
    cdata_iterator_t it = cdata_get_iterator();

    for (const struct cdata_record *r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
    {
        modbus_read_hreg(r->slave, r->reg, r->len, r->val);
    }

    notify();
}

void updater_subscribe(update_fun_t f)
{
    subscribers[subs_cnt++] = f;
}

static void notify(void)
{
    int32_t i;

    for (i = 0; i < subs_cnt; i++)
    {
        if (subscribers[i] != NULL)
            subscribers[i]();
    }
}