#ifndef __BLE_H_
#define __BLE_H_

#include <stdint.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

/*Number of profiles*/
#define NARRA_PROFILE_NUM               0x02

/*Application ID*/
#define SYSTEM_APP_ID                   0x00
#define USAGE_APP_ID                    0x01
/*System profile ID*/
#define SYSTEM_PROFILE_APP_IDX          0x00
#define USAGE_PROFILE_APP_IDX           0x01
/*service instance ID*/
#define SYSTEM_SERVICE_INSTANCE_ID      0x00
#define USAGE_SERVICE_INSTANCE_ID       0x01
/*GATT NAME*/
#define PRODUCT_NAME                   "NARRA"

#define CHAR_VAL_LEN_MAX                512
#define UNINITIALISED                   0

typedef struct
{
    uint8_t* prepare_buf;
    int prepare_len;
    uint16_t handle;
} prepare_write_t;

//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.characteristic_presentation_format.xml

typedef enum 
{
boolean=1,
unsigned_2_bit_int,
unsigned_4_bit_int,
unsigned_8_bit_int,
unsigned_12_bit_int,
unsigned_16_bit_int,
unsigned_24_bit_int,
unsigned_32_bit_int,
unsigned_48_bit_int,
unsigned_64_bit_int,
unsigned_128_bit_int,
signed_8_bit_int,
signed_12_bit_int,
signed_16_bit_int,
signed_24_bit_int,
signed_32_bit_int,
signed_48_bit_int,
signed_64_bit_int,
signed_128_bit_int,
IEEE_754_32_bit_float,
IEEE_754_64_bit_floating_point,
IEEE_11073_16_bit_sfloat,
IEEE_11073_32_bit_float,
IEEE_20601_format,
utf_8_string,
utf_16_string,
opaque_Structure,
} format_t;

typedef struct
{
    uint8_t _format;
    int8_t _exponent;
    uint16_t _unit;
    uint8_t _namespace;
    uint16_t _description;
} __attribute__ ((packed)) presentation_t;

///System Attributes State Machine
enum
{
    SYSTEM_IDX_SYSTEM_INFO_SERVICE=0,

    SYSTEM_IDX_DEV_ID_CHAR,
    SYSTEM_IDX_DEV_ID_VAL,

    SYSTEM_IDX_FW_VER_STRING_CHAR,
    SYSTEM_IDX_FW_VER_STRING_VAL,

    SYSTEM_IDX_MAN_NAME_CHAR,
    SYSTEM_IDX_MAN_NAME_VAL,

    SYSTEM_IDX_NB,
};

///Usage Attributes State Machine
enum
{
    USAGE_IDX_USAGE_SERVICE=0,

    USAGE_IDX_DISPLAY_STRING_CHAR,
    USAGE_IDX_DISPLAY_STRING_VAL,
    USAGE_IDX_DISPLAY_STRING_CFG_1,

    USAGE_IDX_STARTUP_STRING_CHAR,
    USAGE_IDX_STARTUP_STRING_VAL,
    USAGE_IDX_STARTUP_STRING_CFG_1,

    USAGE_IDX_SHUTDOWN_STRING_CHAR,
    USAGE_IDX_SHUTDOWN_STRING_VAL,
    USAGE_IDX_SHUTDOWN_STRING_CFG_1,

    USAGE_IDX_DEVICE_STATE_CHAR,
    USAGE_IDX_DEVICE_STATE_VAL,
    USAGE_IDX_DEVICE_STATE_CFG_1,

    USAGE_IDX_NB,
};

void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, 
									esp_ble_gatts_cb_param_t *param);

void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);

esp_attr_value_t* get_usage_state_attribute(void);

esp_attr_value_t* get_usage_runtime_string_attribute(void);

esp_attr_value_t* get_usage_startup_string_attribute(void);

esp_attr_value_t* get_usage_shutdown_string_attribute(void);

void set_ble_event_group(EventGroupHandle_t event_group);

#endif /*__BLE_H_*/
