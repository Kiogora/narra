#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "bt.h"
#include "bta_api.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gattc_api.h"

#include "ble.h"
#include "utf8_decoder.h"

#define GATTS_TABLE_TAG "GATTS_TABLE_DEMO"

/*Number of profiles*/
#define NARRA_PROFILE_NUM 			    2

/*Application ID*/
#define SYSTEM_APP_ID			        0x00
#define USAGE_APP_ID                    0x01
/*System profile ID*/
#define SYSTEM_PROFILE_APP_IDX 			0
#define USAGE_PROFILE_APP_IDX 			1
/*service instance ID*/
#define SYSTEM_SERVICE_INSTANCE_ID	    0
#define USAGE_SERVICE_INSTANCE_ID	    1
/*GATT NAME*/
#define ADVERTISED_DEVICE_NAME         "Narra_01"
#define DEV_ID_LEN                      8

#define CHAR_VAL_LEN_MAX		0xFF
uint16_t system_handle_table[SYSTEM_IDX_NB];
uint16_t usage_handle_table[USAGE_IDX_NB];

char *string =NULL;
uint8_t state=0x01;


/**********************************************ADVERTISING****************************************************/
static uint8_t raw_adv_data[] = {
0x02, // Len
0x01, // Type Flags
0x06, // GENERAL_DISC_MODE 0x02 | BR_EDR_NOT_SUPPORTED 0x04

0x03, // Len
0x03, // Type 16-Bit UUID
0xAA, // Eddystone UUID 2 -> 0xFEAA LSB
0xFE, // Eddystone UUID 1 MSB
0x13, // Length of Beacon Data
0x16, // Type Service Data
0xAA, // Eddystone UUID 2 -> 0xFEAA LSB
0xFE, // Eddystone UUID 1 MSB
0x10, // Eddystone Frame Type
0x04, // Beacons TX power at 0m
0x03, // URL Scheme 'https://'
0x67, // URL add  1 'g'
0x6F, // URL add  2 'o'
0x6F, // URL add  3 'o'
0x2E, // URL add  4 '.'
0x67, // URL add  5 'g'
0x6C, // URL add  6 'l'
0x2F, // URL add  7 '/'
0x32, // URL add  8 '2'
0x79, // URL add  9 'y'
0x43, // URL add 10 'C'
0x36, // URL add 11 '6'
0x4B, // URL add 12 'K'
0x58  // URL add 13 'X'
};
static uint8_t raw_scan_rsp_data[] = {
9,    // Length
0x09, //<<AD Type-Complete local name>>
0x4E, //N
0x61, //a
0x72, //r
0x72, //r
0x61, //a
0x5f, //
0x30, //0
0x31, //1
17,   //Length
0x06, //<<AD type-Incomplete list 128 bit UUID's>>
0x93, //lsb
0x53,
0x03,
0x97,
0x22,
0x59,
0x53,
0x9c,
0x6d,
0x42,
0xb6,
0xbc,
0x46,
0x95,
0x70,
0xdb  //msb
};

static esp_ble_adv_params_t bitsoko_advert_params = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    //.peer_addr            =
    //.peer_addr_type       =
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    ESP_LOGE(GATTS_TABLE_TAG, "GAP_EVT, event %d\n", event);

    switch (event) 
    {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
        esp_ble_gap_start_advertising(&bitsoko_advert_params);
        break;
    case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        esp_ble_gap_start_advertising(&bitsoko_advert_params);
        break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_RAW_SET_COMPLETE_EVT:
        esp_ble_gap_start_advertising(&bitsoko_advert_params);
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTS_TABLE_TAG, "Advertising start failed\n");
        }
        break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(GATTS_TABLE_TAG, "Advertising stop failed\n");
        }
        else {
            ESP_LOGI(GATTS_TABLE_TAG, "Stop adv successfully\n");
        }
        break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
         ESP_LOGI(GATTS_TABLE_TAG, 
                  "update connetion params status=%d, min_int=%d, max_int=%d, conn_int=%d, latency=%d, timeout=%d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
        break;
    default:
        break;
    }
}

/******************************************END ADVERTISING***************************************************/

/********************************************GATT SERVER ************************************************/

