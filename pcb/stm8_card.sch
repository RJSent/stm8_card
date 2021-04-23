EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "stm8_card"
Date "2021-04-21"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L stm8_card:STM8S103F3 U2
U 1 1 60826CD3
P 8100 3000
F 0 "U2" H 8400 3750 50  0000 C CNN
F 1 "STM8S103F3" H 8400 3650 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 9000 3850 50  0000 C CNN
F 3 "~" H 8500 3000 50  0001 C CNN
	1    8100 3000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 608279B5
P 3950 4050
F 0 "SW1" H 3950 4335 50  0000 C CNN
F 1 "TL59AF100Q" H 3950 4334 50  0001 C CNN
F 2 "stm8_card:TL59AF100Q" H 3950 4250 50  0001 C CNN
F 3 "~" H 3950 4250 50  0001 C CNN
F 4 "EG4378CT-ND" H 3950 4244 50  0000 C CNN "digikey"
	1    3950 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 608281CA
P 3950 4950
F 0 "SW3" H 3950 5235 50  0000 C CNN
F 1 "TL59AF100Q" H 3950 5234 50  0001 C CNN
F 2 "stm8_card:TL59AF100Q" H 3950 5150 50  0001 C CNN
F 3 "~" H 3950 5150 50  0001 C CNN
F 4 "EG4378CT-ND" H 3950 5144 50  0000 C CNN "digikey"
	1    3950 4950
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 608286D3
P 3950 4500
F 0 "SW2" H 3950 4785 50  0000 C CNN
F 1 "TL59AF100Q" H 3950 4784 50  0001 C CNN
F 2 "stm8_card:TL59AF100Q" H 3950 4700 50  0001 C CNN
F 3 "~" H 3950 4700 50  0001 C CNN
F 4 "EG4378CT-ND" H 3950 4694 50  0000 C CNN "digikey"
	1    3950 4500
	1    0    0    -1  
$EndComp
$Comp
L stm8_card:ER-OLED0.91-7 U1
U 1 1 608105A9
P 2500 2100
F 0 "U1" H 2800 2850 50  0000 C CNN
F 1 "ER-OLED0.91-7" H 2850 2750 50  0000 C CNN
F 2 "stm8_card:ER-OLED0.91-7" H 1000 2500 50  0001 C CNN
F 3 "" H 1000 2500 50  0001 C CNN
	1    2500 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 60813C31
P 4600 4050
F 0 "R4" V 4500 4050 50  0000 C CNN
F 1 "4.7k" V 4600 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 4050 50  0001 C CNN
F 3 "~" H 4600 4050 50  0001 C CNN
	1    4600 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 608142DD
P 4600 4500
F 0 "R5" V 4500 4500 50  0000 C CNN
F 1 "4.7k" V 4600 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 4500 50  0001 C CNN
F 3 "~" H 4600 4500 50  0001 C CNN
	1    4600 4500
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 608145EE
P 4600 4950
F 0 "R6" V 4500 4950 50  0000 C CNN
F 1 "4.7k" V 4600 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 4950 50  0001 C CNN
F 3 "~" H 4600 4950 50  0001 C CNN
	1    4600 4950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6081C487
P 6100 4650
F 0 "#PWR08" H 6100 4400 50  0001 C CNN
F 1 "GND" H 6105 4477 50  0000 C CNN
F 2 "" H 6100 4650 50  0001 C CNN
F 3 "" H 6100 4650 50  0001 C CNN
	1    6100 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 6081E543
P 1300 4400
F 0 "BT1" H 1550 4500 50  0000 L CNN
F 1 "103" H 1418 4405 50  0001 L CNN
F 2 "stm8_card:BatteryHolder_Keystone_103_1x20mm_Corrected" V 1300 4460 50  0001 C CNN
F 3 "~" V 1300 4460 50  0001 C CNN
F 4 "36-103-ND" H 1650 4400 50  0000 C CNN "digikey"
	1    1300 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6081EBFF
P 4700 2100
F 0 "#PWR06" H 4700 1850 50  0001 C CNN
F 1 "GND" H 4705 1927 50  0000 C CNN
F 2 "" H 4700 2100 50  0001 C CNN
F 3 "" H 4700 2100 50  0001 C CNN
	1    4700 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3950 3500 4050
Wire Wire Line
	3500 4950 3750 4950
Wire Wire Line
	3750 4500 3500 4500
Connection ~ 3500 4500
Wire Wire Line
	3500 4500 3500 4950
