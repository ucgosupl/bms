#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"

#include "interface/datetime/datetime.h"

#include <stdio.h>
#include <string.h>

static void update_console(void);

static void update_server(void);
static int32_t write_datetime(uint8_t *buf, const struct datetime *dt);
static int32_t write_record(uint8_t *buf, const struct cdata_record *r);

static void update_server_txt(void);
static int32_t txt_add_timestamp(uint8_t *buf, const struct datetime *dt);
static int32_t txt_add_record(uint8_t *buf, const struct cdata_record *r);

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
   updater_subscribe(update_console);
   updater_subscribe(update_server);
   updater_subscribe(update_server_txt);

   //RUNTIME
   updater_cycle();
   // update_console();
   // update_server();

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



static uint8_t frame_buf[1024];

static void update_server(void)
{
    struct datetime dt;
    datetime_get(&dt);

    int32_t n = 0;
    
    n += write_datetime(&frame_buf[n], &dt);

    cdata_iterator_t it = cdata_iterator_create();
    for (const struct cdata_record * r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
    {
      n += write_record(&frame_buf[n], r);
    }

   for (int32_t i = 0; i < n; i++)
   {
       printf("0x%02X\n", frame_buf[i]);
   }
}

static int32_t write_datetime(uint8_t *buf, const struct datetime *dt)
{
    buf[0] = dt->year >> 8;
    buf[1] = dt->year;
    buf[2] = dt->month;
    buf[3] = dt->day;
    buf[4] = dt->h;
    buf[5] = dt->m;
    buf[6] = dt->s;
    buf[7] = 0;

    return 8;
}

static int32_t write_record(uint8_t *buf, const struct cdata_record *r)
{
    buf[0] = r->slave;
    buf[1] = r->fun;
    buf[2] = r->reg >> 8;
    buf[3] = r->reg;
    buf[4] = r->len >> 8;
    buf[5] = r->len;

    memcpy(&buf[6], r->val, r->len * 2);
    
    return 6 + r->len*2;
}


static void update_server_txt(void)
{
    struct datetime dt;
    datetime_get(&dt);

    int32_t n = 0;
    
    n += txt_add_timestamp(&frame_buf[n], &dt);

    cdata_iterator_t it = cdata_iterator_create();
    for (const struct cdata_record * r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
    {
      n += txt_add_record(&frame_buf[n], r);
    }

   printf("%s", frame_buf);
}

static int32_t txt_add_timestamp(uint8_t *buf, const struct datetime *dt)
{
    buf[0] = (dt->year/1000) + '0';
    buf[1] = (dt->year%1000)/100 + '0';
    buf[2] = (dt->year%100)/10 + '0';
    buf[3] = (dt->year%10) + '0';

    buf[4] = '-';

    buf[5] = (dt->month/10) + '0';
    buf[6] = (dt->month%10) + '0';

    buf[7] = '-';

    buf[8] = (dt->day/10) + '0';
    buf[9] = (dt->day%10) + '0';

    buf[10] = ' ';

    buf[11] = (dt->h/10) + '0';
    buf[12] = (dt->h%10) + '0';

    buf[13] = ':';

    buf[14] = (dt->m/10) + '0';
    buf[15] = (dt->m%10) + '0';

    buf[16] = ':';

    buf[17] = (dt->s/10) + '0';
    buf[18] = (dt->s%10) + '0';

    buf[19] = '\n';

    return 20;
}

static int32_t txt_add_record(uint8_t *buf, const struct cdata_record *r)
{
    int32_t n = sprintf((char *)buf, "SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL:", r->slave, r->fun, r->reg, r->len);

    for (int32_t i = 0; i < r->len*2; i++)
    {
        n += sprintf((char *)buf+n, " 0x%02X", r->val[i]);
    }

    n += sprintf((char *)buf+n, "\n");

    return n;
}
