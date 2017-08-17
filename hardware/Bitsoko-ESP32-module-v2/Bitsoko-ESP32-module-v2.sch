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
LIBS:narra
LIBS:Bitsoko-ESP32-module-v2-cache
EELAYER 26 0
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
L ESP32-WROOM32-MODULE U1
U 1 1 599550A2
P 5550 2900
F 0 "U1" H 5550 3987 60  0000 C CNN
F 1 "ESP32-WROOM32-MODULE" H 5550 3881 60  0000 C CNN
F 2 "narra:ESP-WROOM32-MODULE" H 5450 2800 60  0001 C CNN
F 3 "" H 5450 2800 60  0001 C CNN
	1    5550 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2650 3250 2650
Wire Wire Line
	3200 2750 3250 2750
Wire Wire Line
	3200 2850 3250 2850
Wire Wire Line
	3200 2950 3250 2950
Wire Wire Line
	3200 3050 3250 3050
Wire Wire Line
	3200 3150 3250 3150
Wire Wire Line
	3200 3250 3250 3250
Wire Wire Line
	3200 3350 3250 3350
Wire Wire Line
	3200 3450 3250 3450
Wire Wire Line
	2700 2650 2650 2650
Wire Wire Line
	2700 2750 2650 2750
Wire Wire Line
	2700 2850 2650 2850
Wire Wire Line
	2700 2950 2650 2950
Wire Wire Line
	2700 3050 2650 3050
Wire Wire Line
	2700 3150 2650 3150
Wire Wire Line
	2700 3250 2650 3250
Wire Wire Line
	2700 3350 2650 3350
Wire Wire Line
	2700 3450 2650 3450
Wire Wire Line
	7450 2600 7400 2600
Wire Wire Line
	7450 2700 7400 2700
Wire Wire Line
	7450 2800 7400 2800
Wire Wire Line
	7450 2900 7400 2900
Wire Wire Line
	7450 3000 7400 3000
Wire Wire Line
	7450 3100 7400 3100
Wire Wire Line
	7450 3200 7400 3200
Wire Wire Line
	7450 3300 7400 3300
Wire Wire Line
	7450 3400 7400 3400
Wire Wire Line
	7950 2600 8000 2600
Wire Wire Line
	7950 2700 8000 2700
Wire Wire Line
	7950 2800 8000 2800
Wire Wire Line
	7950 2900 8000 2900
Wire Wire Line
	7950 3000 8000 3000
Wire Wire Line
	7950 3100 8000 3100
Wire Wire Line
	7950 3200 8000 3200
Wire Wire Line
	7950 3300 8000 3300
Wire Wire Line
	7950 3400 8000 3400
Text Label 2650 2650 2    60   ~ 0
GND
Text Label 3250 2650 0    60   ~ 0
3V3
Text Label 2650 2750 2    60   ~ 0
EN
Text Label 3250 2750 0    60   ~ 0
SVP
Text Label 2650 2850 2    60   ~ 0
SVN
Text Label 3250 2850 0    60   ~ 0
IO34
Text Label 2650 2950 2    60   ~ 0
IO35
Text Label 3250 2950 0    60   ~ 0
IO32
Text Label 2650 3050 2    60   ~ 0
IO33
Text Label 3250 3050 0    60   ~ 0
IO25
Text Label 2650 3150 2    60   ~ 0
IO26
Text Label 3250 3150 0    60   ~ 0
IO27
Text Label 2650 3250 2    60   ~ 0
IO14
Text Label 3250 3250 0    60   ~ 0
IO12
$Comp
L CONN_02X10 J2
U 1 1 59956261
P 2950 3100
F 0 "J2" H 2950 3765 50  0000 C CNN
F 1 "CONN_02X10" H 2950 3674 50  0000 C CNN
F 2 "narra:Pin_Header_Straight_2x10_Pitch2.54mm_staggered" H 2950 1900 50  0001 C CNN
F 3 "" H 2950 1900 50  0001 C CNN
	1    2950 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X10 J1
U 1 1 59956326
P 7700 3050
F 0 "J1" H 7700 3715 50  0000 C CNN
F 1 "CONN_02X10" H 7700 3624 50  0000 C CNN
F 2 "narra:Pin_Header_Straight_2x10_Pitch2.54mm_staggered" H 7700 1850 50  0001 C CNN
F 3 "" H 7700 1850 50  0001 C CNN
	1    7700 3050
	1    0    0    -1  
$EndComp
Text Label 2650 3350 2    60   ~ 0
GND
Text Label 3250 3350 0    60   ~ 0
IO13
Text Label 2650 3450 2    60   ~ 0
SD2
Text Label 3250 3450 0    60   ~ 0
SD3
Text Label 2700 3550 2    60   ~ 0
CMD
Text Label 3200 3550 0    60   ~ 0
CLK
Wire Wire Line
	7450 3500 7400 3500
Wire Wire Line
	7950 3500 8000 3500
