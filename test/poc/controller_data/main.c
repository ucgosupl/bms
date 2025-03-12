#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"

#include <stdio.h>

static void update_console(void);

uint8_t buf[1024];

int main(void)
{
   cdata_init();

   uint32_t val1 = 0xFFFFFFFF;
   uint32_t val2 = 0xFFFFFFFF;
   uint32_t val3 = 0xFFFFFFFF;

   //CONFIG
   cdata_add_record(0x01, 0x03, 0x1100, 1, &val1);
   cdata_add_record(0x01, 0x03, 0x1101, 2, &val2);
   cdata_add_record(0x01, 0x03, 0x1102, 1, &val3);

   updater_init();

   //RUNTIME
   updater_cycle();
   update_console();

   //DEBUG
   printf("VAL1: 0x%08X\n\n\n\n\n", val1);
   printf("VAL2: 0x%08X\n\n\n\n\n", val2);
   printf("VAL3: 0x%08X\n\n\n\n\n", val3);

   return 0;
}

static void update_console(void)
{
   cdata_iterator_t it = cdata_iterator_create();
   for (const struct cdata_record * r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
   {
      uint32_t val = r->val[0] | r->val[1] << 8 | r->val[2]<< 16 | r->val[3] << 24;
      printf("SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL: 0x%08X\n", r->slave, r->fun, r->reg, r->len, val);
   }
}
