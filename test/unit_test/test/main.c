#include "modbus/modbus.h"

#include <stdio.h>

int main(void)
{
   modbus_init();

   uint32_t val = 0xFFFFFFFF;

   modbus_read_hreg(1, 2, 2, &val);

   printf("VAL: 0x%08X\n\n\n\n\n", val);

   return 0;
}
