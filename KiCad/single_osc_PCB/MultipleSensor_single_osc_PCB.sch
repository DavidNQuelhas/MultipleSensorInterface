EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Multiple Sensor Interface - single sensor/oscillator PCB"
Date "2021-07-25"
Rev ""
Comp "David N. G. da Silva S. Quelhas (Lisboa - Portugal)  ,  License: CERN-OHL-W"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74HC14 U7
U 1 1 5FF7C116
P 3500 5250
F 0 "U7" H 3500 5567 50  0000 C CNN
F 1 "74HC14" H 3500 5476 50  0000 C CNN
F 2 "MultipleSensor_PCB:SOIC-14_3.9x8.7mm_Pitch1.27mm_HandSoldering" H 3500 5250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 3500 5250 50  0001 C CNN
	1    3500 5250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U7
U 2 1 5FF7D1D9
P 4600 5250
F 0 "U7" H 4600 5567 50  0000 C CNN
F 1 "74HC14" H 4600 5476 50  0000 C CNN
F 2 "MultipleSensor_PCB:SOIC-14_3.9x8.7mm_Pitch1.27mm_HandSoldering" H 4600 5250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 4600 5250 50  0001 C CNN
	2    4600 5250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5FFF7D59
P 6100 2400
F 0 "#PWR0102" H 6100 2250 50  0001 C CNN
F 1 "+5V" H 6115 2573 50  0000 C CNN
F 2 "" H 6100 2400 50  0001 C CNN
F 3 "" H 6100 2400 50  0001 C CNN
	1    6100 2400
	1    0    0    -1  
$EndComp
Text GLabel 6950 5250 2    50   UnSpc ~ 0
OSC0_OUT
$Comp
L MultipleSensor_PCB:1N4731 D3
U 1 1 60023DCC
P 3350 3450
F 0 "D3" H 3350 3559 50  0000 C CNN
F 1 "1N4731" H 3350 3350 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3300 3540 50  0001 C CNN
F 3 "" H 3300 3540 50  0001 C CNN
	1    3350 3450
	0    1    1    0   
$EndComp
$Comp
L Diode:1N5817 D1
U 1 1 6002BC18
P 6300 3500
F 0 "D1" H 6300 3599 50  0000 C CNN
F 1 "1N5817" H 6400 3400 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 6300 3325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 6300 3500 50  0001 C CNN
	1    6300 3500
	0    1    1    0   
$EndComp
$Comp
L Diode:1N5817 D2
U 1 1 6002F00F
P 6800 3500
F 0 "D2" H 6800 3599 50  0000 C CNN
F 1 "1N5817" H 6800 3390 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 6800 3325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 6800 3500 50  0001 C CNN
	1    6800 3500
	0    1    1    0   
$EndComp
$Comp
L Device:Polyfuse F1
U 1 1 5FFB7E68
P 7750 3950
F 0 "F1" V 7663 3950 50  0000 C CNN
F 1 "Polyfuse 100m A, 60V" V 7850 3800 50  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:Fuse_TE5_Littlefuse-395Series" H 7800 3750 50  0001 L CNN
F 3 "~" H 7750 3950 50  0001 C CNN
	1    7750 3950
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D10
U 1 1 5FFBED7C
P 4650 3300
F 0 "D10" H 4500 3350 50  0000 C CNN
F 1 "LED_SMD_1206" H 4750 3200 50  0000 C CNN
F 2 "LEDs:LED_1206" H 4650 3300 50  0001 C CNN
F 3 "~" H 4650 3300 50  0001 C CNN
	1    4650 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 5FFD6561
P 5650 3450
F 0 "C14" H 5700 3350 50  0000 L CNN
F 1 "100nF, SMD 0805" H 5500 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5688 3300 50  0001 C CNN
F 3 "~" H 5650 3450 50  0001 C CNN
	1    5650 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3150 7750 3150
