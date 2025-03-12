#include "updater.h"

#include "gateway/controller_data/controller_data.h"

#include "interface/modbus/modbus.h"

#include <stdlib.h>

#define MAX_SUBSCRIBERS 16

static update_t subscribers[MAX_SUBSCRIBERS];
static int32_t n_subscribers;

static void notify(void);

void updater_init(void)
{
    n_subscribers = 0;
    modbus_init();
}

void updater_cycle(void)
{
    cdata_iterator_t it = cdata_iterator_create();
    for (const struct cdata_record * r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
    {
       modbus_read_hreg(r->slave, r->reg, r->len, r->val);
    }

    notify();
}

void updater_subscribe(update_t u)
{
    subscribers[n_subscribers++] = u;
}

static void notify(void)
{
    for (int32_t i = 0; i < n_subscribers; i++)
    {
        subscribers[i]();
    }
}
