#include "builder.h"

#include <stdint.h>
#include <string.h>

#define MAX_PAYLOAD 1024
static uint8_t payload[MAX_PAYLOAD];

static int n;

static void packet_bin_builder_reset(void);
static void packet_bin_builder_add_timestamp(struct datetime *dt);
static void packet_bin_builder_add_record(const struct record *r);
static const uint8_t * packet_bin_builder_get_result(void);

const struct builder packet_bin_builder = {
    packet_bin_builder_reset,
    packet_bin_builder_add_timestamp,
    packet_bin_builder_add_record,
    packet_bin_builder_get_result,
};

const struct builder * packet_bin_builder_get(void)
{
    return &packet_bin_builder;
}

static void packet_bin_builder_reset(void)
{
    memset(payload, 0, MAX_PAYLOAD);
    n = 0;
}

static void packet_bin_builder_add_timestamp(struct datetime *dt)
{
   payload[n + 0] = dt->year >> 8;
   payload[n + 1] = dt->year;
   payload[n + 2] = dt->month;
   payload[n + 3] = dt->day;
   payload[n + 4] = dt->h;
   payload[n + 5] = dt->m;
   payload[n + 6] = dt->s;
   payload[n + 7] = 0;

   n += 8;
}

static void packet_bin_builder_add_record(const struct record *r)
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

static const uint8_t * packet_bin_builder_get_result(void)
{
    return payload;
}
