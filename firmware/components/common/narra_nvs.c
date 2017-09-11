#include "nvs.h"
#include "nvs_flash.h"
#include "esp_partition.h"
#include "esp_err.h"


esp_err_t narra_nvs_init(void)
{
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        const esp_partition_t* nvs_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
                                                                        ESP_PARTITION_SUBTYPE_DATA_NVS,
                                                                        NULL);
        esp_partition_erase_range(nvs_partition, 0, nvs_partition->size);
        err = nvs_flash_init();
    }

    return err;
}
