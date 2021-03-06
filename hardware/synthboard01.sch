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
LIBS:ArduProMiniTKB
LIBS:Connectors
LIBS:MiscellaneousDevices
LIBS:w_connectors
LIBS:Passives
LIBS:synthboard01-cache
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
L ARDUPROMINI-6 uP1
U 1 1 59341B0A
P 5450 2600
F 0 "uP1" H 5450 2500 60  0000 C CNN
F 1 "ARDUPROMINI-6" H 5450 2600 60  0000 C CNN
F 2 "ArduProMiniTKB:ArduProMini-6" H 5450 2600 60  0001 C CNN
F 3 "" H 5450 2600 60  0000 C CNN
	1    5450 2600
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK CON1
U 1 1 59341B72
P 2500 5400
F 0 "CON1" H 2500 5650 50  0000 C CNN
F 1 "9-15V" H 2500 5200 50  0000 C CNN
F 2 "Connectors:BARREL_JACK" H 2500 5400 50  0001 C CNN
F 3 "" H 2500 5400 50  0000 C CNN
	1    2500 5400
	1    0    0    -1  
$EndComp
Text GLabel 4550 3400 0    60   Input ~ 0
AudioOut
$Comp
L VCC #PWR01
U 1 1 59341BEC
P 6400 3100
F 0 "#PWR01" H 6400 2950 50  0001 C CNN
F 1 "VCC" H 6400 3250 50  0000 C CNN
F 2 "" H 6400 3100 50  0000 C CNN
F 3 "" H 6400 3100 50  0000 C CNN
	1    6400 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 59341C0A
P 3050 5600
F 0 "#PWR02" H 3050 5350 50  0001 C CNN
F 1 "GND" H 3050 5450 50  0000 C CNN
F 2 "" H 3050 5600 50  0000 C CNN
F 3 "" H 3050 5600 50  0000 C CNN
	1    3050 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 59341C22
P 3850 3200
F 0 "#PWR03" H 3850 2950 50  0001 C CNN
F 1 "GND" H 3850 3050 50  0000 C CNN
F 2 "" H 3850 3200 50  0000 C CNN
F 3 "" H 3850 3200 50  0000 C CNN
	1    3850 3200
	1    0    0    -1  
$EndComp
$Comp
L +9V #PWR04
U 1 1 59341C3F
P 3200 5250
F 0 "#PWR04" H 3200 5100 50  0001 C CNN
F 1 "+9V" H 3200 5390 50  0000 C CNN
F 2 "" H 3200 5250 50  0000 C CNN
F 3 "" H 3200 5250 50  0000 C CNN
	1    3200 5250
	1    0    0    -1  
$EndComp
$Comp
L +9V #PWR05
U 1 1 59341C59
P 6400 2800
F 0 "#PWR05" H 6400 2650 50  0001 C CNN
F 1 "+9V" H 6400 2940 50  0000 C CNN
F 2 "" H 6400 2800 50  0000 C CNN
F 3 "" H 6400 2800 50  0000 C CNN
	1    6400 2800
	1    0    0    -1  
$EndComp
$Comp
L Jack_3.5mm_5pin J1
U 1 1 59341E91
P 3150 1800
F 0 "J1" H 3150 2050 60  0000 C CNN
F 1 "Audio Out" H 3150 1500 60  0000 C CNN
F 2 "added:AudioJack3.5mm" H 3150 1850 60  0001 C CNN
F 3 "" H 3150 1850 60  0000 C CNN
	1    3150 1800
	1    0    0    1   
