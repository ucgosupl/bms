#include "packet_builder.h"

#include <string.h>

static void pb_txt_reset(void);
static int pb_txt_add_timestamp(uint8_t *buf, const struct datetime *dt);
static int pb_txt_add_record(uint8_t *buf, const struct cdata_record *r);
static void pb_txt_finish(void);

static const struct packet_builder pb_txt = {
    pb_txt_reset,
    pb_txt_add_timestamp,
    pb_txt_add_record,
    pb_txt_finish,
};

const struct packet_builder *pb_txt_get(void)
{
    return &pb_txt;
}

static void pb_txt_reset(void)
{

}

static int pb_txt_add_timestamp(uint8_t *buf, const struct datetime *dt)
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

static int pb_txt_add_record(uint8_t *buf, const struct cdata_record *r)
{
    int32_t n = sprintf((char *)buf, "SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL:", r->slave, r->fun, r->reg, r->len);

    for (int32_t i = 0; i < r->len*2; i++)
    {
        n += sprintf((char *)buf+n, " 0x%02X", r->val[i]);
    }

    n += sprintf((char *)buf+n, "\n");

    return n;
}

static void pb_txt_finish(void)
{

}