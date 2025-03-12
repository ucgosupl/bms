#include "server.h"
#include "packet_builder.h"

#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"

#include "interface/datetime/datetime.h"

#include <string.h>
#include <stdio.h>

static void update_server_builder_bin(void);
static void update_server_builder_txt(void);

void server_init(void)
{
    updater_subscribe(update_server_builder_bin);
    updater_subscribe(update_server_builder_txt);
}


static uint8_t frame_buf[1024];

static void update_server_builder_bin(void)
{
    const struct packet_builder * pb = pb_bin_get();

    pb->reset();

    struct datetime dt;
    datetime_get(&dt);

    int32_t n = 0;

    n += pb->add_timestamp(&frame_buf[n], &dt);

    cdata_iterator_t it = cdata_iterator_create();
    for (const struct cdata_record * r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
    {
      n += pb->add_record(&frame_buf[n], r);
    }

   for (int32_t i = 0; i < n; i++)
   {
       printf("0x%02X\n", frame_buf[i]);
   }

    pb->finish();
}

static void update_server_builder_txt(void)
{
    const struct packet_builder * pb = pb_txt_get();

    pb->reset();

    struct datetime dt;
    datetime_get(&dt);

    int32_t n = 0;

    n += pb->add_timestamp(&frame_buf[n], &dt);

    cdata_iterator_t it = cdata_iterator_create();
    for (const struct cdata_record * r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
    {
      n += pb->add_record(&frame_buf[n], r);
    }

    printf("%s", frame_buf);

    pb->finish();
}
