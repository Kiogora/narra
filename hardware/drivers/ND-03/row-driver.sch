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
LIBS:ND-03-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
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
L ULN2803A U20
U 1 1 599A2748
P 6400 1510
F 0 "U20" H 6400 2077 50  0000 C CNN
F 1 "ULN2803A" H 6400 1986 50  0000 C CNN
F 2 "Housings_DIP:DIP-18_W7.62mm_LongPads" H 6450 860 50  0001 L CNN
F 3 "" H 6500 1410 50  0001 C CNN
	1    6400 1510
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 599A2812
P 2910 1340
F 0 "#PWR037" H 2910 1090 50  0001 C CNN
F 1 "GND" H 2780 1250 50  0000 C CNN
F 2 "" H 2910 1340 50  0001 C CNN
F 3 "" H 2910 1340 50  0001 C CNN
	1    2910 1340
	1    0    0    -1  
$EndComp
Text HLabel 3210 1240 0    60   Input ~ 0
CLK
Text HLabel 3150 1540 0    60   Input ~ 0
RESET
Text Label 4730 1240 0    60   ~ 0
Q0
Text Label 4730 1340 0    60   ~ 0
Q1
Text Label 4730 1440 0    60   ~ 0
Q2
Text Label 4730 1540 0    60   ~ 0
Q3
Text Label 4730 1640 0    60   ~ 0
Q4
Text Label 4730 1740 0    60   ~ 0
Q5
Text Label 4730 1840 0    60   ~ 0
Q6
Text Label 4730 1940 0    60   ~ 0
Q7
Text Label 4730 2040 0    60   ~ 0
Q8
Text Label 5900 1210 2    60   ~ 0
Q7
Text Label 5910 1310 2    60   ~ 0
Q6
Text Label 5910 1410 2    60   ~ 0
Q5
Text Label 5920 1510 2    60   ~ 0
Q4
Text Label 5920 1610 2    60   ~ 0
Q3
Text Label 5920 1710 2    60   ~ 0
Q2
Text Label 5930 1810 2    60   ~ 0
Q1
$Comp
L GS3 J68
U 1 1 599A2F22
P 5640 1910
F 0 "J68" H 5640 2215 50  0000 C CNN
F 1 "GS3" H 5640 2124 50  0000 C CNN
F 2 "Connectors:GS3" V 5728 1836 50  0001 C CNN
F 3 "" H 5640 1910 50  0001 C CNN
	1    5640 1910
	1    0    0    -1  
$EndComp
Text Label 5410 1810 2    60   ~ 0
Q0
Text Label 5410 2010 2    60   ~ 0
Q8
NoConn ~ 4640 2140
NoConn ~ 4640 2340
$Comp
L GND #PWR038
U 1 1 599A3632
P 6400 2280
F 0 "#PWR038" H 6400 2030 50  0001 C CNN
F 1 "GND" H 6405 2107 50  0000 C CNN
F 2 "" H 6400 2280 50  0001 C CNN
F 3 "" H 6400 2280 50  0001 C CNN
	1    6400 2280
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x02 J72
U 1 1 599A3841
P 3160 5530
F 0 "J72" V 3287 5325 50  0000 R CNN
F 1 "Screw_Terminal_1x02" V 3196 5325 50  0000 R CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 3160 5305 50  0001 C CNN
F 3 "" H 3135 5530 50  0001 C CNN
	1    3160 5530
	0    -1   -1   0   
$EndComp
$Comp
L Screw_Terminal_1x02 J71
U 1 1 599A39CE
P 4410 5520
F 0 "J71" V 4537 5315 50  0000 R CNN
F 1 "Screw_Terminal_1x02" V 4446 5315 50  0000 R CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 4410 5295 50  0001 C CNN
F 3 "" H 4385 5520 50  0001 C CNN
	1    4410 5520
	0    -1   -1   0   
