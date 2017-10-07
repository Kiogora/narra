/*Author: alois mbutura<aloismbutura@gmail.com>

 Copyright 2017 Bitsoko services LTD

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
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
