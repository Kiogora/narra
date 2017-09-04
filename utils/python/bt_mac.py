# -*- coding: utf-8 -*-
import os
import sys
import subprocess
"""
Author: Alois Mbutura

This script is used to obtain the bluetooth MAC from a connected ESP32. It then logs the information in a file.
The number of Universal MAC addresses are set manually by the menuconfig command. Default is 4 MAC universal addresses.

The following MAC addresses are derived from the BASE MAC in the EFUSE BLK0.
#ESP_MAC_WIFI_STA
#ESP_MAC_WIFI_SOFTAP
#ESP_MAC_BT
#ESP_MAC_ETH

For 2 universal MAC addresses, the BT and Wifi are both enabled. Ethernet is disabled. Here:
#ESP_MAC_WIFI_STA=ESP_MAC_WIFI_SOFTAP=BASE MAC.
#ESP_MAC_BT=BASE MAC+1

For 4 Universal MAC addresses, the BT, Wifi and ethernet are all enabled. Here:
#ESP_MAC_WIFI_STA=BASE MAC.
#ESP_MAC_WIFI_SOFTAP=BASE MAC+1
#ESP_MAC_BT=BASE MAC+2
#ESP_MAC_ETH=BASE MAC+3
"""
def get_bt_mac_lsb_offset(any_path,config_file):
    """
    Obains the offset of the BT_MAC LSB from the BASE_MAC LSB by sdkconfig inspection.
    """
    mac_sdkconfig_string='CONFIG_NUMBER_OF_UNIVERSAL_MAC_ADDRESS'

    sdkconfig=os.path.join(any_path,config_file)
    config_lines=open(sdkconfig).readlines()
    for line in config_lines:
        if mac_sdkconfig_string in line:
            split_line=line.split('=')
            if '4' in split_line[1]:
                return 2
            elif '2' in split_line[1]:
                return 1
            else:
                print("Unable to find valid value of sdkconfig variable {mac_var}"
                      .format(mac_var=mac_sdkconfig_string))
                sys.exit(1)

def get_base_mac(esptool_script):
    """
    Obtains the BASE_MAC from an ESP32 chip using the "python esptool.py read_mac" command.
    """
    esptool_cmd='read_mac'
    mac_identifier='MAC'

    pipe=subprocess.Popen([esptool_script,esptool_cmd],stdout=subprocess.PIPE)
    esp32_reply=pipe.communicate()
    esp32_reply=esp32_reply[0].decode().split('\n')
    if esp32_reply[-1] != 2:
        for line in esp32_reply:
            if mac_identifier in line:
                split_mac=line.split(':')
                del split_mac[0]
                return split_mac
    else:
        print("Subprocess exited with status code {code}".format(code=esp32_reply[-1]))
        sys.exit(1)

def derive_bt_mac(base_mac,offset):
    """
    Derives the BT_MAC from the BASE_MAC and the BT_MAC LSB offset.
    """
    base_mac_lsb=int(str(base_mac[-1]), base=16)+offset
    base_mac[-1]=format(base_mac_lsb, 'x')
    bt_mac='-'.join(base_mac)
    return bt_mac.strip()

if __name__=='__main__':
    sdkconfig_path_rel_prefix='../../firmware/ESP32/code'
    sdkconfig='sdkconfig'

    esptool_path_rel_prefix='components/esptool_py/esptool/'
    esptool_path_prefix=os.path.join(os.environ['IDF_PATH'], esptool_path_rel_prefix)
    esptool=os.path.join(esptool_path_prefix, 'esptool.py')

    bluetooth_mac=derive_bt_mac(get_base_mac(esptool), get_bt_mac_lsb_offset(sdkconfig_path_rel_prefix, sdkconfig))
    print('The bluetooth MAC for the current connected chip will be {MAC}'.format(MAC=bluetooth_mac))
