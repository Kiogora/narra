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
#ifndef __SYSTEM_PARAMETERS_H_
#define __SYSTEM_PARAMETERS_H_

#include "narra_types.h"
#include "narra_defines.h"

/**
    @typedef struct system_variables
    @brief Struct containing the different system variables that exist on the system.
**/
typedef struct
{
    char* startup_msg;
#ifdef ALLOW_COMPLEX_STARTUP_MSG_UPDATE
#pragma message("COMPLEX STARTUP MESSAGE UPDATE ALLOWED")
    char* startup_recovery;
    uint32_t* startup_crc_checksum;
#else
#pragma message("SIMPLE STARTUP MESSAGE UPDATE ALLOWED")
#endif
    char* shutdown_msg;
#ifdef ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE
#pragma message("COMPLEX SHUTDOWN MESSAGE UPDATE ALLOWED")
    char* shutdown_recovery;
    uint32_t* shutdown_crc_checksum;
#else
#pragma message("SIMPLE SHUTDOWN MESSAGE UPDATE ALLOWED")
#endif
    char* active_msg;
#ifdef ALLOW_COMPLEX_ACTIVE_MSG_UPDATE
#pragma message("COMPLEX ACTIVE MESSAGE UPDATE ALLOWED")
    char* active_recovery;
    uint32_t* active_crc_checksum;
#else
#pragma message("SIMPLE ACTIVE MESSAGE UPDATE ALLOWED")
#endif
} System_variables;

#endif /*__SYSTEM_PARAMETERS_H_*/