$Comp
L power:GND #PWR0103
U 1 1 5FFDA580
P 3250 3850
F 0 "#PWR0103" H 3250 3600 50  0001 C CNN
F 1 "GND" H 3255 3677 50  0000 C CNN
F 2 "" H 3250 3850 50  0001 C CNN
F 3 "" H 3250 3850 50  0001 C CNN
	1    3250 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3750 3250 3850
Wire Wire Line
	6100 2400 6100 3150
Wire Wire Line
	7750 3800 7750 3150
Connection ~ 7750 3150
Wire Wire Line
	7750 3150 6800 3150
Wire Wire Line
	6300 3350 6300 3150
Connection ~ 6300 3150
Wire Wire Line
	6300 3150 6100 3150
Wire Wire Line
	6800 3350 6800 3150
Connection ~ 6800 3150
Wire Wire Line
	6800 3150 6300 3150
Wire Wire Line
	6800 3650 6800 3750
Wire Wire Line
	6800 3750 6300 3750
Wire Wire Line
	6300 3650 6300 3750
Connection ~ 6300 3750
$Comp
L Device:R R28
U 1 1 5FFF718E
P 3650 3150
F 0 "R28" V 3550 3200 50  0000 C CNN
F 1 "22, SMD2512" V 3700 3150 50  0000 C CNN
F 2 "Resistors_SMD:R_2512_HandSoldering" V 3580 3150 50  0001 C CNN
F 3 "~" H 3650 3150 50  0001 C CNN
	1    3650 3150
	0    -1   -1   0   
$EndComp
Text GLabel 2900 3150 0    50   UnSpc ~ 0
VDDS
Connection ~ 6100 3150
$Comp
L Device:CP1 C15
U 1 1 5FFCCF31
P 5200 3450
F 0 "C15" H 5200 3550 50  0000 L CNN
F 1 "100uF, 16V" H 5000 3300 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 5200 3450 50  0001 C CNN
F 3 "~" H 5200 3450 50  0001 C CNN
	1    5200 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3750 3350 3750
Wire Wire Line
	5650 3300 5650 3150
Connection ~ 5650 3150
Wire Wire Line
	5650 3150 6100 3150
Wire Wire Line
	5200 3300 5200 3150
Wire Wire Line
	5200 3150 5650 3150
Wire Wire Line
	5650 3600 5650 3750
Connection ~ 5650 3750
Wire Wire Line
	5650 3750 6300 3750
Wire Wire Line
	5200 3600 5200 3750
Connection ~ 5200 3750
Wire Wire Line
	5200 3750 5650 3750
Wire Wire Line
	5200 3150 4950 3150
Wire Wire Line
	4950 3150 4950 3300
Wire Wire Line
	4950 3300 4800 3300
Connection ~ 5200 3150
Wire Wire Line
	3850 3300 3850 3750
Connection ~ 3850 3750
Wire Wire Line
	3850 3750 5200 3750
Wire Wire Line
	3350 3300 3350 3150
Wire Wire Line
	3350 3150 2900 3150
Wire Wire Line
	3350 3600 3350 3750
Connection ~ 3350 3750
Wire Wire Line
	3350 3750 3850 3750
$Comp
L Device:R R1
U 1 1 5FFE7482
P 3400 5850
F 0 "R1" V 3300 5850 50  0000 C CNN
F 1 "2M, SMD0805" V 3500 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3330 5850 50  0001 C CNN
F 3 "~" H 3400 5850 50  0001 C CNN
	1    3400 5850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C1
U 1 1 5FFE89D1
P 2900 6300
F 0 "C1" H 2950 6200 50  0000 L CNN
F 1 "2.2nF, SMD0805" V 2750 6150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2938 6150 50  0001 C CNN
F 3 "~" H 2900 6300 50  0001 C CNN
	1    2900 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5FFEA0E6
