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
Sheet 6 6
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
L CONN_01X20 J3
U 1 1 5951391D
P 5450 3650
AR Path="/59510C04/5951391D" Ref="J3"  Part="1" 
AR Path="/59531D77/59540F06/5951391D" Ref="J3"  Part="1" 
AR Path="/59552753/5951391D" Ref="J3"  Part="1" 
F 0 "J3" H 5528 3691 50  0000 L CNN
F 1 "CONN_01X20" H 5528 3600 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x20_Pitch2.54mm" H 5450 3650 50  0001 C CNN
F 3 "" H 5450 3650 50  0001 C CNN
	1    5450 3650
	-1   0    0    1   
$EndComp
Wire Notes Line
	470  4780 11220 4780
Wire Notes Line
	475  2365 11220 2365
Text HLabel 5650 4000 2    60   Input ~ 0
EXT_5v
Text HLabel 5650 2700 2    60   BiDi ~ 0
SENSOR_VP
Text HLabel 5650 2800 2    60   BiDi ~ 0
SENSOR_VN
Text GLabel 5650 4200 2    60   Input ~ 0
3v3
Text HLabel 5650 2900 2    60   BiDi ~ 0
IO34
Text HLabel 5650 3000 2    60   BiDi ~ 0
IO35
Text HLabel 5650 3100 2    60   BiDi ~ 0
IO32
Text HLabel 5650 3200 2    60   BiDi ~ 0
IO33
Text HLabel 5650 3300 2    60   BiDi ~ 0
IO25
Text HLabel 5650 3400 2    60   BiDi ~ 0
IO26
Text HLabel 5650 3500 2    60   BiDi ~ 0
IO27
Text HLabel 5650 3600 2    60   BiDi ~ 0
IO14
Text HLabel 5650 3700 2    60   BiDi ~ 0
IO12
Text HLabel 5650 3800 2    60   BiDi ~ 0
IO13
Text HLabel 5650 4300 2    60   BiDi ~ 0
SD2
Text HLabel 5650 4400 2    60   BiDi ~ 0
SD3
Text HLabel 5650 4500 2    60   BiDi ~ 0
CMD
Text HLabel 5650 4600 2    60   BiDi ~ 0
CLK
NoConn ~ 5650 3900
NoConn ~ 5650 4100
$EndSCHEMATC