static prepare_write_t prepare_write_tracker;

/************** GATT ATTRIBUTES ***************/

esp_attr_value_t get_attribute()
{

    esp_attr_value_t usage_state_attribute = 
    {
        .attr_max_len   = CHAR_VAL_LEN_MAX,
        .attr_value     = (uint8_t *)&state,
        .attr_len		= sizeof(usage_state_attribute.attr_value /*state*/),
    };

    esp_attr_value_t usage_string_attribute = 
    {
        .attr_max_len   = CHAR_VAL_LEN_MAX,
        .attr_value     = (uint8_t *)string,
        .attr_len		= strlen( (char *)usage_string_attribute.attr_value /*string*/ ),
    };
}
/***********************************************/
struct gatts_profile_inst {
    esp_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_handle;
    esp_gatt_srvc_id_t service_id;
    uint16_t char_handle;
    esp_bt_uuid_t char_uuid;
    esp_gatt_perm_t perm;
    esp_gatt_char_prop_t property;
    uint16_t descr_handle;
    esp_bt_uuid_t descr_uuid;
};

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by ESP_GATTS_REG_EVT */
static struct gatts_profile_inst narra_profile_table[NARRA_PROFILE_NUM] = {
    [SYSTEM_PROFILE_APP_IDX] = {
        .gatts_cb = system_profile_event_handler,
        .gatts_if = ESP_GATT_IF_NONE,       /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
    },
    [USAGE_PROFILE_APP_IDX] = {
        .gatts_cb = usage_profile_event_handler,
        .gatts_if = ESP_GATT_IF_NONE,       /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
    },
    
};

#define CHAR_DECLARATION_SIZE   (sizeof(uint8_t))
//Device info Service
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.device_information.xml
static const uint16_t device_info_svc = ESP_GATT_UUID_DEVICE_INFO_SVC;
//Reads are mandatory according to the service description xml for interoperability
static const esp_gatt_char_prop_t  sys_char_prop_indicate = ESP_GATT_CHAR_PROP_BIT_INDICATE;
static const esp_gatt_char_prop_t  sys_char_prop_notify = ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static const esp_gatt_char_prop_t  sys_char_prop_read = ESP_GATT_CHAR_PROP_BIT_READ;
static const esp_gatt_char_prop_t  sys_char_prop_read_write = ESP_GATT_CHAR_PROP_BIT_WRITE|ESP_GATT_CHAR_PROP_BIT_READ;
//Service type uuid
static const uint16_t sys_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
//GATT declaration
static const uint16_t sys_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
//GATT descriptor
static const uint16_t sys_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
//Device info service characteristics implemented
static const uint16_t character_manufacturer_name_uuid = ESP_GATT_UUID_MANU_NAME;
static const uint8_t  man_name_val[14]={0x42,0x49,0x54,0x53,0x4F,0x4B,0x4F,0x5F,0x4C,0x54,0x44,0x5F,0x4B,0x45};

static const uint16_t character_fw_ver_string_uuid = ESP_GATT_UUID_FW_VERSION_STR;
static const uint8_t  fw_ver_string_val[3] = {0x35,0x2e,0x31};

//Device ID with Byte Order Mark for endianness identification.
static const uint16_t character_dev_id_uuid = ESP_GATT_UUID_SYSTEM_ID;
static const uint8_t  dev_id_val[DEV_ID_LEN] = {0x24,0x0a,0xc4,0xFF,0xFE,0x05,0x8a,0x46};

