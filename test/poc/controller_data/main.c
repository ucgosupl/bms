#include "gateway/config/config.h"
#include "gateway/config/config_builder.h"
#include "gateway/controller_data/controller_data.h"
#include "gateway/updater/updater.h"
#include "gateway/server/server.h"

#include "server_protocol_mock.h"

#include <string.h>
#include <stdio.h>

static void update_console(void);
static void prepare_config(void);
static void * allocate(size_t size);

int main(void)
{
   config_init();
   cdata_init(allocate);

   prepare_config();
   config_load();

   updater_init();
   updater_subscribe(update_console);

   server_init(PACKET_BIN);
   scp_mock_print_bin();

   uint16_t val = 0xAABB;
   struct cdata_record r = {0x05, 0x03, 0x1122, 0x0001, (uint8_t *)&val};
   scp_mock_trigger_modify((uint8_t *)&r, sizeof(struct cdata_record));
   updater_cycle();

   r.slave = 0x08;
   r.reg = 0xFFAA;
   val = 0x1155;
   scp_mock_trigger_modify((uint8_t *)&r, sizeof(struct cdata_record));

   uint8_t buf[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
   scp_mock_trigger_config(buf, 16);

   return 0;
}

static void update_console(void)
{
   printf("\nCONSOLE UPDATER:\n");
   cdata_iterator_t it = cdata_get_iterator();
   for (const struct cdata_record *r = cdata_get_next(&it); r != NULL; r = cdata_get_next(&it))
   {
      uint32_t val = r->val[0] | r->val[1] << 8 | r->val[2]<< 16 | r->val[3] << 24;
      printf("SLAVE: 0x%02X, FUN: 0x%02X REG: 0x%04X, LEN: 0x%04X, VAL: 0x%08X\n", r->slave, r->fun, r->reg, r->len, val);
   }
}

static uint8_t config_buf[8 * 1024];

static const struct config_record config_records[] =
{
   {1, 3, 0x0010, 1},
   {1, 3, 0x0020, 2},
   {1, 3, 0x0030, 1},
   {1, 3, 0x0040, 2},
};

#define CONFIG_RECORDS_CNT (sizeof(config_records) / sizeof(config_records[0]))

extern void nvmem_mock_saved_config_set(uint8_t *buf);

static void prepare_config(void)
{
   struct config_header h;

   memset(&h, 0, sizeof(struct config_header));

   h.n_records = CONFIG_RECORDS_CNT;

   h.last_modified.year = 2025;
   h.last_modified.month = 1;
   h.last_modified.day = 20;

   h.last_modified.h = 20;
   h.last_modified.m = 25;
   h.last_modified.s = 22;

   strcpy(h.author, "Jan Kowalski");

   memcpy(config_buf, &h, sizeof(struct config_header));
   int32_t offset = sizeof(struct config_header);

   memcpy(config_buf + offset, config_records, sizeof(config_records));
   offset += sizeof(config_records);

   printf("\nPREPARED CONFIG\n");
   for (int32_t i = 0; i < offset; i++)
      printf("0x%02X ", config_buf[i]);
   
   printf("\n\n");

   nvmem_mock_saved_config_set(config_buf);
}

static uint8_t buf[8192];
static int32_t buf_offset = 0;

static void * allocate(size_t size)
{
    int32_t start = buf_offset;

    buf_offset += size;

    return buf + start;
}
