#include "interface/modbus/modbus.h"

#include "gateway/controller_data/controller_data.h"

#include <stdio.h>

uint8_t buf[1024];

int main(void)
{
   modbus_init();
   cdata_init();

   uint32_t val1 = 0xFFFFFFFF;
   uint32_t val2 = 0xFFFFFFFF;
   uint32_t val3 = 0xFFFFFFFF;

   //CONFIG
   cdata_add_record(0x01, 0x03, 0x1100, 1, &val1);
   cdata_add_record(0x01, 0x03, 0x1101, 2, &val2);
   cdata_add_record(0x01, 0x03, 0x1102, 1, &val3);

   //RUNTIME
   cdata_iterator_t it = cdata_iterator_create();
   for (const struct cdata_record * r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
   {
      modbus_read_hreg(r->slave, r->reg, r->len, r->val);
   }

   //DEBUG
   printf("VAL1: 0x%08X\n\n\n\n\n", val1);
   printf("VAL2: 0x%08X\n\n\n\n\n", val2);
   printf("VAL3: 0x%08X\n\n\n\n\n", val3);

   return 0;
}