$EndComp
$Comp
L R R1
U 1 1 59341ED4
P 1800 1600
F 0 "R1" V 1880 1600 50  0000 C CNN
F 1 "1k" V 1800 1600 50  0000 C CNN
F 2 "Resistors_THT:Resistor_Horizontal_RM10mm" V 1730 1600 50  0001 C CNN
F 3 "" H 1800 1600 50  0000 C CNN
	1    1800 1600
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 59341F23
P 2000 1850
F 0 "C2" H 2025 1950 50  0000 L CNN
F 1 "10n" H 2025 1750 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L4_W2.5_P2.5" H 2038 1700 50  0001 C CNN
F 3 "" H 2000 1850 50  0000 C CNN
	1    2000 1850
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 59341F63
P 2200 1600
F 0 "C1" H 2225 1700 50  0000 L CNN
F 1 "10µ" H 2225 1500 50  0000 L CNN
F 2 "Capacitors_THT:C_Radial_D5_L11_P2" H 2238 1450 50  0001 C CNN
F 3 "" H 2200 1600 50  0000 C CNN
	1    2200 1600
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 P1
U 1 1 59342657
P 2600 1100
F 0 "P1" H 2600 1300 50  0000 C CNN
F 1 "Sync" V 2700 1100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 2600 1100 50  0001 C CNN
F 3 "" H 2600 1100 50  0000 C CNN
	1    2600 1100
	0    -1   -1   0   
$EndComp
Text GLabel 2800 1300 2    60   Input ~ 0
Sync
Wire Wire Line
	2600 1700 3000 1700
Wire Wire Line
	2500 1300 2500 1900
Wire Wire Line
	2700 1300 2800 1300
Wire Wire Line
	2600 1300 2600 1700
Connection ~ 2500 1600
$Comp
L GND #PWR06
U 1 1 5934292E
P 2000 2000
F 0 "#PWR06" H 2000 1750 50  0001 C CNN
F 1 "GND" H 2000 1850 50  0000 C CNN
F 2 "" H 2000 2000 50  0000 C CNN
F 3 "" H 2000 2000 50  0000 C CNN
	1    2000 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5934294E
P 2900 2050
F 0 "#PWR07" H 2900 1800 50  0001 C CNN
F 1 "GND" H 2900 1900 50  0000 C CNN
F 2 "" H 2900 2050 50  0000 C CNN
F 3 "" H 2900 2050 50  0000 C CNN
	1    2900 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1600 2500 1600
Wire Wire Line
	1950 1600 2050 1600
Wire Wire Line
	2000 1700 2000 1600
Connection ~ 2000 1600
Wire Wire Line
	2900 2050 2900 2000
Wire Wire Line
	2900 2000 3000 2000
Wire Wire Line
	2500 1900 3000 1900
Text GLabel 1650 1600 0    60   Input ~ 0
AudioOut
Wire Wire Line
	4550 3400 4850 3400
Text GLabel 4550 3250 0    60   Input ~ 0
Sync
Wire Wire Line
	4550 3250 4600 3250
Wire Wire Line
	4600 3250 4600 3300
Wire Wire Line
	4600 3300 4850 3300
Wire Wire Line
	6050 2900 6400 2900
Wire Wire Line
	6400 2900 6400 2800
Wire Wire Line
	6400 3100 6400 3200
Wire Wire Line
	6400 3200 6050 3200
Wire Wire Line
	3850 3200 3850 3150
Wire Wire Line
	3850 3150 4650 3150
Wire Wire Line
	4650 3150 4650 3200
Wire Wire Line
	4650 3200 4850 3200
$Comp
L SWITCH_SPST SW3
U 1 1 59342B78
P 3150 4250
F 0 "SW3" H 3150 4400 60  0000 C CNN
F 1 "Button 2" H 3150 4150 60  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 3150 4250 60  0001 C CNN
F 3 "" H 3150 4250 60  0000 C CNN
	1    3150 4250
	0    1    1    0   
$EndComp
$Comp
L SWITCH_SPST SW4
U 1 1 59342C44
P 3500 4250
F 0 "SW4" H 3500 4400 60  0000 C CNN
F 1 "Button 3" H 3500 4150 60  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 3500 4250 60  0001 C CNN
F 3 "" H 3500 4250 60  0000 C CNN
	1    3500 4250
	0    1    1    0   
$EndComp
$Comp
L SWITCH_SPST SW5
U 1 1 59342C6F
P 3850 4250
F 0 "SW5" H 3850 4400 60  0000 C CNN
F 1 "Button 4" H 3850 4150 60  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 3850 4250 60  0001 C CNN
F 3 "" H 3850 4250 60  0000 C CNN
	1    3850 4250
	0    1    1    0   
