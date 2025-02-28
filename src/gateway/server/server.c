#include "server.h"

#include <string.h>

#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"

#include "interface/datetime/datetime.h"
#include "interface/server_protocol/server_protocol.h"

static void on_update(void);
static int32_t write_datetime(uint8_t *buf, const struct datetime *dt);
static int32_t write_record(uint8_t *buf, const struct cdata_record *r);

void server_init(void)
{
    updater_subscribe(on_update);
}

static void on_update(void)
{
    struct datetime dt;
    datetime_get(&dt);

    uint8_t * frame = scp_new_frame();

    if (NULL == frame)
        return;

    int32_t n = 0;
    
    n += write_datetime(&frame[n], &dt);

   cdata_iterator_t it = cdata_get_iterator();
   for (const struct cdata_record *r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
   {
        n += write_record(&frame[n], r);
   }

   scp_update_records(frame, n);
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
