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
LIBS:Bitsoko-ESP32-module-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
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
L CONN_01X20 J2
U 1 1 59513823
P 5650 3700
AR Path="/59510B3D/59513823" Ref="J2"  Part="1" 
AR Path="/59531D77/59540EC0/59513823" Ref="J2"  Part="1" 
AR Path="/5955270D/59513823" Ref="J2"  Part="1" 
F 0 "J2" H 5728 3741 50  0000 L CNN
F 1 "CONN_01X20" H 5728 3650 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x20_Pitch2.54mm" H 5650 3700 50  0001 C CNN
F 3 "" H 5650 3700 50  0001 C CNN
	1    5650 3700
	1    0    0    -1  
$EndComp
Wire Notes Line
	470  2360 11220 2360
Wire Notes Line
	475  5185 11220 5185
$Comp
L GND #PWR014
U 1 1 59542B62
P 5000 2750
AR Path="/59510B3D/59542B62" Ref="#PWR014"  Part="1" 
AR Path="/59531D77/59540EC0/59542B62" Ref="#PWR014"  Part="1" 
AR Path="/5955270D/59542B62" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 5000 2500 50  0001 C CNN
F 1 "GND" H 4850 2700 50  0000 C CNN
F 2 "" H 5000 2750 50  0001 C CNN
F 3 "" H 5000 2750 50  0001 C CNN
	1    5000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2750 5450 2750
Text HLabel 5450 2850 0    60   BiDi ~ 0
IO23
Text HLabel 5450 2950 0    60   BiDi ~ 0
IO22
Text HLabel 5450 3050 0    60   BiDi ~ 0
IO21
Text HLabel 5450 3150 0    60   BiDi ~ 0
IO19
Text HLabel 5450 3250 0    60   BiDi ~ 0
IO18
Text HLabel 5450 3350 0    60   BiDi ~ 0
IO5
Text HLabel 5450 3450 0    60   BiDi ~ 0
IO17
Text HLabel 5450 3550 0    60   BiDi ~ 0
IO16
Text HLabel 5450 3650 0    60   BiDi ~ 0
IO4
Text HLabel 5450 3750 0    60   BiDi ~ 0
IO2
Text HLabel 5450 3850 0    60   BiDi ~ 0
IO15
Text HLabel 5450 3950 0    60   Input ~ 0
RXD_EXT
Text HLabel 5450 4050 0    60   Output ~ 0
TXD_EXT
Text HLabel 5450 4150 0    60   Input ~ 0
IO0_EXT
Text HLabel 5450 4250 0    60   Input ~ 0
EN_EXT
$Comp
L GND #PWR015
U 1 1 5954CB1B
P 5200 4750
AR Path="/59510B3D/5954CB1B" Ref="#PWR015"  Part="1" 
AR Path="/59531D77/59540EC0/5954CB1B" Ref="#PWR015"  Part="1" 
AR Path="/5955270D/5954CB1B" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 5200 4500 50  0001 C CNN
F 1 "GND" H 5205 4577 50  0000 C CNN
F 2 "" H 5200 4750 50  0001 C CNN
F 3 "" H 5200 4750 50  0001 C CNN
	1    5200 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4550 5450 4550
Connection ~ 5200 4550
Wire Wire Line
	5200 4650 5450 4650
Connection ~ 5200 4650
Text HLabel 5450 4350 0    60   BiDi ~ 0
SD1
Text HLabel 5450 4450 0    60   BiDi ~ 0
SD0
Wire Wire Line
	5200 4550 5200 4750
$EndSCHEMATC
