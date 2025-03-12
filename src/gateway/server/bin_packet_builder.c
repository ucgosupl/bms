#include "packet_builder.h"

#include <string.h>

static void pb_bin_reset(void);
static int pb_bin_add_timestamp(uint8_t *buf, const struct datetime *dt);
static int pb_bin_add_record(uint8_t *buf, const struct cdata_record *r);
static void pb_bin_finish(void);

static const struct packet_builder pb_bin = {
    pb_bin_reset,
    pb_bin_add_timestamp,
    pb_bin_add_record,
    pb_bin_finish,
};

const struct packet_builder *pb_bin_get(void)
{
    return &pb_bin;
}

static void pb_bin_reset(void)
{

}

static int pb_bin_add_timestamp(uint8_t *buf, const struct datetime *dt)
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

static int pb_bin_add_record(uint8_t *buf, const struct cdata_record *r)
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

static void pb_bin_finish(void)
{

}