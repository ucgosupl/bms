#include "modbus/modbus.h"
#include "records/records.h"
#include "updater/updater.h"

#include "aaa/builder.h"

#include <stdio.h>
#include <string.h>

static uint8_t data_buf[64];

static void update_console(void);
static void update_mqtt(void);
static void update_mqtt_txt(void);

static void payload_print(uint8_t *p);

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

#include "utils/timestamp.h"

static void update_mqtt(void)
{
   const struct builder *b = packet_bin_builder_get();

   b->reset();

   struct datetime dt;
   timestamp_get(&dt);
   b->add_timestamp(&dt);

   records_iterator_t it = records_iterator_create();
   for (const struct record *r = records_get_next(&it); r != NULL; r = records_get_next(&it))
   {
      b->add_record(r);
   }

   payload_print(b->get_result());
}

static void payload_print(uint8_t *p)
{
   for (int32_t i = 0; i < 64; i++)
   {
      printf("0x%02X\n", p[i]);
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