P 4100 6300
F 0 "C2" H 4000 6200 50  0000 L CNN
F 1 "2.2nF, SMD0805" V 4250 6150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4138 6150 50  0001 C CNN
F 3 "~" H 4100 6300 50  0001 C CNN
	1    4100 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5FFEB50D
P 4100 7100
F 0 "C4" H 3950 7000 50  0000 L CNN
F 1 "22pF, SMD0805" V 4250 6850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4138 6950 50  0001 C CNN
F 3 "~" H 4100 7100 50  0001 C CNN
	1    4100 7100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5FFEC63F
P 4100 5700
F 0 "R2" V 4000 5700 50  0000 C CNN
F 1 "500, SMD0805" V 4200 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4030 5700 50  0001 C CNN
F 3 "~" H 4100 5700 50  0001 C CNN
	1    4100 5700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 6005479D
P 3500 7450
F 0 "#PWR0108" H 3500 7200 50  0001 C CNN
F 1 "GND" H 3505 7277 50  0000 C CNN
F 2 "" H 3500 7450 50  0001 C CNN
F 3 "" H 3500 7450 50  0001 C CNN
	1    3500 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 7350 3500 7450
Wire Wire Line
	4100 7250 4100 7350
Connection ~ 3500 7350
$Comp
L MultipleSensor_PCB:2_jumpers_related JP0
U 1 1 600C4757
P 3500 6900
F 0 "JP0" V 3500 6669 50  0000 R CNN
F 1 "2_jumpers_related" H 3540 6650 50  0001 C CNN
F 2 "MultipleSensor_PCB:2_jumpers_related_2.54mm" H 3300 7200 50  0001 C CNN
F 3 "" H 3300 7200 50  0001 C CNN
	1    3500 6900
	0    -1   1    0   
$EndComp
Wire Wire Line
	2900 7350 3200 7350
Wire Wire Line
	3500 7350 4100 7350
Wire Wire Line
	4100 6450 4100 6600
Wire Wire Line
	2900 6450 2900 6600
Wire Wire Line
	3400 6600 2900 6600
Wire Wire Line
	3600 6600 4100 6600
Connection ~ 4100 6600
Wire Wire Line
	4100 6600 4100 6950
Wire Wire Line
	3600 7200 3400 7200
Wire Wire Line
	3400 7200 3200 7200
Wire Wire Line
	3200 7200 3200 7350
Connection ~ 3400 7200
Connection ~ 3200 7350
Wire Wire Line
	3200 7350 3500 7350
Wire Wire Line
	3200 5250 2900 5250
Wire Wire Line
	2900 5250 2900 5850
Wire Wire Line
	3250 5850 2900 5850
Connection ~ 2900 5850
Wire Wire Line
	2900 5850 2900 6050
Wire Wire Line
	3800 5250 4100 5250
Wire Wire Line
	4100 6150 4100 6050
Wire Wire Line
	4100 5550 4100 5450
Connection ~ 4100 5250
Wire Wire Line
	4100 5250 4300 5250
Wire Wire Line
	3550 5850 3750 5850
Wire Wire Line
	3750 5850 3750 5450
Wire Wire Line
	3750 5450 4100 5450
Connection ~ 4100 5450
Wire Wire Line
	4100 5450 4100 5250
Text GLabel 2550 6050 0    50   UnSpc ~ 0
S0_IN1
Text GLabel 4550 6050 2    50   UnSpc ~ 0
S0_IN2
Wire Wire Line
	2550 6050 2900 6050
Connection ~ 2900 6050
Wire Wire Line
	2900 6050 2900 6150
Wire Wire Line
	4550 6050 4100 6050
Connection ~ 4100 6050
Wire Wire Line
	4100 6050 4100 5850
$Comp
L 74xx:74HC14 U7
U 7 1 603670D1
P 1550 6300
F 0 "U7" H 1650 6650 50  0000 C CNN
F 1 "74HC14" H 1550 6300 50  0000 C CNN
F 2 "MultipleSensor_PCB:SOIC-14_3.9x8.7mm_Pitch1.27mm_HandSoldering" H 1550 6300 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 1550 6300 50  0001 C CNN
	7    1550 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 602C52DD
