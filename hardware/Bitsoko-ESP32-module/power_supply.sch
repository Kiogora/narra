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
Sheet 2 6
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
L NCP1117-3.3_SOT223 U?
U 1 1 59513A80
P 5665 3015
F 0 "U?" H 5665 3257 50  0000 C CNN
F 1 "NCP1117-3.3_SOT223" H 5665 3166 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 5665 3215 50  0001 C CNN
F 3 "" H 5765 2765 50  0001 C CNN
	1    5665 3015
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59513C5C
P 5665 3765
F 0 "#PWR?" H 5665 3515 50  0001 C CNN
F 1 "GND" H 5670 3592 50  0000 C CNN
F 2 "" H 5665 3765 50  0001 C CNN
F 3 "" H 5665 3765 50  0001 C CNN
	1    5665 3765
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59513D7D
P 4665 3365
F 0 "C?" H 4780 3411 50  0000 L CNN
F 1 "10uF" H 4780 3320 50  0000 L CNN
F 2 "" H 4703 3215 50  0001 C CNN
F 3 "" H 4665 3365 50  0001 C CNN
	1    4665 3365
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59513DB7
P 4665 3765
F 0 "#PWR?" H 4665 3515 50  0001 C CNN
F 1 "GND" H 4670 3592 50  0000 C CNN
F 2 "" H 4665 3765 50  0001 C CNN
F 3 "" H 4665 3765 50  0001 C CNN
	1    4665 3765
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59513EDC
P 6765 3765
F 0 "#PWR?" H 6765 3515 50  0001 C CNN
F 1 "GND" H 6770 3592 50  0000 C CNN
F 2 "" H 6765 3765 50  0001 C CNN
F 3 "" H 6765 3765 50  0001 C CNN
	1    6765 3765
	1    0    0    -1  
$EndComp
Wire Wire Line
	5665 3765 5665 3315
Wire Wire Line
	4465 3015 5365 3015
Wire Wire Line
	4665 3015 4665 3215
Wire Wire Line
	4665 3765 4665 3515
Wire Wire Line
	6765 3765 6765 3515
$Comp
L C C?
U 1 1 59513E27
P 6765 3365
F 0 "C?" H 6880 3411 50  0000 L CNN
F 1 "22uF" H 6880 3320 50  0000 L CNN
F 2 "" H 6803 3215 50  0001 C CNN
F 3 "" H 6765 3365 50  0001 C CNN
	1    6765 3365
	1    0    0    -1  
$EndComp
Wire Wire Line
	6765 3215 6765 3015
Wire Wire Line
	5965 3015 7015 3015
Connection ~ 6765 3015
Connection ~ 4665 3015
Wire Notes Line
	475  2365 11220 2365
Wire Notes Line
	475  4330 11220 4330
Text HLabel 4465 3015 0    60   Input ~ 0
EXT_5V
Text GLabel 7015 3015 2    60   Input ~ 0
3v3
Text Notes 10280 4330 0    60   ~ 0
3v3 Linear regulator
$EndSCHEMATC
