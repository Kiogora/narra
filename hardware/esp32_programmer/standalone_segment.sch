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
LIBS:ESP-32-programmer-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 1350 2500 2850 1650
U 599585FA
F0 "Sheet599585F9" 60
F1 "JTAG.sch" 60
$EndSheet
$Comp
L ESP-32-module U?
U 1 1 5995C751
P 6650 3500
F 0 "U?" H 6650 4747 60  0000 C CNN
F 1 "ESP-32-module" H 6650 4641 60  0000 C CNN
F 2 "narra:ESP32-module-v2" H 6650 3950 60  0001 C CNN
F 3 "" H 6650 3950 60  0001 C CNN
	1    6650 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5995C758
P 5300 2500
F 0 "#PWR?" H 5300 2250 50  0001 C CNN
F 1 "GND" H 5305 2327 50  0000 C CNN
F 2 "" H 5300 2500 50  0001 C CNN
F 3 "" H 5300 2500 50  0001 C CNN
	1    5300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2500 5750 2500
$Comp
L GND #PWR?
U 1 1 5995C75F
P 8000 2550
F 0 "#PWR?" H 8000 2300 50  0001 C CNN
F 1 "GND" H 8005 2377 50  0000 C CNN
F 2 "" H 8000 2550 50  0001 C CNN
F 3 "" H 8000 2550 50  0001 C CNN
	1    8000 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 2550 8000 2500
Wire Wire Line
	8000 2500 7550 2500
$EndSCHEMATC