P 1200 7000
F 0 "#PWR0115" H 1200 6750 50  0001 C CNN
F 1 "GND" H 1205 6827 50  0000 C CNN
F 2 "" H 1200 7000 50  0001 C CNN
F 3 "" H 1200 7000 50  0001 C CNN
	1    1200 7000
	1    0    0    -1  
$EndComp
Text GLabel 1100 5500 0    50   UnSpc ~ 0
VDDS
Wire Wire Line
	1200 6900 1200 7000
Wire Wire Line
	1550 6800 1550 6900
Wire Wire Line
	1550 6900 1200 6900
Wire Wire Line
	1550 5800 1550 5750
Wire Wire Line
	1550 5500 1100 5500
Connection ~ 2900 6600
Wire Wire Line
	2900 6600 2900 6950
Wire Wire Line
	2900 7250 2900 7350
$Comp
L Device:C C3
U 1 1 5FFEA570
P 2900 7100
F 0 "C3" H 2950 7000 50  0000 L CNN
F 1 "22pF, SMD0805" V 2750 6850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2938 6950 50  0001 C CNN
F 3 "~" H 2900 7100 50  0001 C CNN
	1    2900 7100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 604285DB
P 1900 6250
F 0 "C12" H 1950 6150 50  0000 L CNN
F 1 "100nF, SMD0805" V 1850 5950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1938 6100 50  0001 C CNN
F 3 "~" H 1900 6250 50  0001 C CNN
	1    1900 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 6400 1900 6900
Wire Wire Line
	1900 6900 1550 6900
Connection ~ 1550 6900
Wire Wire Line
	1900 6100 1900 5750
Wire Wire Line
	1900 5750 1550 5750
Connection ~ 1550 5750
Wire Wire Line
	3500 3150 3350 3150
Connection ~ 3350 3150
Connection ~ 4950 3150
Wire Wire Line
	3800 3150 4950 3150
$Comp
L Device:R R13
U 1 1 5FFC73B1
P 4150 3300
F 0 "R13" V 4228 3350 50  0000 C CNN
F 1 "220, SMD0805" V 4100 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4080 3300 50  0001 C CNN
F 3 "~" H 4150 3300 50  0001 C CNN
	1    4150 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 3300 4500 3300
Wire Wire Line
	4000 3300 3850 3300
$Comp
L 74xx:74HC14 U7
U 3 1 60211902
P 5450 5250
F 0 "U7" H 5450 5567 50  0000 C CNN
F 1 "74HC14" H 5450 5476 50  0000 C CNN
F 2 "MultipleSensor_PCB:SOIC-14_3.9x8.7mm_Pitch1.27mm_HandSoldering" H 5450 5250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 5450 5250 50  0001 C CNN
	3    5450 5250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U7
U 4 1 602132C9
P 6350 5250
F 0 "U7" H 6350 5567 50  0000 C CNN
F 1 "74HC14" H 6350 5476 50  0000 C CNN
F 2 "MultipleSensor_PCB:SOIC-14_3.9x8.7mm_Pitch1.27mm_HandSoldering" H 6350 5250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6350 5250 50  0001 C CNN
	4    6350 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5250 5150 5250
Wire Wire Line
	5750 5250 6050 5250
Wire Wire Line
	6650 5250 6950 5250
Wire Wire Line
	1550 5500 1550 5750
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 60FB2463
P 650 4350
F 0 "J1" H 568 4025 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 400 4150 50  0000 C CNN
F 2 "MultipleSensor_PCB:TerminalBlock_Screw_1x2_3.96mm" H 650 4350 50  0001 C CNN
F 3 "~" H 650 4350 50  0001 C CNN
	1    650  4350
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J3
U 1 1 60FB33FF
P 10600 4450
F 0 "J3" H 10700 4500 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 10250 4250 50  0000 L CNN
F 2 "MultipleSensor_PCB:TerminalBlock_Screw_1x3_3.96mm" H 10600 4450 50  0001 C CNN
F 3 "~" H 10600 4450 50  0001 C CNN
	1    10600 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 60FB43A1
