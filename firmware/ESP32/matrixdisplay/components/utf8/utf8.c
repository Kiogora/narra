// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
#include <stdint.h>
#include <stddef.h>
#include "utf8.h"

/*Private functions*/
/*******************/
static uint32_t decode(uint32_t* state, uint32_t* codep, uint32_t byte) 
{
    uint32_t type = utf8d[byte];
    *codep = (*state != UTF8_ACCEPT) ? (byte & 0x3fu) | (*codep << 6) : (0xff >> type) & (byte);
    *state = utf8d[256 + *state*16 + type];
    return *state;
}

/*Public functions*/
/******************/
int check_valid_UTF8(char* _bytestring, size_t* _count)
{
    uint32_t codepoint;
    uint32_t state = 0;

    for (*_count = 0; *_bytestring; ++_bytestring)
    {
        if (!decode(&state, &codepoint, *_bytestring)){ *_count += 1;}
    }
    return state != UTF8_ACCEPT;
}

void utf8string_create(uint32_t* _codepointbuffer, char* _bytestring)
{
    uint32_t codepoint;
    uint32_t state = 0;
    for (int k = 0; *_bytestring; ++_bytestring)
    {
        if (!decode(&state, &codepoint, *_bytestring))
        {
            *(_codepointbuffer + (sizeof(uint32_t) * k) )  = codepoint;
            k++;
        }
    }
}
