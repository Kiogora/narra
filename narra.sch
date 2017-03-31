EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:narra-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED_RGB D1
U 1 1 58DE0E2B
P 3900 1000
F 0 "D1" H 3900 1370 50  0000 C CNN
F 1 "LED_RGB" H 3900 650 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 950 50  0001 C CNN
F 3 "" H 3900 950 50  0001 C CNN
	1    3900 1000
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB D2
U 1 1 58DE0E90
P 3900 1850
F 0 "D2" H 3900 2220 50  0000 C CNN
F 1 "LED_RGB" H 3900 1500 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 1800 50  0001 C CNN
F 3 "" H 3900 1800 50  0001 C CNN
	1    3900 1850
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB D3
U 1 1 58DE125F
P 3900 2650
F 0 "D3" H 3900 3020 50  0000 C CNN
F 1 "LED_RGB" H 3900 2300 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 2600 50  0001 C CNN
F 3 "" H 3900 2600 50  0001 C CNN
	1    3900 2650
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB D4
U 1 1 58DE1265
P 3900 3500
F 0 "D4" H 3900 3870 50  0000 C CNN
F 1 "LED_RGB" H 3900 3150 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 3450 50  0001 C CNN
F 3 "" H 3900 3450 50  0001 C CNN
	1    3900 3500
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB D5
U 1 1 58DE1E6F
P 3900 4300
F 0 "D5" H 3900 4670 50  0000 C CNN
F 1 "LED_RGB" H 3900 3950 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 4250 50  0001 C CNN
F 3 "" H 3900 4250 50  0001 C CNN
	1    3900 4300
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB D6
U 1 1 58DE1E75
P 3900 5150
F 0 "D6" H 3900 5520 50  0000 C CNN
F 1 "LED_RGB" H 3900 4800 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 5100 50  0001 C CNN
F 3 "" H 3900 5100 50  0001 C CNN
	1    3900 5150
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB D7
U 1 1 58DE1E87
P 3900 5950
F 0 "D7" H 3900 6320 50  0000 C CNN
F 1 "LED_RGB" H 3900 5600 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 5900 50  0001 C CNN
F 3 "" H 3900 5900 50  0001 C CNN
	1    3900 5950
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB D8
U 1 1 58DE1E8D
P 3900 6800
F 0 "D8" H 3900 7170 50  0000 C CNN
F 1 "LED_RGB" H 3900 6450 50  0000 C CNN
F 2 "LEDs:LED_WS2812-PLCC6" H 3900 6750 50  0001 C CNN
F 3 "" H 3900 6750 50  0001 C CNN
	1    3900 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 800  3700 2750
Connection ~ 3700 1000
Connection ~ 3700 1200
Connection ~ 3700 1650
Connection ~ 3700 1850
Connection ~ 3700 2050
Wire Wire Line
	4100 800  4100 2850
Connection ~ 4100 1000
Connection ~ 4100 1650
Connection ~ 4100 1850
Connection ~ 4100 2050
Wire Wire Line
	3700 2450 3700 4400
Connection ~ 3700 2650
Connection ~ 3700 2850
Connection ~ 3700 3300
Connection ~ 3700 3500
Connection ~ 3700 3700
Connection ~ 4100 2650
Wire Wire Line
	4100 2650 4100 4400
Connection ~ 4100 3300
Connection ~ 4100 3500
Connection ~ 4100 3700
Wire Wire Line
	3700 4100 3700 6050
Connection ~ 3700 4300
Connection ~ 3700 4500
Connection ~ 3700 4950
Connection ~ 3700 5150
Connection ~ 3700 5350
Connection ~ 4100 4300
Connection ~ 4100 4950
Connection ~ 4100 5150
Connection ~ 4100 5350
Connection ~ 3700 5950
Connection ~ 3700 6150
Connection ~ 3700 6600
Connection ~ 3700 6800
Connection ~ 3700 7000
Connection ~ 4100 5950
Connection ~ 4100 6600
Connection ~ 4100 6800
Connection ~ 4100 7000
Connection ~ 4100 1200
Connection ~ 4100 2850
Connection ~ 4100 4500
Connection ~ 4100 6150
Wire Wire Line
	4100 4100 4100 6050
Wire Wire Line
	4100 5750 4100 7250
Wire Wire Line
	3700 7000 3700 5950
Connection ~ 4100 5750
Wire Wire Line
	3700 800  3350 800 
Wire Wire Line
	4100 7250 4450 7250
Text Label 3350 800  2    60   ~ 0
Rows_cathode
Text Label 4450 7250 0    60   ~ 0
Columns_anode
$EndSCHEMATC
