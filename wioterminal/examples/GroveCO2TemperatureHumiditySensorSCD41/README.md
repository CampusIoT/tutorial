# Wio Terminal et Grove CO2 & Temperature & Humidity Sensor SCD41

La platine [Grove CO2 & Temperature & Humidity Sensor SCD41](https://wiki.seeedstudio.com/Grove-CO2_%26_Temperature_%26_Humidity_Sensor-SCD41/) comporte un des derniers modèles de capteurs CO2 Sensirion SCD4x

Suivez les instructions pour l'installation des bibliothèques (https://github.com/Sensirion/arduino-i2c-scd4x).

Chargez l'exemple de test sur le Wio Terminal.

Voici un petit test effectué dans une pièce non ventilée un soir.

```
22:48:00.100 -> Serial: 0x27F7BF073B58
22:40:00.103 -> Waiting for first measurement... (5 sec)
...
22:49:04.703 -> Co2:2590	Temperature:26.30	Humidity:44.97
22:49:09.705 -> Co2:2613	Temperature:26.31	Humidity:45.23
22:49:14.680 -> Co2:2679	Temperature:26.15	Humidity:45.59
22:49:19.694 -> Co2:2762	Temperature:25.93	Humidity:45.95
```

Quelques heures plus tard (la nuit passée).

```
07:17:44.486 -> Co2:1045	Temperature:17.80	Humidity:43.51
07:17:49.487 -> Co2:993	Temperature:17.80	Humidity:43.82
07:17:54.486 -> Co2:1002	Temperature:17.71	Humidity:44.14
```

Ouverture de la fenêtre pour aérer.

```
07:17:59.501 -> Co2:984	Temperature:17.57	Humidity:44.40
07:18:04.494 -> Co2:947	Temperature:17.40	Humidity:44.67
07:18:09.515 -> Co2:921	Temperature:17.26	Humidity:44.90
07:18:14.525 -> Co2:919	Temperature:17.12	Humidity:45.21
07:18:19.551 -> Co2:925	Temperature:17.04	Humidity:45.79
07:18:24.548 -> Co2:928	Temperature:16.93	Humidity:46.07
07:18:29.554 -> Co2:928	Temperature:16.82	Humidity:46.48
07:18:34.549 -> Co2:932	Temperature:16.72	Humidity:46.80
07:18:39.564 -> Co2:934	Temperature:16.62	Humidity:47.07
07:18:44.580 -> Co2:934	Temperature:16.52	Humidity:47.30
07:18:49.572 -> Co2:934	Temperature:16.43	Humidity:47.37
07:18:54.593 -> Co2:934	Temperature:16.34	Humidity:47.32
07:18:59.587 -> Co2:936	Temperature:16.27	Humidity:47.31
07:19:04.605 -> Co2:938	Temperature:16.24	Humidity:47.52
07:19:09.622 -> Co2:939	Temperature:16.19	Humidity:47.69
07:19:14.608 -> Co2:947	Temperature:16.15	Humidity:48.01
07:19:19.609 -> Co2:966	Temperature:16.07	Humidity:48.45
07:19:24.630 -> Co2:969	Temperature:16.02	Humidity:48.44
07:19:29.639 -> Co2:970	Temperature:15.98	Humidity:48.22
07:19:34.657 -> Co2:969	Temperature:15.96	Humidity:48.04
07:19:39.662 -> Co2:965	Temperature:15.93	Humidity:47.94
07:19:44.661 -> Co2:960	Temperature:15.94	Humidity:47.94
07:19:49.653 -> Co2:950	Temperature:15.93	Humidity:47.86
07:19:54.658 -> Co2:948	Temperature:15.93	Humidity:47.91
07:19:59.667 -> Co2:949	Temperature:15.91	Humidity:47.98
07:20:04.695 -> Co2:949	Temperature:15.90	Humidity:48.10
07:20:09.685 -> Co2:946	Temperature:15.90	Humidity:47.92
07:20:14.686 -> Co2:936	Temperature:15.89	Humidity:47.71
07:20:19.696 -> Co2:926	Temperature:15.87	Humidity:47.53
07:20:24.696 -> Co2:922	Temperature:15.88	Humidity:47.35
07:20:29.730 -> Co2:898	Temperature:15.84	Humidity:47.16
07:20:34.734 -> Co2:885	Temperature:15.81	Humidity:47.00
07:20:39.744 -> Co2:866	Temperature:15.82	Humidity:46.78
07:20:44.741 -> Co2:861	Temperature:15.81	Humidity:46.65
07:20:49.731 -> Co2:858	Temperature:15.80	Humidity:46.80
07:20:54.745 -> Co2:860	Temperature:15.79	Humidity:47.03
07:20:59.757 -> Co2:861	Temperature:15.79	Humidity:47.06
07:21:04.765 -> Co2:861	Temperature:15.76	Humidity:46.81
07:21:09.767 -> Co2:860	Temperature:15.77	Humidity:46.57
07:21:14.784 -> Co2:861	Temperature:15.77	Humidity:46.38
07:21:19.794 -> Co2:860	Temperature:15.79	Humidity:46.44
07:21:24.796 -> Co2:860	Temperature:15.80	Humidity:46.62
07:21:29.813 -> Co2:860	Temperature:15.79	Humidity:46.62
07:21:34.797 -> Co2:860	Temperature:15.79	Humidity:46.41
07:21:39.814 -> Co2:859	Temperature:15.78	Humidity:46.22
07:21:44.804 -> Co2:854	Temperature:15.78	Humidity:46.08
07:21:49.809 -> Co2:851	Temperature:15.80	Humidity:45.91
07:21:54.849 -> Co2:839	Temperature:15.80	Humidity:45.72
07:21:59.832 -> Co2:832	Temperature:15.83	Humidity:45.50
07:22:04.843 -> Co2:817	Temperature:15.80	Humidity:45.53
```
## Affichage des valeurs sur l'écran LCD

TODO