Text Label 8000 2600 0    60   ~ 0
GND
Text Label 7400 2600 2    60   ~ 0
IO23
Text Label 8000 2700 0    60   ~ 0
IO22
Text Label 7400 2700 2    60   ~ 0
TXD
Text Label 8000 2800 0    60   ~ 0
RXD
Text Label 7400 2800 2    60   ~ 0
IO21
Text Label 8000 2900 0    60   ~ 0
IO20
Text Label 7400 2900 2    60   ~ 0
IO19
Text Label 8000 3000 0    60   ~ 0
IO18
Text Label 7400 3000 2    60   ~ 0
IO5
Text Label 8000 3100 0    60   ~ 0
IO17
Text Label 7400 3100 2    60   ~ 0
IO16
Text Label 8000 3200 0    60   ~ 0
IO4
Text Label 7400 3200 2    60   ~ 0
IO0
Text Label 8000 3300 0    60   ~ 0
IO2
Text Label 7400 3300 2    60   ~ 0
IO15
Text Label 8000 3400 0    60   ~ 0
SD1
Text Label 7400 3400 2    60   ~ 0
SD0
NoConn ~ 7400 3500
NoConn ~ 8000 3500
Wire Wire Line
	4600 2450 4550 2450
Wire Wire Line
	4600 2550 4550 2550
Wire Wire Line
	4600 2650 4550 2650
Wire Wire Line
	4600 2750 4550 2750
Wire Wire Line
	4600 2850 4550 2850
Wire Wire Line
	4600 2950 4550 2950
Wire Wire Line
	4600 3050 4550 3050
Wire Wire Line
	4600 3150 4550 3150
Wire Wire Line
	4600 3250 4550 3250
Wire Wire Line
	4600 3350 4550 3350
Wire Wire Line
	4600 3450 4550 3450
Wire Wire Line
	4600 3550 4550 3550
Wire Wire Line
	4600 3650 4550 3650
Wire Wire Line
	4600 3750 4550 3750
Wire Wire Line
	5150 4150 5150 4200
Wire Wire Line
	5250 4150 5250 4200
Wire Wire Line
	5350 4150 5350 4200
Wire Wire Line
	5450 4150 5450 4200
Wire Wire Line
	5550 4150 5550 4200
Wire Wire Line
	5650 4150 5650 4200
Wire Wire Line
	5750 4150 5750 4200
Wire Wire Line
	5850 4150 5850 4200
Wire Wire Line
	5950 4150 5950 4200
Wire Wire Line
	6050 4150 6050 4200
Wire Wire Line
	6500 3750 6550 3750
Wire Wire Line
	6500 3650 6550 3650
Wire Wire Line
	6500 3550 6550 3550
Wire Wire Line
	6500 3450 6550 3450
Wire Wire Line
	6500 3350 6550 3350
Wire Wire Line
	6500 3250 6550 3250
Wire Wire Line
	6500 3150 6550 3150
Wire Wire Line
	6500 3050 6550 3050
Wire Wire Line
	6500 2950 6550 2950
Wire Wire Line
	6500 2850 6550 2850
Wire Wire Line
	6500 2750 6550 2750
Wire Wire Line
	6500 2650 6550 2650
Wire Wire Line
	6500 2550 6550 2550
Wire Wire Line
	6500 2450 6550 2450
Text Label 4550 2450 2    60   ~ 0
GND
Text Label 4550 2550 2    60   ~ 0
3V3
Text Label 4550 2650 2    60   ~ 0
EN
Text Label 4550 2750 2    60   ~ 0
SVP
Text Label 4550 2850 2    60   ~ 0
SVN
Text Label 4550 2950 2    60   ~ 0
IO34
Text Label 4550 3050 2    60   ~ 0
IO35
Text Label 4550 3150 2    60   ~ 0
IO32
Text Label 4550 3250 2    60   ~ 0
IO33
Text Label 4550 3350 2    60   ~ 0
IO25
Text Label 4550 3450 2    60   ~ 0
IO26
Text Label 4550 3550 2    60   ~ 0
IO27
Text Label 4550 3650 2    60   ~ 0
IO14
Text Label 4550 3750 2    60   ~ 0
IO12
Text Label 5150 4200 3    60   ~ 0
GND
Text Label 5250 4200 3    60   ~ 0
IO13
Text Label 5350 4200 3    60   ~ 0
SD2
Text Label 5450 4200 3    60   ~ 0
SD3
Text Label 5550 4200 3    60   ~ 0
CMD
Text Label 5650 4200 3    60   ~ 0
CLK
Text Label 5750 4200 3    60   ~ 0
SD0
Text Label 5850 4200 3    60   ~ 0
SD1
Text Label 5950 4200 3    60   ~ 0
IO15
Text Label 6050 4200 3    60   ~ 0
IO2
Text Label 6550 3750 0    60   ~ 0
IO0
Text Label 6550 3650 0    60   ~ 0
IO4
Text Label 6550 3550 0    60   ~ 0
IO16
Text Label 6550 3450 0    60   ~ 0
IO17
Text Label 6550 3350 0    60   ~ 0
IO5
Text Label 6550 3250 0    60   ~ 0
IO18
Text Label 6550 3150 0    60   ~ 0
IO19
Text Label 6550 3050 0    60   ~ 0
IO20
Text Label 6550 2950 0    60   ~ 0
IO21
Text Label 6550 2850 0    60   ~ 0
RXD
Text Label 6550 2750 0    60   ~ 0
TXD
Text Label 6550 2650 0    60   ~ 0
IO22
Text Label 6550 2550 0    60   ~ 0
IO23
Text Label 6550 2450 0    60   ~ 0
GND
$EndSCHEMATC