P 1550 4750
F 0 "J2" V 1422 4830 50  0000 L CNN
F 1 "Conn_01x02" V 1513 4830 50  0000 L CNN
F 2 "MultipleSensor_PCB:PinHeader_1x02_P2.54mm_Vertical_HandSoldering" H 1550 4750 50  0001 C CNN
F 3 "~" H 1550 4750 50  0001 C CNN
	1    1550 4750
	0    1    1    0   
$EndComp
Text GLabel 2000 4350 2    50   UnSpc ~ 0
S0_IN1
Wire Wire Line
	1550 4350 1550 4550
Wire Wire Line
	850  4350 1550 4350
Text GLabel 1900 4100 2    50   UnSpc ~ 0
S0_IN2
Wire Wire Line
	2000 4350 1550 4350
Connection ~ 1550 4350
Wire Wire Line
	1450 4550 1450 4250
Wire Wire Line
	1450 4250 850  4250
Wire Wire Line
	1900 4100 1450 4100
Wire Wire Line
	1450 4100 1450 4250
Connection ~ 1450 4250
Wire Wire Line
	10400 4350 8950 4350
Wire Wire Line
	7750 4350 7750 4100
Connection ~ 8950 4350
Wire Wire Line
	8950 4350 7750 4350
$Comp
L power:GND #PWR0101
U 1 1 60FE2E49
P 8400 4850
F 0 "#PWR0101" H 8400 4600 50  0001 C CNN
F 1 "GND" H 8405 4677 50  0000 C CNN
F 2 "" H 8400 4850 50  0001 C CNN
F 3 "" H 8400 4850 50  0001 C CNN
	1    8400 4850
	1    0    0    -1  
$EndComp
Text GLabel 9800 5000 3    50   UnSpc ~ 0
OSC0_OUT
Wire Wire Line
	10400 4550 9800 4550
Wire Wire Line
	8850 4450 10400 4450
Wire Wire Line
	8400 4850 8400 4450
Wire Wire Line
	8400 4450 8850 4450
Connection ~ 8850 4450
Wire Wire Line
	9800 5000 9800 4550
Connection ~ 9800 4550
Wire Wire Line
	9800 4550 8650 4550
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 60FCE019
P 8850 5500
F 0 "J4" V 8722 5680 50  0000 L CNN
F 1 "Conn_01x04" V 8813 5680 50  0000 L CNN
F 2 "MultipleSensor_PCB:PinHeader_1x04_P2.54mm_Vertical_HandSoldering" H 8850 5500 50  0001 C CNN
F 3 "~" H 8850 5500 50  0001 C CNN
	1    8850 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	8950 4350 8950 5300
Wire Wire Line
	8850 4450 8850 5050
Wire Wire Line
	8750 5300 8750 5050
Wire Wire Line
	8750 5050 8850 5050
Connection ~ 8850 5050
Wire Wire Line
	8850 5050 8850 5300
Wire Wire Line
	8650 4550 8650 5300
Text Notes 7000 6950 0    39   Italic 0
CERN Open Hardware Licence Version 2 - Weakly Reciprocal (CERN-OHL-W) , Preamble:\n- CERN has developed this licence to promote collaboration among hardware designers and to provide a legal tool which supports \nthe freedom to use, study, modify, share and distribute hardware designs and products based on those designs.\n- The CERN-OHL-W is copyright CERN 2020. Anyone is welcome to use it, in unmodified form only.\n- Use of this Licence does not imply any endorsement by CERN of any Licensor or their designs \nnor does it imply any involvement by CERN in their development.
$EndSCHEMATC
