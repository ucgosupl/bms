#pragma once

#include <stdint.h>

struct datetime
{
   uint16_t year;
   uint8_t month;
   uint8_t day;

   uint8_t h;
   uint8_t m;
   uint8_t s;
};

void datetime_get(struct datetime *dt);
