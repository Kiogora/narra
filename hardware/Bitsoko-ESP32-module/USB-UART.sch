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
Sheet 3 6
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
L CONN_01X06 J1
U 1 1 5951994E
P 5680 3525
AR Path="/59510B33/5951994E" Ref="J1"  Part="1" 
AR Path="/59531D77/59540E0F/5951994E" Ref="J1"  Part="1" 
AR Path="/5955265C/5951994E" Ref="J1"  Part="1" 
F 0 "J1" H 5758 3566 50  0000 L CNN
F 1 "CONN_01X06" H 5758 3475 50  0000 L CNN
F 2 "narra:Pin_header_5mil_staggered_1x06_2.54mm" H 5680 3525 50  0001 C CNN
F 3 "" H 5680 3525 50  0001 C CNN
	1    5680 3525
	1    0    0    -1  
$EndComp
Text GLabel 5105 3275 0    60   Input ~ 0
3v3
$Comp
L GND #PWR05
U 1 1 595199D1
P 5230 3875
AR Path="/59510B33/595199D1" Ref="#PWR05"  Part="1" 
AR Path="/59531D77/59540E0F/595199D1" Ref="#PWR05"  Part="1" 
AR Path="/5955265C/595199D1" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 5230 3625 50  0001 C CNN
F 1 "GND" H 5235 3702 50  0000 C CNN
F 2 "" H 5230 3875 50  0001 C CNN
F 3 "" H 5230 3875 50  0001 C CNN
	1    5230 3875
	1    0    0    -1  
$EndComp
Text Notes 9450 4300 0    60   ~ 0
Auto-programming ICSP UART header
Text HLabel 5105 3375 0    60   Output ~ 0
RX
Text HLabel 5105 3475 0    60   Input ~ 0
TX
Text HLabel 5105 3575 0    60   Output ~ 0
IO0
Text HLabel 5105 3675 0    60   Output ~ 0
EN
Wire Notes Line
	490  2050 11235 2050
Wire Notes Line
	470  4330 11220 4330
Wire Wire Line
	5480 3775 5230 3775
Wire Wire Line
	5480 3275 5105 3275
Wire Wire Line
	5230 3775 5230 3875
Wire Wire Line
	5105 3375 5480 3375
Wire Wire Line
	5105 3475 5480 3475
Wire Wire Line
	5105 3575 5480 3575
Wire Wire Line
	5105 3675 5480 3675
Wire Wire Line
	5455 3375 5430 3350
Wire Wire Line
	5430 3350 5430 3225
Connection ~ 5455 3375
Wire Wire Line
	5370 3390 5455 3475
Wire Wire Line
	5370 2990 5370 3390
Connection ~ 5455 3475
Wire Wire Line
	5275 3395 5455 3575
Wire Wire Line
	5275 2720 5275 3395
Connection ~ 5455 3575
Wire Wire Line
	5455 3675 5280 3500
Connection ~ 5455 3675
Text HLabel 5190 2590 1    40   Output ~ 0
RX_EXT
Text HLabel 5275 2720 1    40   Input ~ 0
TX_EXT
Text HLabel 5370 2990 1    40   Output ~ 0
IO0_EXT
Text HLabel 5430 3225 1    40   Output ~ 0
EN_EXT
Wire Wire Line
	5280 3500 5225 3440
Wire Wire Line
	5225 3440 5190 3400
Wire Wire Line
	5190 3400 5190 2590
$EndSCHEMATC
