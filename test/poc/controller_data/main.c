#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"

#include <stdio.h>

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

   //DEBUG
   printf("VAL1: 0x%08X\n\n\n\n\n", val1);
   printf("VAL2: 0x%08X\n\n\n\n\n", val2);
   printf("VAL3: 0x%08X\n\n\n\n\n", val3);

   return 0;
}
