#include "packet_builder.h"

#include <string.h>

static int32_t bin_pb_add_timestamp(uint8_t *buf, const struct datetime *dt);
static int32_t bin_pb_add_record(uint8_t *buf, const struct cdata_record *r);

const struct packet_builder bin_packet_builder = {
    bin_pb_add_timestamp,
    bin_pb_add_record,
};

const struct packet_builder * bin_pb_get(void)
{
    return &bin_packet_builder;
}

static int32_t bin_pb_add_timestamp(uint8_t *buf, const struct datetime *dt)
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

static int32_t bin_pb_add_record(uint8_t *buf, const struct cdata_record *r)
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
