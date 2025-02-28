#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"
#include "gateway/server/server.h"

#include <stdio.h>

static uint8_t buf[512];

static void update_console(void);

int main(void)
{
   cdata_init();

   cdata_add_record(1, 3, 0x0010, 1, &buf[0]);  //2 bytes
   cdata_add_record(1, 3, 0x0020, 2, &buf[2]);  //4 bytes
   cdata_add_record(1, 3, 0x0030, 1, &buf[6]);  //2 bytes
   cdata_add_record(1, 3, 0x0040, 2, &buf[8]);  //4 bytes

   updater_init();
   updater_subscribe(update_console);

   server_init();

   updater_cycle();

   return 0;
}

static void update_console(void)
{
   cdata_iterator_t it = cdata_get_iterator();
   for (const struct cdata_record *r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
   {
      uint32_t val = r->val[0] | r->val[1] << 8 | r->val[2]<< 16 | r->val[3] << 24;
      printf("SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL: 0x%08X\n", r->slave, r->fun, r->reg, r->len, val);
   }
}
