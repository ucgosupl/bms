#include "server_protocol_mock.h"

#include "interface/server_protocol/server_protocol.h"

#include <stdio.h>

enum print_policy {PRINT_BIN, PRINT_TXT};

static uint8_t frame[1024];
enum print_policy pp = PRINT_BIN;

static void print_bin(const uint8_t *frame, int32_t n);
static void print_txt(const uint8_t *frame, int32_t n);

uint8_t * scp_new_frame(void)
{
    return frame;
}

void scp_update_records(const uint8_t *frame, int32_t n)
{
    switch(pp)
    {
        case PRINT_BIN:
            print_bin(frame, n);
            break;
        case PRINT_TXT:
            print_txt(frame, n);
            break;
        default:
            break;
    }
}

static on_modify_t modify_cb = NULL;

void scp_modify_subscribe(on_modify_t c)
{
    modify_cb = c;
}

static on_config_t config_cb = NULL;

void scp_config_subscribe(on_config_t c)
{
    config_cb = c;
}

void scp_mock_print_bin(void)
{
    pp = PRINT_BIN;
}

void scp_mock_print_txt(void)
{
    pp = PRINT_TXT;  
}

void scp_mock_trigger_modify(uint8_t *frame, int32_t n)
{
    if (NULL != modify_cb)
        modify_cb(frame, n);
}

void scp_mock_trigger_config(uint8_t *frame, int32_t n)
{
    if (NULL != config_cb)
        config_cb(frame, n);
}

static void print_bin(const uint8_t *frame, int32_t n)
{
    printf("\nSERVER PROTOCOL MOCK PRINT BIN\n");
    for (int32_t i = 0; i < n; i++)
    {
        printf("0x%02X\n", frame[i]);
    }
}

static void print_txt(const uint8_t *frame, int32_t n)
{
    (void) n;

    printf("\nSERVER PROTOCOL MOCK PRINT TXT\n");
    printf("%s", frame);
}