Wire Wire Line
	3750 4050 3500 4050
Connection ~ 3500 4050
Wire Wire Line
	3500 4050 3500 4500
Connection ~ 4800 4950
Wire Wire Line
	4750 4050 4800 4050
Wire Wire Line
	4750 4950 4800 4950
Wire Wire Line
	4150 4050 4200 4050
Wire Wire Line
	4150 4500 4200 4500
Wire Wire Line
	4150 4950 4200 4950
Wire Wire Line
	4800 4050 4800 4500
Wire Wire Line
	4750 4500 4800 4500
Connection ~ 4800 4500
Wire Wire Line
	4800 4500 4800 4950
Text GLabel 1250 4000 0    50   Input ~ 0
3v3
Text GLabel 3450 3950 0    50   Input ~ 0
3v3
Text GLabel 4250 3950 2    50   Input ~ 0
btn0
Text GLabel 4250 4400 2    50   Input ~ 0
btn1
Text GLabel 4250 4850 2    50   Input ~ 0
btn2
Wire Wire Line
	4200 3950 4200 4050
Connection ~ 4200 4050
Wire Wire Line
	4200 4050 4450 4050
Wire Wire Line
	4200 4400 4200 4500
Connection ~ 4200 4500
Wire Wire Line
	4200 4500 4450 4500
Wire Wire Line
	4200 4850 4200 4950
Connection ~ 4200 4950
Wire Wire Line
	4200 4950 4450 4950
Text GLabel 9100 2950 2    50   Input ~ 0
btn0
Text GLabel 9100 3050 2    50   Input ~ 0
btn1
Text GLabel 9100 3150 2    50   Input ~ 0
btn2
Wire Wire Line
	9100 2950 8850 2950
Wire Wire Line
	9100 3050 8850 3050
Wire Wire Line
	9100 3150 8850 3150
Text GLabel 4050 2350 2    50   Input ~ 0
SDA
Text GLabel 9100 3450 2    50   Input ~ 0
SDA
Text GLabel 4050 2500 2    50   Input ~ 0
SCL
Text GLabel 9100 3350 2    50   Input ~ 0
SCL
Wire Wire Line
	9100 3350 8850 3350
Wire Wire Line
	8850 3450 9100 3450
Text GLabel 7950 1850 0    50   Input ~ 0
3v3
Wire Wire Line
	3150 2800 3050 2800
Wire Wire Line
	6500 4600 6600 4600
Wire Wire Line
	6100 4600 6100 4650
$Comp
L power:GND #PWR010
U 1 1 6082B314
P 8100 3800
F 0 "#PWR010" H 8100 3550 50  0001 C CNN
F 1 "GND" H 8105 3627 50  0000 C CNN
F 2 "" H 8100 3800 50  0001 C CNN
F 3 "" H 8100 3800 50  0001 C CNN
	1    8100 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 6082D715
P 1400 1850
F 0 "C1" H 1492 1896 50  0000 L CNN
F 1 "1uf" H 1492 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1400 1850 50  0001 C CNN
F 3 "~" H 1400 1850 50  0001 C CNN
	1    1400 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 6082E3CB
P 1400 2150
F 0 "C2" H 1492 2196 50  0000 L CNN
F 1 "1uf" H 1492 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1400 2150 50  0001 C CNN
F 3 "~" H 1400 2150 50  0001 C CNN
	1    1400 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1750 2000 1750
Wire Wire Line
	2000 1900 1650 1900
Wire Wire Line
	1650 1900 1650 1950
Wire Wire Line
	1650 1950 1400 1950
Wire Wire Line
	1400 2050 2000 2050
Wire Wire Line
	1400 2250 1650 2250
Wire Wire Line
	1650 2250 1650 2200
Wire Wire Line
	1650 2200 2000 2200
$Comp
L Switch:SW_Push SW4
U 1 1 60827F4F
P 6300 4600
F 0 "SW4" H 6300 4900 50  0000 C CNN
F 1 "TL3302AF260QG" H 6300 4884 50  0001 C CNN
F 2 "stm8_card:TL3302AF260QG" H 6300 4800 50  0001 C CNN
F 3 "~" H 6300 4800 50  0001 C CNN
F 4 "EG4584CT-ND" H 6300 4794 50  0000 C CNN "digikey"
	1    6300 4600
	1    0    0    -1  
$EndComp
Text GLabel 6600 4600 2    50   Input ~ 0
NRST
Text GLabel 7250 3000 0    50   Input ~ 0
NRST
Text GLabel 3150 2800 2    50   Input ~ 0
NRST
Wire Wire Line
	7250 3000 7400 3000