$EndComp
$Comp
L Screw_Terminal_1x02 J69
U 1 1 599A3A48
P 5620 5500
F 0 "J69" V 5747 5295 50  0000 R CNN
F 1 "Screw_Terminal_1x02" V 5656 5295 50  0000 R CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 5620 5275 50  0001 C CNN
F 3 "" H 5595 5500 50  0001 C CNN
	1    5620 5500
	0    -1   -1   0   
$EndComp
$Comp
L Screw_Terminal_1x02 J70
U 1 1 599A3AF8
P 6860 5500
F 0 "J70" V 6987 5295 50  0000 R CNN
F 1 "Screw_Terminal_1x02" V 6896 5295 50  0000 R CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 6860 5275 50  0001 C CNN
F 3 "" H 6835 5500 50  0001 C CNN
	1    6860 5500
	0    -1   -1   0   
$EndComp
Text Label 6000 1910 2    60   ~ 0
JUMP
Text Notes 11220 6530 2    60   ~ 0
TERMINAL BLOCKS\n
Text Label 3060 5260 1    60   ~ 0
R1
Text Label 3260 5270 1    60   ~ 0
R2
Text Label 4310 5250 1    60   ~ 0
R3
Text Label 4510 5250 1    60   ~ 0
R4
Text Label 5520 5230 1    60   ~ 0
R5
Text Label 5720 5230 1    60   ~ 0
R6
Text Label 6760 5230 1    60   ~ 0
R7
Text Label 6960 5230 1    60   ~ 0
R8
Text Label 7310 1210 0    60   ~ 0
R1
Text Label 7310 1310 0    60   ~ 0
R2
Text Label 7310 1410 0    60   ~ 0
R3
Text Label 7310 1510 0    60   ~ 0
R4
Text Label 7310 1610 0    60   ~ 0
R5
Text Label 7310 1710 0    60   ~ 0
R6
Text Label 7310 1810 0    60   ~ 0
R7
Text Label 7310 1910 0    60   ~ 0
R8
NoConn ~ 6800 2010
$Comp
L CD4017 U21
U 1 1 599C290B
P 3990 1790
F 0 "U21" H 3990 2606 50  0000 C CNN
F 1 "CD4017" H 3990 2515 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_Socket_LongPads" H 3990 1790 60  0001 C CNN
F 3 "" H 3990 1790 60  0001 C CNN
	1    3990 1790
	1    0    0    -1  
$EndComp
Text GLabel 3425 1035 0    60   Input ~ 0
5v
$Comp
L GND #PWR039
U 1 1 599C2C7A
P 3990 2425
F 0 "#PWR039" H 3990 2175 50  0001 C CNN
F 1 "GND" H 4120 2335 50  0000 C CNN
F 2 "" H 3990 2425 50  0001 C CNN
F 3 "" H 3990 2425 50  0001 C CNN
	1    3990 2425
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 59A532E8
P 7100 1210
F 0 "R2" V 7140 1360 50  0000 C CNN
F 1 "R" V 7100 1210 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1210 50  0001 C CNN
F 3 "" H 7100 1210 50  0001 C CNN
	1    7100 1210
	0    -1   -1   0   
$EndComp
Wire Notes Line
	470  4590 11220 4590
Wire Wire Line
	3340 1240 3210 1240
Wire Wire Line
	2910 1340 3340 1340
Wire Wire Line
	3340 1540 3150 1540
Wire Wire Line
	4640 1240 4730 1240
Wire Wire Line
	4640 1340 4730 1340
Wire Wire Line
	4640 1440 4730 1440
Wire Wire Line
	4640 1540 4730 1540
Wire Wire Line
	4640 1640 4730 1640
Wire Wire Line
	4640 1740 4730 1740
Wire Wire Line
	4640 1840 4730 1840
Wire Wire Line
	4640 1940 4730 1940
Wire Wire Line
	4640 2040 4730 2040
Wire Wire Line
	6000 1210 5900 1210
Wire Wire Line
	6000 1310 5910 1310
Wire Wire Line
	6000 1410 5910 1410