static const esp_gatts_attr_db_t system_gatt_db[SYSTEM_IDX_NB] =
{
    [SYSTEM_IDX_SYSTEM_INFO_SERVICE]    =  
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&sys_primary_service_uuid, ESP_GATT_PERM_READ,
      sizeof(uint16_t), sizeof(uint16_t), (uint8_t *)&device_info_svc}},

    [SYSTEM_IDX_MAN_NAME_CHAR]       	=    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&sys_character_declaration_uuid, ESP_GATT_PERM_READ, 
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&sys_char_prop_read}},

    [SYSTEM_IDX_MAN_NAME_VAL]        	=    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_manufacturer_name_uuid, ESP_GATT_PERM_READ, 
    sizeof(man_name_val), sizeof(man_name_val), (uint8_t *)man_name_val}},

    [SYSTEM_IDX_DEV_ID_CHAR]     	    =    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&sys_character_declaration_uuid, ESP_GATT_PERM_READ, 
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&sys_char_prop_read}},

    [SYSTEM_IDX_DEV_ID_VAL]     	    =    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_dev_id_uuid, ESP_GATT_PERM_READ, 
    sizeof(dev_id_val), sizeof(dev_id_val), (uint8_t *)dev_id_val}},

    [SYSTEM_IDX_FW_VER_STRING_CHAR]     =    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&sys_character_declaration_uuid, ESP_GATT_PERM_READ, 
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&sys_char_prop_read}},

    [SYSTEM_IDX_FW_VER_STRING_VAL]     	=    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_fw_ver_string_uuid, ESP_GATT_PERM_READ, 
    sizeof(fw_ver_string_val), sizeof(fw_ver_string_val), (uint8_t *)fw_ver_string_val}},

};

//Usage Service
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.device_information.xml
//Reads are mandatory according to the service description xml for interoperability
static const esp_gatt_char_prop_t  usage_char_prop_indicate = ESP_GATT_CHAR_PROP_BIT_INDICATE;
static const esp_gatt_char_prop_t  usage_char_prop_notify = ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static const esp_gatt_char_prop_t  usage_char_prop_read = ESP_GATT_CHAR_PROP_BIT_READ;
static const esp_gatt_char_prop_t  usage_char_prop_read_write = ESP_GATT_CHAR_PROP_BIT_WRITE|
                                                                ESP_GATT_CHAR_PROP_BIT_READ;
presentation_t utf8_presentation = 
{
    ._format=utf_8_string,
    ._exponent=0,
    ._unit=0,
    ._namespace=0,
    ._description=0,
};

presentation_t bool_presentation = 
{
    ._format=boolean,
    ._exponent=0,
    ._unit=0,
    ._namespace=0,
    ._description=0,
};

//Service type uuid
static const uint16_t usage_primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
//GATT declaration
static const uint16_t usage_character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
//GATT presentation
static const uint16_t usage_character_char_presentation_uuid = ESP_GATT_UUID_CHAR_PRESENT_FORMAT;
//GATT descriptor
static const uint16_t usage_character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;

//Usage service characteristics implemented
//db709546-bcb6-426d-9c53-592297035393
static const uint8_t usage_svc[ESP_UUID_LEN_128] =
{
/* LSB <-----------------------------------------------------------------> MSB */
0x93,0x53,0x03,0x97,0x22,0x59,0x53,0x9c,0x6d,0x42,0xb6,0xbc,0x46,0x95,0x70,0xdb,
};

//8f5d6995-35e5-4a1f-8280-a70697147c19
static const uint8_t character_display_string_uuid[ESP_UUID_LEN_128] =
{
/* LSB <---------------------------------------------------------------> MSB */
0x19,0x7c,0x14,0x97,0x06,0xa7,0x80,0x82,0x1f,0x4a,0xe5,0x35,0x95,0x69,0x5d,0x8f,
};
static const uint8_t  display_string_val[5] = {0x48,0x45,0x4c,0x4c,0x4f};

