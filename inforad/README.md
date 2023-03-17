# INFORAD K0 and K1 GNSS USB Stick

![Inforad K1](images/inforad-k1.jpg)

## Spec
```
Récepteur GPS: SiRFStar III , 20 canaux
Temps d’acquisition moyen*: Initialisation: 3 min, 38 secondes à froid et 8 secondes à chaud
Temps de réactualisation: 1 seconde
Précision: position 10 mètres RMS - vitesse < à 1km/h
Processeur: RISC 32 bits ARM7 at 49MHz
Mémoire: Processeur 128Kb - Vive 8Mb
Alarme: Sonore
Alimentation: 5 Vdc par adaptateur allume-cigare
Entrée: 12/24 Vdc, Sortie: 5 Vdc - 850mA max.
Dimensions: Longueur: 75 mm - Largeur: 25 mm - Hauteur: 10 mm
Poids du produit complet: 20 g.
```

## Get NMEA 0183 sentences

Baudrate is 4800.

```bash
tio -b 4800 -m INLCRNL /dev/tty.usbserial-140 
```

## GPSd @ Raspberry Pi

https://gpsd.gitlab.io/gpsd/installation.html

## GNSS Utilities

```bash
cgps -s
```

```
┌───────────────────────────────────────────┐┌──────────────────Seen 46/Used 12┐
│ Time:    	2022-09-24T17:11:45.000Z (0) ││GNSS   PRN  Elev   Azim   SNR Use│
│ Latitude:     	45.18217183 N       	││SB123   36  59.0   58.0  31.0  Y │
│ Longitude:     	5.73570767 E       	││SB132   45  62.0  222.0  31.0  Y │
│ Alt (HAE, MSL):	281.700,	234.300 m  ││GL  1   65  66.0  137.0  44.0  Y │
│ Speed:         	0.09 km/h          	││GL  12  65  66.0  137.0  36.0  Y │
│ Track (true, var):            	n/a deg ││GL  2   66  50.0  324.0  33.0  Y │
│ Climb:         	6.00 m/min         	││GL  22  66  50.0  324.0  23.0  Y │
│ Status:     	3D DGPS FIX (42 secs) 	││GL  8   72  15.0  139.0  24.0  Y │
│ Long Err  (XDOP, EPX):  0.83, +/-  3.1 m  ││GL  82  72  15.0  139.0  31.0  Y │
│ Lat Err   (YDOP, EPY):  0.75, +/-  2.8 m  ││GL 11   75  65.0   37.0  30.0  Y │
│ Alt Err   (VDOP, EPV):  1.22, +/-  7.0 m  ││GL 112  75  65.0   37.0  22.0  Y │
│ 2D Err	(HDOP, CEP):  0.81, +/-  3.8 m  ││GL 12   76  53.0  217.0  31.0  Y │
│ 3D Err	(PDOP, SEP):  1.46, +/-  6.9 m  ││GL 122  76  53.0  217.0  21.0  Y │
│ Time Err  (TDOP):   	1.34          	││GP  7	7  10.0   65.0   0.0  N │
│ Geo Err   (GDOP):   	2.40          	││GP  8	8   4.0   27.0   0.0  N │
│ ECEF X, VX:          	n/a	n/a   	││GP 17   17   3.0  122.0   0.0  N │
│ ECEF Y, VY:          	n/a	n/a   	││GP 23   23   4.0  327.0   0.0  N │
│ ECEF Z, VZ:          	n/a	n/a   	││SB121   34   7.0  322.0  16.0  N │
│ Speed Err (EPS):   	+/- 22.5 km/h  	││SB128   41   0.0   99.0   0.0  N │
│ Track Err (EPD):    	n/a           	││GL  3   67   1.0  320.0   0.0  N │
│ Time offset:        	0.518489770 s 	││GL 10   74  10.0   38.0   0.0  N │
│ Grid Square:        	JN25ue83      	││GL 13   77   5.0  218.0  28.0  N │
└───────────────────────────────────────────┘└More...──────────────────────────┘
```


```bash
gpsmon
```

```
tcp://127.0.0.1:5015      	NMEA0183>
┌──────────────────────────────────────────────────────────────────────────────┐or":14}
│Time: 2022-09-24T17:14:14.000Z   Lat: 45 10.931670' N   Lon:   5 44.138770' E │15","driver":"NMEA0183","activated":"2022-09-24T17:14:03.518Z","flags":1}]}
└───────────────────────────────── Cooked TPV ─────────────────────────────────┘false,"timing":false,"split24":false,"pps":true}
┌──────────────────────────────────────────────────────────────────────────────┐
│ GNRMC GNVTG GNGGA GNGSA GPGSV GLGSV GAGSV GBGSV GNGLL                    	│
└───────────────────────────────── Sentences ──────────────────────────────────┘
┌───────────────────────┌─────────────────────────┌────────────────────────────┐
│ SVID  PRN  Az El SN HU│Time: 	171414.00  	│Time:  	171414.00    	│
│SB123   36  57 57 26  Y│Latitude:   4510.93167 N │Latitude:  4510.93167   	│
│SB132   45 223 63 36  Y│Longitude: 00544.13877 E │Longitude: 00544.13877  	│
│GL  1   65 139 65 48  Y│Speed:	0.032      	│Altitude:  236.6        	│
│GL  12  65 139 65 35  Y│Course:              	│Quality:   2   Sats: 12 	│
│GL  2   66 324 51 31  Y│Status:   A    	FAA:D │HDOP:  	0.82         	│
│GL  22  66 324 51 25  Y│MagVar:              	│Geoid: 	47.4         	│
│GL  8   72 139 14 38  Y└───────── RMC ───────────└─────────── GGA ────────────┘
│GL  82  72 139 14 29  Y┌─────────────────────────┌────────────────────────────┐
│GL 11   75  37 64 25  Y│Mode: A3 Sats: 36 45 65 +│UTC:       	RMS:     	│
│GL 112  75  37 64 26  Y│DOP H=0.82 V=1.31 P=1.55 │MAJ:       	MIN:     	│
│GL 12   76 218 54 37  Y│TOFF:  0.093964033   	│ORI:       	LAT:     	│
│GL 122  76 218 54 30  Y│PPS: N/A             	│LON:       	ALT:     	│
└───v──── GSV ──────────└────── GSA + PPS ────────└─────────── GST ────────────┘
(72) $GPGSV,3,1,10,05,52,225,27,13,76,333,33,14,57,092,42,15,45,302,32,1*6A
(67) $GPGSV,3,2,10,20,23,188,38,28,,,44,30,41,062,28,36,32,146,47,1*5B
(46) $GPGSV,3,3,10,40,19,121,36,49,38,181,44,1*60
```

### PyGPSClient

```bash
python3 -m pip install --upgrade PyGPSClient
pygpsclient
```

Remarque: vous pouvez vous connecter à distance (TCP/UDP) sur le RPI au port 5015
