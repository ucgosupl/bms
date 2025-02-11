#include "builder.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

static void console_builder_reset(void);
static void console_builder_add_timestamp(struct datetime *dt);
static void console_builder_add_record(const struct record *r);
static const uint8_t * console_builder_get_result(void);

const struct builder console_builder = {
    console_builder_reset,
    console_builder_add_timestamp,
    console_builder_add_record,
    console_builder_get_result,
};

const struct builder * console_builder_get(void)
{
    return &console_builder;
}

static void console_builder_reset(void)
{
    printf("Console Builder Packet View:\n");
}

static void console_builder_add_timestamp(struct datetime *dt)
{
   printf("TIMESTAMP: %d-%d-%d, %02d:%02d:%02d\n", dt->year, dt->month, dt->day, dt->h, dt->m, dt->s);
}

static void console_builder_add_record(const struct record *r)
{
      uint32_t val = ((r->len) == 1) ?
                        r->val[0] | r->val[1] << 8 :
                        r->val[0] | r->val[1] << 8 | r->val[2]<< 16 | r->val[3] << 24;

       printf("SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL: 0x%08X\n", r->slave, r->fun, r->reg, r->len, val);
}

static const uint8_t * console_builder_get_result(void)
{
    return NULL;
}
