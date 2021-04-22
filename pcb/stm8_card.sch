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
L stm8_card:stm8s103f3 U?
U 1 1 60826CD3
P 8100 3000
F 0 "U?" H 8400 3750 50  0000 C CNN
F 1 "stm8s103f3" H 8400 3650 50  0000 C CNN
F 2 "" H 8500 3000 50  0001 C CNN
F 3 "~" H 8500 3000 50  0001 C CNN
	1    8100 3000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 608279B5
P 3950 4050
F 0 "SW?" H 3950 4335 50  0000 C CNN
F 1 "TL59AF100Q" H 3950 4334 50  0001 C CNN
F 2 "" H 3950 4250 50  0001 C CNN
F 3 "~" H 3950 4250 50  0001 C CNN
F 4 "EG4378CT-ND" H 3950 4244 50  0000 C CNN "digikey"
	1    3950 4050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 608281CA
P 3950 4950
F 0 "SW?" H 3950 5235 50  0000 C CNN
F 1 "TL59AF100Q" H 3950 5234 50  0001 C CNN
F 2 "" H 3950 5150 50  0001 C CNN
F 3 "~" H 3950 5150 50  0001 C CNN
F 4 "EG4378CT-ND" H 3950 5144 50  0000 C CNN "digikey"
	1    3950 4950
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 608286D3
P 3950 4500
F 0 "SW?" H 3950 4785 50  0000 C CNN
F 1 "TL59AF100Q" H 3950 4784 50  0001 C CNN
F 2 "" H 3950 4700 50  0001 C CNN
F 3 "~" H 3950 4700 50  0001 C CNN
F 4 "EG4378CT-ND" H 3950 4694 50  0000 C CNN "digikey"
	1    3950 4500
	1    0    0    -1  
$EndComp
$Comp
L stm8_card:ER-OLED0.91-7 U?
U 1 1 608105A9
P 2500 2100
F 0 "U?" H 2800 2850 50  0000 C CNN
F 1 "ER-OLED0.91-7" H 2850 2750 50  0000 C CNN
F 2 "" H 1000 2500 50  0001 C CNN
F 3 "" H 1000 2500 50  0001 C CNN
	1    2500 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60813C31
P 4600 4050
F 0 "R?" V 4500 4050 50  0000 C CNN
F 1 "4.7k" V 4600 4050 50  0000 C CNN
F 2 "" V 4530 4050 50  0001 C CNN
F 3 "~" H 4600 4050 50  0001 C CNN
	1    4600 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 608142DD
P 4600 4500
F 0 "R?" V 4500 4500 50  0000 C CNN
F 1 "4.7k" V 4600 4500 50  0000 C CNN
F 2 "" V 4530 4500 50  0001 C CNN
F 3 "~" H 4600 4500 50  0001 C CNN
	1    4600 4500
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 608145EE
P 4600 4950
F 0 "R?" V 4500 4950 50  0000 C CNN
F 1 "4.7k" V 4600 4950 50  0000 C CNN
F 2 "" V 4530 4950 50  0001 C CNN
F 3 "~" H 4600 4950 50  0001 C CNN
	1    4600 4950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6081C487
P 6100 4700
F 0 "#PWR?" H 6100 4450 50  0001 C CNN
F 1 "GND" H 6105 4527 50  0000 C CNN
F 2 "" H 6100 4700 50  0001 C CNN
F 3 "" H 6100 4700 50  0001 C CNN
	1    6100 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 6081E543
P 1300 4400
F 0 "BT?" H 1418 4496 50  0000 L CNN
F 1 "Battery_Cell" H 1418 4405 50  0000 L CNN
F 2 "" V 1300 4460 50  0001 C CNN
F 3 "~" V 1300 4460 50  0001 C CNN
	1    1300 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6081EBFF
P 4700 2100
F 0 "#PWR?" H 4700 1850 50  0001 C CNN
F 1 "GND" H 4705 1927 50  0000 C CNN
F 2 "" H 4700 2100 50  0001 C CNN
F 3 "" H 4700 2100 50  0001 C CNN
	1    4700 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4200 1300 4050
Wire Wire Line
	1300 4600 1300 4500
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
	4800 4950 4800 5150
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
Text GLabel 1250 4050 0    50   Input ~ 0
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
Text GLabel 8050 2200 0    50   Input ~ 0
3v3
Wire Wire Line
	8050 2200 8100 2200
Wire Wire Line
	8100 2200 8100 2300
Wire Wire Line
	3150 2800 3050 2800
Wire Wire Line
	6500 4650 6600 4650
Wire Wire Line
	6100 4650 6100 4700
$Comp
L power:GND #PWR?
U 1 1 6082B314
P 8100 3750
F 0 "#PWR?" H 8100 3500 50  0001 C CNN
F 1 "GND" H 8105 3577 50  0000 C CNN
F 2 "" H 8100 3750 50  0001 C CNN
F 3 "" H 8100 3750 50  0001 C CNN
	1    8100 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6082D715
P 1400 1850
F 0 "C?" H 1492 1896 50  0000 L CNN
F 1 "1uf" H 1492 1805 50  0000 L CNN
F 2 "" H 1400 1850 50  0001 C CNN
F 3 "~" H 1400 1850 50  0001 C CNN
	1    1400 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6082E3CB