//7351f963-fbc7-42cc-88ca-dc084155c2db
static const uint8_t character_device_state_uuid[ESP_UUID_LEN_128] =
{
/* LSB <---------------------------------------------------------------> MSB */
0xdb,0xc2,0x55,0x41,0x08,0xdc,0xca,0x88,0xcc,0x42,0xc7,0xfb,0x63,0xf9,0x51,0x73,
};
static const uint8_t  device_state_val[1] = {0x01};
//5c5be607-4f2e-4f8e-b2b2-c16116c6783c
static const uint8_t character_device_mtu_uuid[ESP_UUID_LEN_128] =
{
/* LSB <---------------------------------------------------------------> MSB */
0x3c,0x78,0xc6,0x16,0x61,0xc1,0xb2,0xb2,0x8e,0x4f,0x2e,0x4f,0x07,0xe6,0x5b,0x5c,
};
static const esp_gatts_attr_db_t usage_gatt_db[USAGE_IDX_NB] =
{
    [USAGE_IDX_USAGE_SERVICE]               =  
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&usage_primary_service_uuid, ESP_GATT_PERM_READ,
      sizeof(usage_svc), sizeof(usage_svc), (uint8_t *)usage_svc}},

    [USAGE_IDX_DISPLAY_STRING_CHAR]         =
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&usage_character_declaration_uuid, ESP_GATT_PERM_READ,
      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,(uint8_t *)&usage_char_prop_read_write}},

    [USAGE_IDX_DISPLAY_STRING_VAL]          =    
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_128, (uint8_t *)&character_display_string_uuid, ESP_GATT_PERM_READ|
      ESP_GATT_PERM_WRITE, sizeof(display_string_val), sizeof(display_string_val), (uint8_t *)display_string_val}},

    [USAGE_IDX_DISPLAY_STRING_CFG_1]     	=    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&usage_character_char_presentation_uuid, ESP_GATT_PERM_READ,
     sizeof(utf8_presentation),sizeof(utf8_presentation), (uint8_t *)&utf8_presentation}},

    [USAGE_IDX_DEVICE_STATE_CHAR]     	     =    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&usage_character_declaration_uuid, ESP_GATT_PERM_READ, 
    CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *)&usage_char_prop_read_write}},

    [USAGE_IDX_DEVICE_STATE_VAL]     	     =    
    {{ESP_GATT_RSP_BY_APP}, {ESP_UUID_LEN_128, (uint8_t *)&character_device_state_uuid, ESP_GATT_PERM_READ|
    ESP_GATT_PERM_WRITE, sizeof(device_state_val), sizeof(device_state_val), (uint8_t *)device_state_val}},

    [USAGE_IDX_DEVICE_STATE_CFG_1]      =    
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&usage_character_char_presentation_uuid, ESP_GATT_PERM_READ,
     sizeof(bool_presentation), sizeof(bool_presentation), (uint8_t *)&bool_presentation}},
};

static void system_profile_event_handler(esp_gatts_cb_event_t event, 
										esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) 
{
    ESP_LOGE(GATTS_TABLE_TAG, "event = %x\n",event);
    switch (event) {
    	case ESP_GATTS_REG_EVT:
		    ESP_LOGI(GATTS_TABLE_TAG, "%s %d\n", __func__, __LINE__);
            //TODO Redo the advertised name as there may be more than one beacon in a vicinity.
        	esp_ble_gap_set_device_name(ADVERTISED_DEVICE_NAME);

        	ESP_LOGI(GATTS_TABLE_TAG, "%s %d\n", __func__, __LINE__);

            esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));
            esp_ble_gap_config_scan_rsp_data_raw(raw_scan_rsp_data, sizeof(raw_scan_rsp_data));

        	ESP_LOGI(GATTS_TABLE_TAG, "%s %d\n", __func__, __LINE__);

		    esp_ble_gatts_create_attr_tab(system_gatt_db, gatts_if, SYSTEM_IDX_NB, SYSTEM_SERVICE_INSTANCE_ID);
       	break;
    	case ESP_GATTS_READ_EVT:
       	 break;
    	case ESP_GATTS_WRITE_EVT: 
      	 	break;
    	case ESP_GATTS_EXEC_WRITE_EVT:
		break;
    	case ESP_GATTS_MTU_EVT:
		break;
   	 case ESP_GATTS_CONF_EVT:
		break;
    	case ESP_GATTS_UNREG_EVT:
        	break;
    	case ESP_GATTS_DELETE_EVT:
        	break;
    	case ESP_GATTS_START_EVT:
        	break;
    	case ESP_GATTS_STOP_EVT:
        	break;
    	case ESP_GATTS_CONNECT_EVT:
        	break;
    	case ESP_GATTS_DISCONNECT_EVT:
        esp_ble_gap_start_advertising(&bitsoko_advert_params);
		break;
    	case ESP_GATTS_OPEN_EVT:
		break;
    	case ESP_GATTS_CANCEL_OPEN_EVT:
		break;
    	case ESP_GATTS_CLOSE_EVT:
		break;
    	case ESP_GATTS_LISTEN_EVT:
		break;
    	case ESP_GATTS_CONGEST_EVT:
		break;
    case ESP_GATTS_CREAT_ATTR_TAB_EVT:{
        ESP_LOGI(GATTS_TABLE_TAG, "The number handle =%x\n",param->add_attr_tab.num_handle);
        if (param->add_attr_tab.status != ESP_GATT_OK){
            ESP_LOGE(GATTS_TABLE_TAG, "Create attribute table failed, error code=0x%x", param->add_attr_tab.status);
        }
        else if (param->add_attr_tab.num_handle != SYSTEM_IDX_NB){
            ESP_LOGE(GATTS_TABLE_TAG, "Create attribute table abnormally, num_handle (%d) \
                    doesn't equal to SYSTEM_IDX_NB(%d)", param->add_attr_tab.num_handle, SYSTEM_IDX_NB);
        }
        else {
            ESP_LOGE(GATTS_TABLE_TAG, "Reached create sys attribute tab");
            memcpy(system_handle_table, param->add_attr_tab.handles, sizeof(system_handle_table));
            esp_ble_gatts_start_service(system_handle_table[SYSTEM_IDX_SYSTEM_INFO_SERVICE]);
        }
        break;
         }

    default:
        break;
    }
}