Wire Wire Line
	3500 3950 3450 3950
Wire Wire Line
	4200 3950 4250 3950
Wire Wire Line
	4200 4400 4250 4400
Wire Wire Line
	4200 4850 4250 4850
$Comp
L power:GND #PWR04
U 1 1 60844B9E
P 2500 3200
F 0 "#PWR04" H 2500 2950 50  0001 C CNN
F 1 "GND" H 2505 3027 50  0000 C CNN
F 2 "" H 2500 3200 50  0001 C CNN
F 3 "" H 2500 3200 50  0001 C CNN
	1    2500 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3200 2500 3100
Wire Wire Line
	4050 2350 3950 2350
Wire Wire Line
	3050 2500 3650 2500
Connection ~ 3950 2350
Wire Wire Line
	3950 2350 3050 2350
Wire Wire Line
	3950 2350 3950 2550
Wire Wire Line
	3650 2550 3650 2500
Connection ~ 3650 2500
Wire Wire Line
	3650 2500 4050 2500
Wire Wire Line
	3800 2950 3950 2950
Connection ~ 3800 2950
Wire Wire Line
	3800 3050 3800 2950
Text GLabel 3800 3050 3    50   Input ~ 0
3v3
Wire Wire Line
	3950 2950 3950 2850
Wire Wire Line
	3650 2950 3800 2950
Wire Wire Line
	3650 2850 3650 2950
$Comp
L Device:R R3
U 1 1 60849F57
P 3950 2700
F 0 "R3" V 4050 2700 50  0000 C CNN
F 1 "4.7k" V 3950 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3880 2700 50  0001 C CNN
F 3 "~" H 3950 2700 50  0001 C CNN
	1    3950 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 608498CA
P 3650 2700
F 0 "R2" V 3750 2700 50  0000 C CNN
F 1 "4.7k" V 3650 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3580 2700 50  0001 C CNN
F 3 "~" H 3650 2700 50  0001 C CNN
	1    3650 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 608515E3
P 3300 2050
F 0 "R1" V 3350 2200 50  0000 C CNN
F 1 "390k" V 3300 2050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3230 2050 50  0001 C CNN
F 3 "~" H 3300 2050 50  0001 C CNN
	1    3300 2050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C7
U 1 1 60851930
P 3300 1900
F 0 "C7" V 3250 1800 50  0000 C CNN
F 1 "4.7uf" V 3250 2050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3300 1900 50  0001 C CNN
F 3 "~" H 3300 1900 50  0001 C CNN
	1    3300 1900
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 60851F1A
P 3300 1750
F 0 "C6" V 3250 1650 50  0000 C CNN
F 1 "2.2uf" V 3250 1900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3300 1750 50  0001 C CNN
F 3 "~" H 3300 1750 50  0001 C CNN
	1    3300 1750
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 60852DD5
P 3700 2150
F 0 "#PWR05" H 3700 1900 50  0001 C CNN
F 1 "GND" H 3600 2150 50  0000 C CNN
F 2 "" H 3700 2150 50  0001 C CNN
F 3 "" H 3700 2150 50  0001 C CNN
	1    3700 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2050 3150 2050
Wire Wire Line
	3050 1900 3200 1900
Wire Wire Line
	3050 1750 3200 1750
Wire Wire Line
	3400 1750 3700 1750
Wire Wire Line
	3700 1750 3700 1900
Wire Wire Line
	3400 1900 3700 1900
Connection ~ 3700 1900
Wire Wire Line
	3700 1900 3700 2050
Wire Wire Line
	3450 2050 3700 2050
Connection ~ 3700 2050
Wire Wire Line
	3700 2050 3700 2150
$Comp
L Device:C_Small C4
U 1 1 6085DCB0
P 1800 2900
F 0 "C4" H 1850 3000 50  0000 L CNN
F 1 "22nf" H 1850 2800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1800 2900 50  0001 C CNN
F 3 "~" H 1800 2900 50  0001 C CNN
	1    1800 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6085E004
P 1650 3200
F 0 "#PWR02" H 1650 2950 50  0001 C CNN
F 1 "GND" H 1655 3027 50  0000 C CNN
F 2 "" H 1650 3200 50  0001 C CNN
F 3 "" H 1650 3200 50  0001 C CNN
	1    1650 3200
	1    0    0    -1  