Wire Wire Line
	6000 1510 5920 1510
Wire Wire Line
	6000 1610 5920 1610
Wire Wire Line
	6000 1710 5920 1710
Wire Wire Line
	6000 1810 5930 1810
Wire Wire Line
	5790 1910 6000 1910
Wire Wire Line
	5490 1810 5410 1810
Wire Wire Line
	5490 2010 5410 2010
Wire Wire Line
	6800 1210 6950 1210
Wire Wire Line
	6800 1310 6950 1310
Wire Wire Line
	6800 1410 6950 1410
Wire Wire Line
	6800 1510 6950 1510
Wire Wire Line
	6800 1610 6950 1610
Wire Wire Line
	6800 1710 6950 1710
Wire Wire Line
	6800 1810 6950 1810
Wire Wire Line
	6800 1910 6950 1910
Wire Wire Line
	6400 2280 6400 2210
Wire Notes Line
	11220 6530 470  6530
Wire Wire Line
	3060 5330 3060 5260
Wire Wire Line
	3260 5330 3260 5270
Wire Wire Line
	4310 5320 4310 5250
Wire Wire Line
	4510 5320 4510 5250
Wire Wire Line
	5520 5300 5520 5230
Wire Wire Line
	5720 5300 5720 5230
Wire Wire Line
	6760 5300 6760 5230
Wire Wire Line
	6960 5300 6960 5230
Wire Notes Line
	475  2565 11220 2565
Wire Wire Line
	3425 1035 3990 1035
Wire Wire Line
	3990 1035 3990 1190
Wire Wire Line
	3990 2425 3990 2390
$Comp
L R R3
U 1 1 59A53F67
P 7100 1310
F 0 "R3" V 7140 1460 50  0000 C CNN
F 1 "R" V 7100 1310 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1310 50  0001 C CNN
F 3 "" H 7100 1310 50  0001 C CNN
	1    7100 1310
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 59A53FF7
P 7100 1410
F 0 "R4" V 7140 1560 50  0000 C CNN
F 1 "R" V 7100 1410 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1410 50  0001 C CNN
F 3 "" H 7100 1410 50  0001 C CNN
	1    7100 1410
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 59A54063
P 7100 1510
F 0 "R5" V 7140 1660 50  0000 C CNN
F 1 "R" V 7100 1510 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1510 50  0001 C CNN
F 3 "" H 7100 1510 50  0001 C CNN
	1    7100 1510
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 59A5411A
P 7100 1610
F 0 "R6" V 7140 1760 50  0000 C CNN
F 1 "R" V 7100 1610 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1610 50  0001 C CNN
F 3 "" H 7100 1610 50  0001 C CNN
	1    7100 1610
	0    -1   -1   0   
$EndComp
$Comp
L R R7
U 1 1 59A54156
P 7100 1710
F 0 "R7" V 7140 1860 50  0000 C CNN
F 1 "R" V 7100 1710 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1710 50  0001 C CNN
F 3 "" H 7100 1710 50  0001 C CNN
	1    7100 1710
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 59A54223
P 7100 1810
F 0 "R8" V 7140 1960 50  0000 C CNN
F 1 "R" V 7100 1810 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1810 50  0001 C CNN
F 3 "" H 7100 1810 50  0001 C CNN
	1    7100 1810
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 59A54263
P 7100 1910
F 0 "R9" V 7140 2060 50  0000 C CNN
F 1 "R" V 7100 1910 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 1910 50  0001 C CNN
F 3 "" H 7100 1910 50  0001 C CNN
	1    7100 1910
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7250 1210 7310 1210
Wire Wire Line
	7250 1310 7310 1310
Wire Wire Line
	7250 1410 7310 1410
Wire Wire Line
	7250 1510 7310 1510
Wire Wire Line
	7250 1610 7310 1610
Wire Wire Line
	7250 1710 7310 1710
Wire Wire Line
	7250 1810 7310 1810
Wire Wire Line
	7250 1910 7310 1910
$EndSCHEMATC