//Remember The Max MTU negotiable ESP_GATT_MAX_MTU_SIZE(517) < ESP_GATT_MAX_ATTR_LEN(600)
static void usage_profile_read_event_handler(esp_attr_value_t attribute, esp_gatts_cb_event_t event, 
                                             esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    if (param->read.handle == usage_handle_table[USAGE_IDX_DEVICE_STATE_VAL])
    {
        read_attribute_by_app(attribute, event, gatts_if, param);
    }
    else if (param->read.handle == usage_handle_table[USAGE_IDX_DISPLAY_STRING_VAL])
    {
        read_attribute_by_app(attribute, event, gatts_if, param);
    }
    else
    { 
        ;
    }  
}

static void read_attribute_by_app(esp_attr_value_t attribute, esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, 
                                  esp_ble_gatts_cb_param_t *param)
{
    esp_gatt_status_t status = ESP_GATT_OK;

    if(attribute.attr_len > attribute.attr_max_len)
    {
        attribute.attr_len = attribute.attr_max_len;
    }

    esp_gatt_rsp_t rsp;
    memset(&rsp, 0, sizeof(esp_gatt_rsp_t));

    if (param->read.offset < attribute.attr_len)
    {
        rsp.attr_value.len = (attribute.attr_len) - param->read.offset;
        rsp.attr_value.offset = param->read.offset;
        memcpy(rsp.attr_value.value, attribute.attr_value+param->read.offset, rsp.attr_value.len);
    }
    rsp.attr_value.handle = param->read.handle;
    rsp.attr_value.auth_req = ESP_GATT_AUTH_REQ_NONE;

    esp_err_t response_err = esp_ble_gatts_send_response(gatts_if, param->read.conn_id, param->read.trans_id,
                                                         status, &rsp);
    if (response_err != ESP_OK)
    {
       LOG_ERROR("Send response error\n");
    }

    if (status != ESP_GATT_OK)
    {
        return;
    }
}