$EndComp
$Comp
L SWITCH_SPST SW6
U 1 1 59342CA2
P 4200 4250
F 0 "SW6" H 4200 4400 60  0000 C CNN
F 1 "Button 5" H 4200 4150 60  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 4200 4250 60  0001 C CNN
F 3 "" H 4200 4250 60  0000 C CNN
	1    4200 4250
	0    1    1    0   
$EndComp
$Comp
L SWITCH_SPST SW7
U 1 1 59342CD8
P 4550 4250
F 0 "SW7" H 4550 4400 60  0000 C CNN
F 1 "Button 6" H 4550 4150 60  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 4550 4250 60  0001 C CNN
F 3 "" H 4550 4250 60  0000 C CNN
	1    4550 4250
	0    1    1    0   
$EndComp
$Comp
L SWITCH_SPST SW2
U 1 1 59342D10
P 2800 4250
F 0 "SW2" H 2800 4400 60  0000 C CNN
F 1 "Button 1" H 2800 4150 60  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 2800 4250 60  0001 C CNN
F 3 "" H 2800 4250 60  0000 C CNN
	1    2800 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 3500 2800 3500
Wire Wire Line
	2800 3500 2800 4050
Wire Wire Line
	3150 4050 3150 3600
Wire Wire Line
	3150 3600 4850 3600
Wire Wire Line
	4850 3700 3500 3700
Wire Wire Line
	3500 3700 3500 4050
Wire Wire Line
	3850 4050 3850 3800
Wire Wire Line
	3850 3800 4850 3800
Wire Wire Line
	4850 3900 4200 3900
Wire Wire Line
	4200 3900 4200 4050
Wire Wire Line
	4850 4000 4550 4000
Wire Wire Line
	4550 4000 4550 4050
$Comp
L SWITCH_SPST SW1
U 1 1 59342E8A
P 2450 4250
F 0 "SW1" H 2450 4400 60  0000 C CNN
F 1 "Reset" H 2450 4150 60  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 2450 4250 60  0001 C CNN
F 3 "" H 2450 4250 60  0000 C CNN
	1    2450 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 4050 2450 3100
Wire Wire Line
	2450 3100 4850 3100
$Comp
L GND #PWR08
U 1 1 59343025
P 2450 4450
F 0 "#PWR08" H 2450 4200 50  0001 C CNN
F 1 "GND" H 2450 4300 50  0000 C CNN
F 2 "" H 2450 4450 50  0000 C CNN
F 3 "" H 2450 4450 50  0000 C CNN
	1    2450 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5934305A
P 2800 4450
F 0 "#PWR09" H 2800 4200 50  0001 C CNN
F 1 "GND" H 2800 4300 50  0000 C CNN
F 2 "" H 2800 4450 50  0000 C CNN
F 3 "" H 2800 4450 50  0000 C CNN
	1    2800 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5934308F
P 3150 4450
F 0 "#PWR010" H 3150 4200 50  0001 C CNN
F 1 "GND" H 3150 4300 50  0000 C CNN
F 2 "" H 3150 4450 50  0000 C CNN
F 3 "" H 3150 4450 50  0000 C CNN
	1    3150 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 593430C4
P 3500 4450
F 0 "#PWR011" H 3500 4200 50  0001 C CNN
F 1 "GND" H 3500 4300 50  0000 C CNN
F 2 "" H 3500 4450 50  0000 C CNN
F 3 "" H 3500 4450 50  0000 C CNN
	1    3500 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 593430F9
P 3850 4450
F 0 "#PWR012" H 3850 4200 50  0001 C CNN
F 1 "GND" H 3850 4300 50  0000 C CNN
F 2 "" H 3850 4450 50  0000 C CNN
F 3 "" H 3850 4450 50  0000 C CNN
	1    3850 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5934312E
P 4200 4450
F 0 "#PWR013" H 4200 4200 50  0001 C CNN
F 1 "GND" H 4200 4300 50  0000 C CNN
F 2 "" H 4200 4450 50  0000 C CNN
F 3 "" H 4200 4450 50  0000 C CNN
	1    4200 4450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 59343163
P 4550 4450
F 0 "#PWR014" H 4550 4200 50  0001 C CNN
F 1 "GND" H 4550 4300 50  0000 C CNN
F 2 "" H 4550 4450 50  0000 C CNN
F 3 "" H 4550 4450 50  0000 C CNN
	1    4550 4450
	1    0    0    -1  
