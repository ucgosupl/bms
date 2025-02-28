#include "packet_builder.h"

#include <string.h>
#include <stdio.h>

static int32_t txt_pb_add_timestamp(uint8_t *buf, const struct datetime *dt);
static int32_t txt_pb_add_record(uint8_t *buf, const struct cdata_record *r);

const struct packet_builder txt_packet_builder = {
    txt_pb_add_timestamp,
    txt_pb_add_record,
};

const struct packet_builder * txt_pb_get(void)
{
    return &txt_packet_builder;
}

static int32_t txt_pb_add_timestamp(uint8_t *buf, const struct datetime *dt)
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

static int32_t txt_pb_add_record(uint8_t *buf, const struct cdata_record *r)
{
    int32_t n = sprintf((char *)buf, "SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL:", r->slave, r->fun, r->reg, r->len);

    for (int32_t i = 0; i < r->len*2; i++)
    {
        n += sprintf((char *)buf+n, " 0x%02X", r->val[i]);
    }

    n += sprintf((char *)buf+n, "\n");

    return n;
}