$EndComp
Text GLabel 1450 2550 0    50   Input ~ 0
3v3
$Comp
L Device:C_Small C3
U 1 1 608634F0
P 1500 2900
F 0 "C3" H 1550 3000 50  0000 L CNN
F 1 "1uf" H 1550 2800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1500 2900 50  0001 C CNN
F 3 "~" H 1500 2900 50  0001 C CNN
	1    1500 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3000 1500 3150
Wire Wire Line
	1500 3150 1650 3150
Connection ~ 1650 3150
Wire Wire Line
	1500 2800 1500 2550
Wire Wire Line
	1500 2550 1450 2550
Wire Wire Line
	2000 2550 1500 2550
Connection ~ 1500 2550
Wire Wire Line
	1650 3200 1650 3150
Wire Wire Line
	1800 3000 1800 3150
Wire Wire Line
	1650 3150 1800 3150
Wire Wire Line
	1800 2800 1800 2700
Wire Wire Line
	1800 2700 2000 2700
$Comp
L Connector_Generic:Conn_01x08 J1
U 1 1 608162A6
P 5250 1650
F 0 "J1" H 5330 1642 50  0000 L CNN
F 1 "DEBUG HEADER" H 5330 1551 50  0000 L CNN
F 2 "stm8_card:2mm_2x4_ICSP" H 5250 1650 50  0001 C CNN
F 3 "~" H 5250 1650 50  0001 C CNN
	1    5250 1650
	1    0    0    -1  
$EndComp
Text GLabel 4750 1350 0    50   Input ~ 0
3v3
Wire Wire Line
	5050 1350 4750 1350
Wire Wire Line
	5050 2050 4700 2050
Wire Wire Line
	4700 2050 4700 2100
Text GLabel 4750 1450 0    50   Input ~ 0
TX
Text GLabel 7250 2700 0    50   Input ~ 0
TX
Text GLabel 4750 1550 0    50   Input ~ 0
RX
Text GLabel 7250 2800 0    50   Input ~ 0
RX
Wire Wire Line
	4750 1450 5050 1450
Wire Wire Line
	4750 1550 5050 1550
Text GLabel 4750 1650 0    50   Input ~ 0
SWIM
Wire Wire Line
	4750 1650 5050 1650
Text GLabel 4750 1750 0    50   Input ~ 0
NRST
Wire Wire Line
	4750 1750 5050 1750
Text GLabel 9100 2750 2    50   Input ~ 0
SWIM
Wire Wire Line
	9100 2750 8850 2750
Wire Wire Line
	7250 2700 7400 2700
Wire Wire Line
	7250 2800 7400 2800
$Comp
L Device:C_Small C8
U 1 1 608B409C
P 7100 3600
F 0 "C8" H 7192 3646 50  0000 L CNN
F 1 "1uf" H 7192 3555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7100 3600 50  0001 C CNN
F 3 "~" H 7100 3600 50  0001 C CNN
	1    7100 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3400 7100 3400
$Comp
L power:GND #PWR09
U 1 1 608B7854
P 7100 3800
F 0 "#PWR09" H 7100 3550 50  0001 C CNN
F 1 "GND" H 7105 3627 50  0000 C CNN
F 2 "" H 7100 3800 50  0001 C CNN
F 3 "" H 7100 3800 50  0001 C CNN
	1    7100 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3800 7100 3700
Wire Wire Line
	7100 3500 7100 3400
Wire Wire Line
	8100 3800 8100 3700
$Comp
L power:GND #PWR07
U 1 1 60813F2A
P 4800 5050
F 0 "#PWR07" H 4800 4800 50  0001 C CNN
F 1 "GND" H 4805 4877 50  0000 C CNN
F 2 "" H 4800 5050 50  0001 C CNN
F 3 "" H 4800 5050 50  0001 C CNN
	1    4800 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4950 4800 5050
$Comp
L power:GND #PWR01
U 1 1 60827C7E
P 2250 4150
F 0 "#PWR01" H 2250 3900 50  0001 C CNN
F 1 "GND" H 2255 3977 50  0000 C CNN
F 2 "" H 2250 4150 50  0001 C CNN
F 3 "" H 2250 4150 50  0001 C CNN
	1    2250 4150
	1    0    0    -1  
