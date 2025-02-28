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

static void print_bin(const uint8_t *frame, int32_t n)
{
    for (int32_t i = 0; i < n; i++)
    {
        printf("0x%02X\n", frame[i]);
    }
}

static void print_txt(const uint8_t *frame, int32_t n)
{
    (void) n;

    printf("%s", frame);
}


void scp_mock_print_bin(void)
{
    pp = PRINT_BIN;
}

void scp_mock_print_txt(void)
{
    pp = PRINT_TXT;  
}
