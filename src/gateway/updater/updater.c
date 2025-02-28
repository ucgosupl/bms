#include "updater.h"

#include "gateway/controller_data/controller_data.h"
#include "interface/modbus/modbus.h"

#include <stdlib.h>

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
}