$EndComp
NoConn ~ 8850 2550
NoConn ~ 8850 2650
NoConn ~ 8850 2850
NoConn ~ 8850 3250
NoConn ~ 7400 3300
NoConn ~ 7400 3500
NoConn ~ 7400 3100
NoConn ~ 7400 2600
NoConn ~ 5050 1850
NoConn ~ 5050 1950
$Comp
L power:PWR_FLAG #FLG01
U 1 1 6084AA5A
P 1300 4150
F 0 "#FLG01" H 1300 4225 50  0001 C CNN
F 1 "PWR_FLAG" V 1300 4277 50  0000 L CNN
F 2 "" H 1300 4150 50  0001 C CNN
F 3 "~" H 1300 4150 50  0001 C CNN
	1    1300 4150
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 6084B498
P 1300 4550
F 0 "#FLG02" H 1300 4625 50  0001 C CNN
F 1 "PWR_FLAG" V 1300 4677 50  0000 L CNN
F 2 "" H 1300 4550 50  0001 C CNN
F 3 "~" H 1300 4550 50  0001 C CNN
	1    1300 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 4000 1300 4000
Wire Wire Line
	1300 4000 1300 4150
Wire Wire Line
	1300 4200 1300 4150
Connection ~ 1300 4150
Wire Wire Line
	1300 4500 1300 4550
Connection ~ 1300 4550
Wire Wire Line
	2050 1300 2050 1400
Wire Wire Line
	2150 1300 2050 1300
Wire Wire Line
	2500 1050 2500 1300
Wire Wire Line
	2500 1300 2500 1400
Connection ~ 2500 1300
Wire Wire Line
	2500 1300 2350 1300
$Comp
L power:GND #PWR03
U 1 1 60888E69
P 2050 1400
F 0 "#PWR03" H 2050 1150 50  0001 C CNN
F 1 "GND" H 2055 1227 50  0000 C CNN
F 2 "" H 2050 1400 50  0001 C CNN
F 3 "" H 2050 1400 50  0001 C CNN
	1    2050 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 608724BC
P 2250 1300
F 0 "C5" V 2300 1350 50  0000 L CNN
F 1 "1uf" V 2300 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2250 1300 50  0001 C CNN
F 3 "~" H 2250 1300 50  0001 C CNN
	1    2250 1300
	0    -1   -1   0   
$EndComp
Text GLabel 2350 1050 0    50   Input ~ 0
3v3
Wire Wire Line
	2350 1050 2500 1050
$Comp
L Device:C_Small C9
U 1 1 6086F05B
P 7900 2100
F 0 "C9" V 7950 2150 50  0000 L CNN
F 1 "1uf" V 7950 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7900 2100 50  0001 C CNN
F 3 "~" H 7900 2100 50  0001 C CNN
	1    7900 2100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 6086F703
P 7700 2200
F 0 "#PWR0101" H 7700 1950 50  0001 C CNN
F 1 "GND" H 7705 2027 50  0000 C CNN
F 2 "" H 7700 2200 50  0001 C CNN
F 3 "" H 7700 2200 50  0001 C CNN
	1    7700 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1850 7950 1850
Wire Wire Line
	8100 1850 8100 2100
Wire Wire Line
	8000 2100 8100 2100
Connection ~ 8100 2100
Wire Wire Line
	8100 2100 8100 2300
Wire Wire Line
	7800 2100 7700 2100
Wire Wire Line
	7700 2100 7700 2200
$Comp
L Device:R R7
U 1 1 6087FF9F
P 2050 4000
F 0 "R7" V 1950 4000 50  0000 C CNN
F 1 "470" V 2050 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1980 4000 50  0001 C CNN
F 3 "~" H 2050 4000 50  0001 C CNN
	1    2050 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 6088C1B4
P 1700 4000
F 0 "D1" H 1693 3745 50  0000 C CNN
F 1 "LED" H 1693 3836 50  0000 C CNN
F 2 "stm8_card:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1700 4000 50  0001 C CNN
F 3 "~" H 1700 4000 50  0001 C CNN
F 4 "404-1316-1-ND" H 1700 4000 50  0001 C CNN "digikey"
	1    1700 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1300 4000 1550 4000
Connection ~ 1300 4000
Wire Wire Line
	1850 4000 1900 4000
Wire Wire Line
	2250 4000 2250 4150
Wire Wire Line
	2200 4000 2250 4000
$Comp
L power:GND #PWR?
U 1 1 608BFC4F
P 1300 4750
F 0 "#PWR?" H 1300 4500 50  0001 C CNN
F 1 "GND" H 1305 4577 50  0000 C CNN
F 2 "" H 1300 4750 50  0001 C CNN
F 3 "" H 1300 4750 50  0001 C CNN
	1    1300 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4550 1300 4750
$EndSCHEMATC