static void usage_profile_prepare_write_event_handler(esp_gatt_if_t gatts_if, prepare_write_t *prepare_write_state,
                                                      esp_ble_gatts_cb_param_t *param)
{
    esp_gatt_status_t status = ESP_GATT_OK;
    if (param->write.need_rsp)
    {
        if (param->write.is_prep)
        {
            if (prepare_write_env->prepare_buf == NULL)
            {
                prepare_write_env->prepare_buf = (uint8_t *)malloc(CHAR_VAL_LEN_MAX * sizeof(uint8_t));
                prepare_write_env->prepare_len = 0;
                prepare_write_env->handle = 0;

                if (prepare_write_env->prepare_buf == NULL)
                {
                    LOG_ERROR("Gatt_server insufficient heap memory resource\n");

                    status = ESP_GATT_NO_RESOURCES;
                }
            }
            else
            {
                if(param->write.offset > CHAR_VAL_LEN_MAX)
                {
                    status = ESP_GATT_INVALID_OFFSET;
                }
                else if ((param->write.offset + param->write.len) > CHAR_VAL_LEN_MAX) 
                {
                    status = ESP_GATT_INVALID_ATTR_LEN;
                }
            }

            esp_gatt_rsp_t *gatt_rsp = (esp_gatt_rsp_t *)malloc(sizeof(esp_gatt_rsp_t));
            memset(gatt_rsp, 0, sizeof(esp_gatt_rsp_t));

            gatt_rsp->attr_value.len = param->write.len;
            gatt_rsp->attr_value.handle = param->write.handle;
            gatt_rsp->attr_value.offset = param->write.offset;
            gatt_rsp->attr_value.auth_req = ESP_GATT_AUTH_REQ_NONE;

            memcpy(gatt_rsp->attr_value.value, param->write.value, param->write.len);
            esp_err_t response_err = esp_ble_gatts_send_response(gatts_if, 
                                                                 param->write.conn_id, 
                                                                 param->write.trans_id, 
                                                                 status, 
                                                                 gatt_rsp);
            if (response_err != ESP_OK)
            {
               LOG_ERROR("Send response error\n");
            }
            free(gatt_rsp);
            if (status != ESP_GATT_OK)
            {
                return;
            }

            memcpy(prepare_write_env->prepare_buf + param->write.offset,
                   param->write.value,
                   param->write.len);

            prepare_write_env->prepare_len += param->write.len;
            prepare_write_env->handle =  param->write.handle;
        }
        else
        {
            //BLE stack is not ready to perform prep_write, send NULL response to client to control communication.
            esp_ble_gatts_send_response(gatts_if, param->write.conn_id, param->write.trans_id, status, NULL);
        }
    }
}

static void clear_write_buffer(prepare_write_t *prepare_write_env)
{
    if (prepare_write_env->prepare_buf)
    {
        free(prepare_write_env->prepare_buf);
        prepare_write_env->prepare_buf = NULL;
    }
    prepare_write_env->prepare_len = 0;
    prepare_write_env->handle = 0;
} 

static void usage_profile_exec_write_event_handler(prepare_write_t* prepare_write_env,
                                                   esp_ble_gatts_cb_param_t *param)
{
/*    
    if (param->write.handle == usage_handle_table[USAGE_IDX_DEVICE_STATE_VAL])
    {
        write_attribute_by_app(attribute, event, gatts_if, param);
    }
    else if (param->write.handle == usage_handle_table[USAGE_IDX_DISPLAY_STRING_VAL])
    {
        write_attribute_by_app(attribute, event, gatts_if, param);
    }
    else
    {
        ;
    }
*/    
    if (param->exec_write.exec_write_flag == ESP_GATT_PREP_WRITE_EXEC)
    {
        //Zero out the memory block
        memset(prepare_write_env->&prepare_buf, 0, attributeptr->attr_len);
        memcpy(attributeptr->attr_value, prepare_write_env->&prepare_buff, prepare_write_env->prepare_len)
        attribute.attr_len = prepare_write_env->prepare_len;
    }
    else
    {
        ESP_LOGI(GATTS_TAG,"ESP_GATT_PREP_WRITE_CANCEL");
    }
    clear_write_buffer(prepare_write_env);
}

