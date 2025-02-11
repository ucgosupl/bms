#pragma once

#include <stdint.h>

#include "utils/timestamp.h"
#include "records/records.h"

typedef void (*builder_reset_fun_t)(void);
typedef void (*builder_add_timestamp_fun_t)(struct datetime *dt);
typedef void (*builder_add_record_fun_t)(const struct record *r);
typedef const uint8_t * (*builder_get_result_fun_t)(void);

struct builder
{
    builder_reset_fun_t reset;
    builder_add_timestamp_fun_t add_timestamp;
    builder_add_record_fun_t add_record;
    builder_get_result_fun_t get_result;
};

