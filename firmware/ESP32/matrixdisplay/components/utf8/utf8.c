// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
#include <stdint.h>
#include "utf8.h"

uint32_t decode(uint32_t* state, uint32_t* codep, uint32_t byte) 
{
    uint32_t type = utf8d[byte];
    *codep = (*state != UTF8_ACCEPT) ? (byte & 0x3fu) | (*codep << 6) : (0xff >> type) & (byte);
    *state = utf8d[256 + *state*16 + type];
    return *state;
}

