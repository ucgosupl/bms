#include "modbus/modbus.h"
#include "records/records.h"
#include "updater/updater.h"

#include <stdio.h>
#include <string.h>

static uint8_t data_buf[64];

static void update_console(void);
static void update_mqtt(void);
static void update_mqtt_txt(void);

static void payload_print(void);

int main(void)
{
   modbus_init();
   records_init();

   records_add(1, 3, 0x0010, 1, &data_buf[0]);    //2 bytes
   records_add(1, 3, 0x0020, 2, &data_buf[2]);    //4 bytes
   records_add(1, 3, 0x0030, 1, &data_buf[6]);    //2 bytes
   records_add(1, 3, 0x0040, 2, &data_buf[8]);    //4 bytes

   updater_completed_subscribe(update_console);
   updater_completed_subscribe(update_mqtt_txt);
   updater_completed_subscribe(update_mqtt);
   updater_cycle();

   payload_print();

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

struct datetime
{
   uint16_t year;
   uint8_t month;
   uint8_t day;

   uint8_t h;
   uint8_t m;
   uint8_t s;
};

uint8_t seed = 0;

static void timestamp_get(struct datetime *dt)
{
   dt->year = 2025;
   dt->month = 02;
   dt->day = 20;

   dt->h = seed++;
   dt->m = seed++;
   dt->s = seed++;
}

static uint8_t payload[1024];

static void update_mqtt(void)
{
   struct datetime dt;
   timestamp_get(&dt);

   payload[0] = dt.year >> 8;
   payload[1] = dt.year;
   payload[2] = dt.month;
   payload[3] = dt.day;
   payload[4] = dt.h;
   payload[5] = dt.m;
   payload[6] = dt.s;
   payload[7] = 0;

   uint8_t n = 8;
   records_iterator_t it = records_iterator_create();
   for (const struct record *r = records_get_next(&it); r != NULL; r = records_get_next(&it))
   {
      payload[n] = r->slave;
      payload[n + 1] = r->fun;
      payload[n + 2] = r->reg >> 8;
      payload[n + 3] = r->reg;
      payload[n + 4] = r->len >> 8;
      payload[n + 5] = r->len;

      memcpy(&payload[n + 6], r->val, r->len * 2);
      n += 6 + r->len*2;
   }
}

static void payload_print(void)
{
   for (int32_t i = 0; i < 64; i++)
   {
      printf("0x%02X\n", payload[i]);
   }
}

static void update_mqtt_txt(void)
{
   struct datetime dt;
   timestamp_get(&dt);

   printf("%d-%d-%d, %02d:%02d:%02d\n", dt.year, dt.month, dt.day, dt.h, dt.m, dt.s);
   records_iterator_t it = records_iterator_create();
   
   for (const struct record *r = records_get_next(&it); r != NULL; r = records_get_next(&it))
   {
      uint32_t val = ((r->len) == 1) ?
                        r->val[0] | r->val[1] << 8 :
                        r->val[0] | r->val[1] << 8 | r->val[2]<< 16 | r->val[3] << 24;

       printf("SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL: 0x%08X\n", r->slave, r->fun, r->reg, r->len, val);
   }
}