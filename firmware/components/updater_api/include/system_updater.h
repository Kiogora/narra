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
#ifndef __SYSTEM_UPDATER_H_
#define __SYSTEM_UPDATER_H_

#include "narra_types.h"
#include "narra_defines.h"
#include "narra_parameters.h"
#include "narra_system.h"

#if defined ALLOW_SIMPLE_STARTUP_MSG_UPDATE || defined ALLOW_COMPLEX_STARTUP_MSG_UPDATE
int32_t system_update_startup(char* new_startup_msg);
#endif
#if defined ALLOW_SIMPLE_ACTIVE_MSG_UPDATE || defined ALLOW_COMPLEX_ACTIVE_MSG_UPDATE
int32_t system_update_active(char* new_active_msg);
#endif
#if defined ALLOW_SIMPLE_SHUTDOWN_MSG_UPDATE || defined ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE
int32_t system_update_shutdown(char* new_shutdown_msg);
#endif

#endif /*__SYSTEM_UPDATER_H_*/

//TODO: Section the update function internals above to change based on the above preprocessor macros. Maybe edit the bootloader?