$EndComp
Text GLabel 6450 3600 2    60   Input ~ 0
A0
Text GLabel 6700 3500 2    60   Input ~ 0
A1
Text GLabel 6450 3400 2    60   Input ~ 0
A2
Text GLabel 6700 3300 2    60   Input ~ 0
A3
Wire Wire Line
	6050 3300 6700 3300
Wire Wire Line
	6050 3400 6450 3400
Wire Wire Line
	6700 3500 6050 3500
Wire Wire Line
	6050 3600 6450 3600
$Comp
L POT RV1
U 1 1 593434FC
P 1950 6700
F 0 "RV1" V 1775 6700 50  0000 C CNN
F 1 "10k" V 1850 6700 50  0000 C CNN
F 2 "added:Potentiometer_Alpha-RV09" H 1950 6700 50  0001 C CNN
F 3 "" H 1950 6700 50  0000 C CNN
	1    1950 6700
	-1   0    0    1   
$EndComp
Text GLabel 1800 6700 0    60   Input ~ 0
A0
$Comp
L VCC #PWR015
U 1 1 593435B6
P 1950 6550
F 0 "#PWR015" H 1950 6400 50  0001 C CNN
F 1 "VCC" H 1950 6700 50  0000 C CNN
F 2 "" H 1950 6550 50  0000 C CNN
F 3 "" H 1950 6550 50  0000 C CNN
	1    1950 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 593435EE
P 1950 6850
F 0 "#PWR016" H 1950 6600 50  0001 C CNN
F 1 "GND" H 1950 6700 50  0000 C CNN
F 2 "" H 1950 6850 50  0000 C CNN
F 3 "" H 1950 6850 50  0000 C CNN
	1    1950 6850
	1    0    0    -1  
$EndComp
$Comp
L POT RV2
U 1 1 59343642
P 2550 6700
F 0 "RV2" V 2375 6700 50  0000 C CNN
F 1 "10k" V 2450 6700 50  0000 C CNN
F 2 "added:Potentiometer_Alpha-RV09" H 2550 6700 50  0001 C CNN
F 3 "" H 2550 6700 50  0000 C CNN
	1    2550 6700
	-1   0    0    1   
$EndComp
Text GLabel 2400 6700 0    60   Input ~ 0
A1
$Comp
L VCC #PWR017
U 1 1 59343649
P 2550 6550
F 0 "#PWR017" H 2550 6400 50  0001 C CNN
F 1 "VCC" H 2550 6700 50  0000 C CNN
F 2 "" H 2550 6550 50  0000 C CNN
F 3 "" H 2550 6550 50  0000 C CNN
	1    2550 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5934364F
P 2550 6850
F 0 "#PWR018" H 2550 6600 50  0001 C CNN
F 1 "GND" H 2550 6700 50  0000 C CNN
F 2 "" H 2550 6850 50  0000 C CNN
F 3 "" H 2550 6850 50  0000 C CNN
	1    2550 6850
	1    0    0    -1  
$EndComp
$Comp
L POT RV3
U 1 1 59343729
P 3150 6700
F 0 "RV3" V 2975 6700 50  0000 C CNN
F 1 "10k" V 3050 6700 50  0000 C CNN
F 2 "added:Potentiometer_Alpha-RV09" H 3150 6700 50  0001 C CNN
F 3 "" H 3150 6700 50  0000 C CNN
	1    3150 6700
	-1   0    0    1   
$EndComp
Text GLabel 3000 6700 0    60   Input ~ 0
A2
$Comp
L VCC #PWR019
U 1 1 59343730
P 3150 6550
F 0 "#PWR019" H 3150 6400 50  0001 C CNN
F 1 "VCC" H 3150 6700 50  0000 C CNN
F 2 "" H 3150 6550 50  0000 C CNN
F 3 "" H 3150 6550 50  0000 C CNN
	1    3150 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 59343736
P 3150 6850
F 0 "#PWR020" H 3150 6600 50  0001 C CNN
F 1 "GND" H 3150 6700 50  0000 C CNN
F 2 "" H 3150 6850 50  0000 C CNN
F 3 "" H 3150 6850 50  0000 C CNN
	1    3150 6850
	1    0    0    -1  