P 1400 2150
F 0 "C?" H 1492 2196 50  0000 L CNN
F 1 "1uf" H 1492 2105 50  0000 L CNN
F 2 "" H 1400 2150 50  0001 C CNN
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
L Switch:SW_Push SW?
U 1 1 60827F4F
P 6300 4650
F 0 "SW?" H 6300 4950 50  0000 C CNN
F 1 "TL3302AF260QG" H 6300 4934 50  0001 C CNN
F 2 "" H 6300 4850 50  0001 C CNN
F 3 "~" H 6300 4850 50  0001 C CNN
F 4 "EG4584CT-ND" H 6300 4844 50  0000 C CNN "digikey"
	1    6300 4650
	1    0    0    -1  
$EndComp
Text GLabel 6600 4650 2    50   Input ~ 0
NRST
Text GLabel 7250 3000 0    50   Input ~ 0
NRST
Text GLabel 3150 2800 2    50   Input ~ 0
NRST
Wire Wire Line
	7250 3000 7400 3000
Text GLabel 2450 1300 0    50   Input ~ 0
3v3
Wire Wire Line
	2450 1300 2500 1300
Wire Wire Line
	2500 1300 2500 1400
Wire Wire Line
	3500 3950 3450 3950
Wire Wire Line
	1300 4050 1250 4050
Wire Wire Line
	4200 3950 4250 3950
Wire Wire Line
	4200 4400 4250 4400
Wire Wire Line
	4200 4850 4250 4850
$Comp
L power:GND #PWR?
U 1 1 60844B9E
P 2500 3200
F 0 "#PWR?" H 2500 2950 50  0001 C CNN
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
L Device:R R?
U 1 1 60849F57
P 3950 2700
F 0 "R?" V 4050 2700 50  0000 C CNN
F 1 "4.7k" V 3950 2700 50  0000 C CNN
F 2 "" V 3880 2700 50  0001 C CNN
F 3 "~" H 3950 2700 50  0001 C CNN
	1    3950 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 608498CA
P 3650 2700
F 0 "R?" V 3750 2700 50  0000 C CNN
F 1 "4.7k" V 3650 2700 50  0000 C CNN
F 2 "" V 3580 2700 50  0001 C CNN
F 3 "~" H 3650 2700 50  0001 C CNN
	1    3650 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 608515E3
P 3300 2050
F 0 "R?" V 3350 2200 50  0000 C CNN
F 1 "4.7k" V 3300 2050 50  0000 C CNN
F 2 "" V 3230 2050 50  0001 C CNN
F 3 "~" H 3300 2050 50  0001 C CNN
	1    3300 2050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60851930
P 3300 1900
F 0 "C?" V 3250 1800 50  0000 C CNN
F 1 "4.7uf" V 3250 2050 50  0000 C CNN
F 2 "" H 3300 1900 50  0001 C CNN
F 3 "~" H 3300 1900 50  0001 C CNN
	1    3300 1900
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60851F1A
P 3300 1750
F 0 "C?" V 3250 1650 50  0000 C CNN
F 1 "2.2uf" V 3250 1900 50  0000 C CNN
F 2 "" H 3300 1750 50  0001 C CNN
F 3 "~" H 3300 1750 50  0001 C CNN
	1    3300 1750
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60852DD5
P 3700 2150
F 0 "#PWR?" H 3700 1900 50  0001 C CNN
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
L Device:C_Small C?
U 1 1 6085DCB0
P 1850 2900
F 0 "C?" H 1900 3000 50  0000 L CNN
F 1 "1uf" H 1900 2800 50  0000 L CNN
F 2 "" H 1850 2900 50  0001 C CNN
F 3 "~" H 1850 2900 50  0001 C CNN
	1    1850 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6085E004
P 1650 3200
F 0 "#PWR?" H 1650 2950 50  0001 C CNN
F 1 "GND" H 1655 3027 50  0000 C CNN
F 2 "" H 1650 3200 50  0001 C CNN
F 3 "" H 1650 3200 50  0001 C CNN
	1    1650 3200
	1    0    0    -1  
$EndComp
Text GLabel 1450 2550 0    50   Input ~ 0
3v3
$Comp
L Device:C_Small C?
U 1 1 608634F0
P 1500 2900
F 0 "C?" H 1550 3000 50  0000 L CNN
F 1 "1uf" H 1550 2800 50  0000 L CNN
F 2 "" H 1500 2900 50  0001 C CNN
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
	1850 3000 1850 3150
Wire Wire Line
	1650 3150 1850 3150
Wire Wire Line
	1850 2800 1850 2700
Wire Wire Line
	1850 2700 2000 2700
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 608162A6
P 5250 1650
F 0 "J?" H 5330 1642 50  0000 L CNN
F 1 "DEBUG HEADER" H 5330 1551 50  0000 L CNN
F 2 "" H 5250 1650 50  0001 C CNN
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
L Device:C_Small C?
U 1 1 608B409C
P 7100 3550
F 0 "C?" H 7192 3596 50  0000 L CNN
F 1 "1uf" H 7192 3505 50  0000 L CNN
F 2 "" H 7100 3550 50  0001 C CNN
F 3 "~" H 7100 3550 50  0001 C CNN
	1    7100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3400 7100 3400
$Comp
L power:GND #PWR?
U 1 1 608B7854
P 7100 3750
F 0 "#PWR?" H 7100 3500 50  0001 C CNN
F 1 "GND" H 7105 3577 50  0000 C CNN
F 2 "" H 7100 3750 50  0001 C CNN
F 3 "" H 7100 3750 50  0001 C CNN
	1    7100 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3750 7100 3650
Wire Wire Line
	7100 3450 7100 3400
Wire Wire Line
	8100 3750 8100 3700
$EndSCHEMATC
