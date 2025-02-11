#include "modbus/modbus.h"
#include "records/records.h"

#include <stdio.h>

static uint8_t buf[64];

int main(void)
{
   modbus_init();
   records_init();

   records_add(1, 3, 0x0010, 1, &buf[0]); //2 bytes
   records_add(1, 3, 0x0020, 2, &buf[2]);    //4 bytes
   records_add(1, 3, 0x0030, 1, &buf[6]);    //2 bytes
   records_add(1, 3, 0x0040, 2, &buf[8]);    //4 bytes

   records_iterator_t it = records_iterator_create();

   const struct record *r = records_get_next(&it);

   while (r != NULL)
   {
      modbus_read_hreg(r->slave, r->reg, r->len, r->val);

      uint32_t val = r->val[0] | r->val[1] << 8 | r->val[2]<< 16 | r->val[3] << 24;
      printf("SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL: 0x%08X\n", r->slave, r->fun, r->reg, r->len, val);

      r = records_get_next(&it);
   }

   for (int32_t i = 0; i < 12; i++)
   {
      printf("0x%02x\n", buf[i]);
   }

   return 0;
}
