#include "updater.h"

#include "modbus/modbus.h"
#include "records/records.h"





#define MAX_SUBSCRIBERS  16

static update_fun_t subscribers[MAX_SUBSCRIBERS];
static int32_t subs_cnt;

void updater_completed_subscribe(update_fun_t f)
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

void updater_cycle(void)
{
    records_iterator_t it = records_iterator_create();

    for (const struct record *r = records_get_next(&it); r != NULL; r = records_get_next(&it))
    {
        modbus_read_hreg(r->slave, r->reg, r->len, r->val);
    }

    notify();
}