$EndComp
$Comp
L POT RV4
U 1 1 5934373C
P 3750 6700
F 0 "RV4" V 3575 6700 50  0000 C CNN
F 1 "10k" V 3650 6700 50  0000 C CNN
F 2 "added:Potentiometer_Alpha-RV09" H 3750 6700 50  0001 C CNN
F 3 "" H 3750 6700 50  0000 C CNN
	1    3750 6700
	-1   0    0    1   
$EndComp
Text GLabel 3600 6700 0    60   Input ~ 0
A3
$Comp
L VCC #PWR021
U 1 1 59343743
P 3750 6550
F 0 "#PWR021" H 3750 6400 50  0001 C CNN
F 1 "VCC" H 3750 6700 50  0000 C CNN
F 2 "" H 3750 6550 50  0000 C CNN
F 3 "" H 3750 6550 50  0000 C CNN
	1    3750 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 59343749
P 3750 6850
F 0 "#PWR022" H 3750 6600 50  0001 C CNN
F 1 "GND" H 3750 6700 50  0000 C CNN
F 2 "" H 3750 6850 50  0000 C CNN
F 3 "" H 3750 6850 50  0000 C CNN
	1    3750 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 5300 3200 5300
Wire Wire Line
	3200 5300 3200 5250
Wire Wire Line
	2800 5500 3050 5500
Wire Wire Line
	3050 5500 3050 5600
Text GLabel 6250 4200 2    60   Input ~ 0
A4
Wire Wire Line
	6050 4200 6250 4200
$Comp
L POT RV5
U 1 1 59344D9C
P 4350 6700
F 0 "RV5" V 4175 6700 50  0000 C CNN
F 1 "10k" V 4250 6700 50  0000 C CNN
F 2 "added:Potentiometer_Alpha-RV09" H 4350 6700 50  0001 C CNN
F 3 "" H 4350 6700 50  0000 C CNN
	1    4350 6700
	-1   0    0    1   
$EndComp
Text GLabel 4200 6700 0    60   Input ~ 0
A4
$Comp
L VCC #PWR023
U 1 1 59344DA3
P 4350 6550
F 0 "#PWR023" H 4350 6400 50  0001 C CNN
F 1 "VCC" H 4350 6700 50  0000 C CNN
F 2 "" H 4350 6550 50  0000 C CNN
F 3 "" H 4350 6550 50  0000 C CNN
	1    4350 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 59344DA9
P 4350 6850
F 0 "#PWR024" H 4350 6600 50  0001 C CNN
F 1 "GND" H 4350 6700 50  0000 C CNN
F 2 "" H 4350 6850 50  0000 C CNN
F 3 "" H 4350 6850 50  0000 C CNN
	1    4350 6850
	1    0    0    -1  
$EndComp
$Comp
L Jack_3.5mm_5pin J2
U 1 1 5935AED2
P 9500 1600
F 0 "J2" H 9500 1850 60  0000 C CNN
F 1 "Addit. Plug 1" H 9500 1300 60  0000 C CNN
F 2 "added:AudioJack3.5mm" H 9500 1650 60  0001 C CNN
F 3 "" H 9500 1650 60  0000 C CNN
	1    9500 1600
	1    0    0    1   
$EndComp
$Comp
L CONN_01X03 P2
U 1 1 5935AF5F
P 8750 1300
F 0 "P2" H 8750 1500 50  0000 C CNN
F 1 "AP1" V 8850 1300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 8750 1300 50  0001 C CNN
F 3 "" H 8750 1300 50  0000 C CNN
	1    8750 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8650 1800 9350 1800
Wire Wire Line
	8650 1800 8650 1500
Wire Wire Line
	9100 1500 9350 1500
Wire Wire Line
	9100 1500 9100 1600
Wire Wire Line
	9100 1600 8750 1600
Wire Wire Line
	8750 1600 8750 1500
Wire Wire Line
	8850 1500 8850 1700
Wire Wire Line
	8850 1700 9350 1700
