#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "unity.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_partition.h"
#include "esp_log.h"
#include "crc.h"
#include <string.h>


static const char* TAG = "crc";

TEST_CASE("crc", "[CRC]")
{
    char* test = "123456789";

    TEST_ASSERT_EQUAL_UINT16(crcSlow(test, strlen(test)), CHECK_VALUE);
    crcInit();
    TEST_ASSERT_EQUAL_UINT16(crcFast(test, strlen(test)), CHECK_VALUE);
}
