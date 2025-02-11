#include "modbus/modbus.h"
#include "records/records.h"
#include "updater/updater.h"

#include <stdio.h>

static uint8_t buf[64];

static void update_console(void);

int main(void)
{
   modbus_init();
   records_init();

   records_add(1, 3, 0x0010, 1, &buf[0]); //2 bytes
   records_add(1, 3, 0x0020, 2, &buf[2]);    //4 bytes
   records_add(1, 3, 0x0030, 1, &buf[6]);    //2 bytes
   records_add(1, 3, 0x0040, 2, &buf[8]);    //4 bytes

   updater_completed_subscribe(update_console);
   updater_cycle();

   return 0;
}

static void update_console(void)
{
    records_iterator_t it = records_iterator_create();

    for (const struct record *r = records_get_next(&it); r != NULL; r = records_get_next(&it))
    {
      uint32_t val = ((r->len) == 1) ?
                        r->val[0] | r->val[1] << 8 :
                        r->val[0] | r->val[1] << 8 | r->val[2]<< 16 | r->val[3] << 24;

       printf("SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL: 0x%08X\n", r->slave, r->fun, r->reg, r->len, val);
    }
}