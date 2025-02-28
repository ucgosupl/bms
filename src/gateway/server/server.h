#pragma once

enum packet_type
{
    PACKET_BIN,
    PACKET_TXT,
    PACKET_MAX,
};

void server_init(enum packet_type pt);