$Comp
L Jack_3.5mm_5pin J3
U 1 1 5935B39B
P 9550 2450
F 0 "J3" H 9550 2700 60  0000 C CNN
F 1 "Addit. Plug 2" H 9550 2150 60  0000 C CNN
F 2 "added:AudioJack3.5mm" H 9550 2500 60  0001 C CNN
F 3 "" H 9550 2500 60  0000 C CNN
	1    9550 2450
	1    0    0    1   
$EndComp
$Comp
L CONN_01X03 P4
U 1 1 5935B3A1
P 8800 2150
F 0 "P4" H 8800 2350 50  0000 C CNN
F 1 "AP2" V 8900 2150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 8800 2150 50  0001 C CNN
F 3 "" H 8800 2150 50  0000 C CNN
	1    8800 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 2650 9400 2650
Wire Wire Line
	8700 2650 8700 2350
Wire Wire Line
	9150 2350 9400 2350
Wire Wire Line
	9150 2350 9150 2450
Wire Wire Line
	9150 2450 8800 2450
Wire Wire Line
	8800 2450 8800 2350
Wire Wire Line
	8900 2350 8900 2550
Wire Wire Line
	8900 2550 9400 2550
$Comp
L CONN_01X02 P3
U 1 1 5935B83D
P 8300 1650
F 0 "P3" H 8300 1800 50  0000 C CNN
F 1 "AP1_GND" V 8400 1650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8300 1650 50  0001 C CNN
F 3 "" H 8300 1650 50  0000 C CNN
	1    8300 1650
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X02 P5
U 1 1 5935B8C8
P 8300 2450
F 0 "P5" H 8300 2600 50  0000 C CNN
F 1 "AP2_GND" V 8400 2450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8300 2450 50  0001 C CNN
F 3 "" H 8300 2450 50  0000 C CNN
	1    8300 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	8500 2400 8700 2400
Connection ~ 8700 2400
Wire Wire Line
	8500 1600 8650 1600
Connection ~ 8650 1600
$Comp
L GND #PWR025
U 1 1 5935BAAE
P 8500 2500
F 0 "#PWR025" H 8500 2250 50  0001 C CNN
F 1 "GND" H 8500 2350 50  0000 C CNN
F 2 "" H 8500 2500 50  0000 C CNN
F 3 "" H 8500 2500 50  0000 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 5935BB04
P 8500 1700
F 0 "#PWR026" H 8500 1450 50  0001 C CNN
F 1 "GND" H 8500 1550 50  0000 C CNN
F 2 "" H 8500 1700 50  0000 C CNN
F 3 "" H 8500 1700 50  0000 C CNN
	1    8500 1700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P6
U 1 1 5935BC15
P 9000 3300
F 0 "P6" H 9000 3650 50  0000 C CNN
F 1 "Analog Pins" V 9100 3300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 9000 3300 50  0001 C CNN
F 3 "" H 9000 3300 50  0000 C CNN
	1    9000 3300
	1    0    0    -1  
$EndComp
Text GLabel 8650 3050 0    60   Input ~ 0
A0
Text GLabel 8400 3150 0    60   Input ~ 0
A1
Text GLabel 8650 3250 0    60   Input ~ 0
A2
Text GLabel 8400 3350 0    60   Input ~ 0
A3
Text GLabel 8650 3450 0    60   Input ~ 0
A4
Text GLabel 6450 4300 2    60   Input ~ 0
A5
Wire Wire Line
	6050 4300 6450 4300
Text GLabel 8400 3550 0    60   Input ~ 0
A5
Wire Wire Line
	8650 3050 8800 3050
Wire Wire Line
	8800 3150 8400 3150
Wire Wire Line
	8650 3250 8800 3250
Wire Wire Line
	8800 3350 8400 3350
Wire Wire Line
	8800 3450 8650 3450
Wire Wire Line
	8800 3550 8400 3550
Text GLabel 6200 3700 2    60   Input ~ 0
D13
Text GLabel 6450 3800 2    60   Input ~ 0
D12
Text GLabel 6200 3900 2    60   Input ~ 0
D11
Text GLabel 6450 4000 2    60   Input ~ 0
D10
Wire Wire Line
	6050 3700 6200 3700
Wire Wire Line
	6450 3800 6050 3800
Wire Wire Line
	6050 3900 6200 3900