static void usage_profile_event_handler(esp_gatts_cb_event_t event, 
										esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) 
{
    ESP_LOGE(GATTS_TABLE_TAG, "event decimal number= %d\n",event);
    switch (event) {
    	case ESP_GATTS_REG_EVT:
        	ESP_LOGI(GATTS_TABLE_TAG, "%s %d\n", __func__, __LINE__);
		    esp_ble_gatts_create_attr_tab(usage_gatt_db, gatts_if, USAGE_IDX_NB, USAGE_SERVICE_INSTANCE_ID);
       	break;
    	case ESP_GATTS_READ_EVT:
            usage_profile_read_event_handler(event, gatts_if, param);
       	 break;
    	case ESP_GATTS_WRITE_EVT:
            usage_profile_prepare_write_event_handler(event, gatts_if, param);
      	 	break;
    	case ESP_GATTS_EXEC_WRITE_EVT:
            usage_profile_exec_write_event_handler(prepare_write_tracker, param);
		break;
    	case ESP_GATTS_MTU_EVT:
		break;
   	 case ESP_GATTS_CONF_EVT:
		break;
    	case ESP_GATTS_UNREG_EVT:
        	break;
    	case ESP_GATTS_DELETE_EVT:
        	break;
    	case ESP_GATTS_START_EVT:
        	break;
    	case ESP_GATTS_STOP_EVT:
        	break;
    	case ESP_GATTS_CONNECT_EVT:
        	break;
    	case ESP_GATTS_DISCONNECT_EVT:
		break;
    	case ESP_GATTS_OPEN_EVT:
		break;
    	case ESP_GATTS_CANCEL_OPEN_EVT:
		break;
    	case ESP_GATTS_CLOSE_EVT:
		break;
    	case ESP_GATTS_LISTEN_EVT:
		break;
    	case ESP_GATTS_CONGEST_EVT:
		break;
    case ESP_GATTS_CREAT_ATTR_TAB_EVT:{
        ESP_LOGI(GATTS_TABLE_TAG, "The number handle =%x\n",param->add_attr_tab.num_handle);
        if (param->add_attr_tab.status != ESP_GATT_OK)
        {
            ESP_LOGE(GATTS_TABLE_TAG, "Create attribute table failed, error code=0x%x", param->add_attr_tab.status);
        }
        else if (param->add_attr_tab.num_handle != USAGE_IDX_NB)
        {
            ESP_LOGE(GATTS_TABLE_TAG, "Create attribute table abnormally, num_handle (%d) \
                    doesn't equal to USAGE_IDX_NB(%d)", param->add_attr_tab.num_handle, USAGE_IDX_NB);
        }
        else 
        {
            ESP_LOGE(GATTS_TABLE_TAG, "Reached create usage attribute tab");
            memcpy(usage_handle_table, param->add_attr_tab.handles, sizeof(usage_handle_table));
            esp_ble_gatts_start_service(usage_handle_table[USAGE_IDX_USAGE_SERVICE]);
        }
        break;
         }
    default:
        break;
    }
}

static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, 
									esp_ble_gatts_cb_param_t *param)
{
    ESP_LOGI(GATTS_TABLE_TAG, "EVT %d, gatts if %d\n", event, gatts_if);

    /* If event is register event, store the gatts_if for each profile */
    if (event == ESP_GATTS_REG_EVT) {
        if (param->reg.status == ESP_GATT_OK) 
        {
            narra_profile_table[param->reg.app_id].gatts_if = gatts_if;
        } 
        else 
        {
            ESP_LOGI(GATTS_TABLE_TAG, "Reg app failed, app_id %04x, status %d\n",
                    param->reg.app_id, 
                    param->reg.status);
            return;
        }
    }
	
    do {
        int idx;
        for (idx = 0; idx < NARRA_PROFILE_NUM; idx++) 
        {
            if (gatts_if == ESP_GATT_IF_NONE || gatts_if == narra_profile_table[idx].gatts_if) 
                {
                    if (narra_profile_table[idx].gatts_cb) 
                    {
                        narra_profile_table[idx].gatts_cb(event, gatts_if, param);
                    }
                }
        }
    } while (0);
}

/*****************************************END GATT SERVER ************************************************/
void bleTask(void *pvParameters)
{
    esp_err_t ret;

    // Initialize NVS.
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret)
    {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed\n", __func__);
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM);
    if (ret)
    {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed\n", __func__);
        return;
    }

    ESP_LOGI(GATTS_TABLE_TAG, "%s init bluetooth\n", __func__);
    ret = esp_bluedroid_init();
    if (ret)
    {
        ESP_LOGE(GATTS_TABLE_TAG, "%s init bluetooth failed\n", __func__);
        return;
    }
    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable bluetooth failed\n", __func__);
        return;
    }
    string ="What the fuck are you saying bitch!!!!";
    esp_ble_gatts_register_callback(gatts_event_handler);
    esp_ble_gap_register_callback(gap_event_handler);
    esp_ble_gatts_app_register(SYSTEM_APP_ID);
    esp_ble_gatts_app_register(USAGE_APP_ID);

    while(1)
    {
        ;
    }
}
