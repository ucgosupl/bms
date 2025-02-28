#include "server.h"
#include "packet_builder.h"

#include <string.h>

#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"

#include "interface/datetime/datetime.h"
#include "interface/server_protocol/server_protocol.h"
#include "interface/modbus/modbus.h"

static void on_update(void);
static void on_modify(const uint8_t *frame, int32_t n);

typedef const struct packet_builder * (*pb_get_fun_t)(void);
static const pb_get_fun_t pb_fun_mapper[PACKET_MAX] =
{
    bin_pb_get,
    txt_pb_get,
};

static const struct packet_builder *pb;

void server_init(enum packet_type pt)
{
    pb = pb_fun_mapper[pt]();
    updater_subscribe(on_update);
    scp_modify_subscribe(on_modify);
}

static void on_update(void)
{
    struct datetime dt;
    datetime_get(&dt);

    uint8_t * frame = scp_new_frame();

    if (NULL == frame)
        return;

    int32_t n = 0;

    n += pb->add_timestamp(&frame[n], &dt);

   cdata_iterator_t it = cdata_get_iterator();
   for (const struct cdata_record *r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
   {
        n += pb->add_record(&frame[n], r);
   }

   scp_update_records(frame, n);
}

static void on_modify(const uint8_t *frame, int32_t n)
{
    (void) n;
    
    struct cdata_record *r = (struct cdata_record *)frame;

    modbus_write_hreg(r->slave, r->reg, r->len, r->val);
}