Wire Wire Line
	6050 4000 6450 4000
Text GLabel 8650 3850 0    60   Input ~ 0
D10
Text GLabel 8400 3950 0    60   Input ~ 0
D11
$Comp
L CONN_01X04 P7
U 1 1 5935CB3D
P 9000 4000
F 0 "P7" H 9000 4250 50  0000 C CNN
F 1 "Digital Pins" V 9100 4000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 9000 4000 50  0001 C CNN
F 3 "" H 9000 4000 50  0000 C CNN
	1    9000 4000
	1    0    0    -1  
$EndComp
Text GLabel 8650 4050 0    60   Input ~ 0
D12
Text GLabel 8400 4150 0    60   Input ~ 0
D13
Wire Wire Line
	8650 3850 8800 3850
Wire Wire Line
	8800 3950 8400 3950
Wire Wire Line
	8650 4050 8800 4050
Wire Wire Line
	8800 4150 8400 4150
$Comp
L CONN_01X06 P8
U 1 1 5935CFC7
P 9000 4700
F 0 "P8" H 9000 5050 50  0000 C CNN
F 1 "Power Pins" V 9100 4700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 9000 4700 50  0001 C CNN
F 3 "" H 9000 4700 50  0000 C CNN
	1    9000 4700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR027
U 1 1 5935D0B1
P 8650 4400
F 0 "#PWR027" H 8650 4250 50  0001 C CNN
F 1 "VCC" H 8650 4550 50  0000 C CNN
F 2 "" H 8650 4400 50  0000 C CNN
F 3 "" H 8650 4400 50  0000 C CNN
	1    8650 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 5935D110
P 8650 5000
F 0 "#PWR028" H 8650 4750 50  0001 C CNN
F 1 "GND" H 8650 4850 50  0000 C CNN
F 2 "" H 8650 5000 50  0000 C CNN
F 3 "" H 8650 5000 50  0000 C CNN
	1    8650 5000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P9
U 1 1 5935D1FD
P 9000 5400
F 0 "P9" H 9000 5550 50  0000 C CNN
F 1 "Outputs" V 9100 5400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 9000 5400 50  0001 C CNN
F 3 "" H 9000 5400 50  0000 C CNN
	1    9000 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 4450 8800 4450
Wire Wire Line
	8650 4400 8650 4650
Wire Wire Line
	8650 4550 8800 4550
Wire Wire Line
	8650 4650 8800 4650
Connection ~ 8650 4550
Connection ~ 8650 4450
Wire Wire Line
	8650 5000 8650 4750
Wire Wire Line
	8650 4750 8800 4750
Wire Wire Line
	8800 4850 8650 4850
Connection ~ 8650 4850
Wire Wire Line
	8800 4950 8650 4950
Connection ~ 8650 4950
Text GLabel 8650 5450 0    60   Input ~ 0
Sync
Text GLabel 8350 5350 0    60   Input ~ 0
AudioOut
Wire Wire Line
	8350 5350 8800 5350
Wire Wire Line
	8800 5450 8650 5450
$Comp
L USB_OTG P10
U 1 1 5937399C
P 5600 5650
F 0 "P10" H 5925 5525 50  0000 C CNN
F 1 "USB_OTG" H 5600 5850 50  0000 C CNN
F 2 "Connectors:USB_Micro-B" V 5550 5550 50  0001 C CNN
F 3 "" V 5550 5550 50  0000 C CNN
	1    5600 5650
	0    -1   1    0   
$EndComp
$Comp
L VCC #PWR029
U 1 1 59373A8F
P 5900 5450
F 0 "#PWR029" H 5900 5300 50  0001 C CNN
F 1 "VCC" H 5900 5600 50  0000 C CNN
F 2 "" H 5900 5450 50  0000 C CNN
F 3 "" H 5900 5450 50  0000 C CNN
	1    5900 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 59373C2B
P 5900 5850
F 0 "#PWR030" H 5900 5600 50  0001 C CNN
F 1 "GND" H 5900 5700 50  0000 C CNN
F 2 "" H 5900 5850 50  0000 C CNN
F 3 "" H 5900 5850 50  0000 C CNN
	1    5900 5850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
