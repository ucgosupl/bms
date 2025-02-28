#pragma once

#include "gateway/controller_data/controller_data.h"
#include "interface/datetime/datetime.h"

typedef int32_t (*pb_add_timestamp_fun_t)(uint8_t *buf, const struct datetime *dt);
typedef int32_t (*pb_add_record_fun_t)(uint8_t *buf, const struct cdata_record *r);

struct packet_builder
{
    pb_add_timestamp_fun_t add_timestamp;
    pb_add_record_fun_t add_record;
};

const struct packet_builder * bin_pb_get(void);
