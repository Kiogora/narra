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
#include "system_loader.h"
#include <string.h>

static const char* TAG = "system_loader";

TEST_CASE("system_loader", "[loader]")
{
    System_variables system_variables;
    TEST_ESP_OK(system_loader(&system_variables));
}
