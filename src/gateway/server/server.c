#include "server.h"
#include "packet_builder.h"

#include <string.h>

#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"

#include "interface/datetime/datetime.h"
#include "interface/server_protocol/server_protocol.h"

static void on_update(void);
static void set_pb_policy(enum packet_type pt);

static const struct packet_builder *pb;

void server_init(enum packet_type pt)
{
    set_pb_policy(pt);
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

    n += pb->add_timestamp(&frame[n], &dt);

   cdata_iterator_t it = cdata_get_iterator();
   for (const struct cdata_record *r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
   {
        n += pb->add_record(&frame[n], r);
   }

   scp_update_records(frame, n);
}

static void set_pb_policy(enum packet_type pt)
{
    switch (pt)
    {
        case PACKET_BIN:
            pb = bin_pb_get();
            break;
        case PACKET_TXT:
            pb = txt_pb_get();
        default:
            break;
    }
}
