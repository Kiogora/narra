#ifndef __BLE_H_
#define __BLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static void system_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, 
                                         esp_ble_gatts_cb_param_t *param);

static void usage_profile_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, 
                                        esp_ble_gatts_cb_param_t *param);

static void read_attribute_by_app(esp_attr_value_t attribute, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, 
                                  esp_ble_gatts_cb_param_t *param);

static void usage_profile_read_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, 
                                             esp_ble_gatts_cb_param_t *param);

static void usage_profile_prepare_write_event_handler(esp_gatt_if_t gatts_if, prepare_write_t *prepare_write_state,
                                                      esp_ble_gatts_cb_param_t *param);

static void usage_profile_exec_write_event_handler(esp_attr_value_t attribute, prepare_write_t *prepare_write_env,
                                                   esp_ble_gatts_cb_param_t *param);

static void clear_write_buffer(prepare_write_t *prepare_write_env);

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

    USAGE_IDX_DEVICE_STATE_CHAR,
    USAGE_IDX_DEVICE_STATE_VAL,
    USAGE_IDX_DEVICE_STATE_CFG_1,

    USAGE_IDX_NB,
};

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

typedef struct
{
    uint8_t* prepare_buf;
    int prepare_len;
} prepare_write_t;

#endif /*__BLE_H_*/
