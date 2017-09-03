# -*- coding: utf-8 -*-
import os
import sys
"""
Author: Alois Mbutura
This script is used to obtain the bluetooth MAC from a connected ESP32. It then logs the information in a file.

The following MAC addresses are derived from the BASE MAC in the EFUSE BLK0.
#ESP_MAC_WIFI_STA
#ESP_MAC_WIFI_SOFTAP
#ESP_MAC_BT
#ESP_MAC_ETH

More info at {IDF_PATH}/components/esp32/system_api.c

For 2 universal MAC addresses, the BT and Wifi are both enabled. Ethernet is disabled. Here:
#ESP_MAC_WIFI_STA=ESP_MAC_WIFI_SOFTAP=BASE MAC.
#ESP_MAC_BT=BASE MAC+1

For 4 Universal MAC addresses, the BT, Wifi and ethernet are all enabled. Here:
#ESP_MAC_WIFI_STA=BASE MAC.
#ESP_MAC_WIFI_SOFTAP=BASE MAC+1
#ESP_MAC_BT=BASE MAC+2
#ESP_MAC_ETH=BASE MAC+3

#The number of MAC addresses are set manually by the menuconfig command. Default is 4 MAC universal addresses.
"""
esptool_path_prefix=os.path.join(os.environ['IDF_PATH'],'components/esptool_py/esptool/')
esptool=os.path.join(esptool_path_prefix, 'esptool.py')
path='../../firmware/ESP32/code'

mac_config_string='CONFIG_NUMBER_OF_UNIVERSAL_MAC_ADDRESS'
config_file='sdkconfig'

def get_bt_mac_lsb_offset(any_path):
    """
    Obains the offset of the BT MAC Least significant byte from the BASE MAC Least significant byte.
    """
    sdkconfig=os.path.join(any_path,config_file)
    config_lines=open(sdkconfig).readlines()
    for line in config_lines:
        if mac_config_string in line:
            split_line=line.split('=')
            if '4' in split_line[1]:
                return 2
            elif '2' in split_line[1]:
                return 1
            else:
                return None

def get_base_mac():
    """
    Obtains the BASE MAC Least significant byte from an ESP32 chip using esptool.
    """
    cmd='read_mac'
    output=os.popen(esptool+' '+cmd).readlines()
    for line in output:
        if 'MAC' in line:
            split_mac=line.split(':')
            del split_mac[0]
            split_mac[-1]=split_mac[-1].rstrip()
            return split_mac

def derive_bt_mac(base_mac,offset):
    """
    Derives the bluetooth MAC from the BASE MAC and the offset from sdkconfig inspection
    """
    base_mac_lsb=int((str(base_mac[-1]).rstrip()), base=16)+offset
    base_mac[-1]=str(hex(base_mac_lsb))
    base_mac[-1]
    bt_mac='-'.join(base_mac)
    bt_mac=bt_mac.replace('0x', '')
    bt_mac=bt_mac.strip()
    return bt_mac

if __name__=='__main__':
    bluetooth_mac=derive_bt_mac(get_base_mac(), get_bt_mac_lsb_offset(path))
    print('The bluetooth MAC derived for the current connected chip is {MAC}'.format(MAC=bluetooth_mac) )
