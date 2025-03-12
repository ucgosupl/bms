#pragma once

#include "interface/datetime/datetime.h"
#include "gateway/controller_data/controller_data.h"

typedef void (*reset_fun)(void);
typedef int (*add_timestamp_fun)(uint8_t *buf, const struct datetime *dt);
typedef int (*add_record_fun)(uint8_t *buf, const struct cdata_record *r);
typedef void (*finish_fun)(void);

struct packet_builder
{
    reset_fun reset;

    add_timestamp_fun add_timestamp;
    add_record_fun add_record;

    finish_fun finish;
};

const struct packet_builder *pb_bin_get(void);
const struct packet_builder *pb_txt_get(void);
