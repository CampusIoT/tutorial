# Sipeed Maix Bit

La carte Sipeed Maix Bit est une carte de développement dotée d'un processeur double coeur RISC-V. Elle est dotée d'une camera et d'un écran TFT 320*240 points, ainsi qu'un lecteur de SDCard.
Elle se programme en MicroPython.

![maix_bit](maix_bit.png)
![maix_bit](sipeed_maix_bit.jpg)
![maix_bit Pin](maixbit_pin_maps.svg)

## Mise à jour du firmware

Téléchargez la dernière version du [firmware](http://dl.sipeed.com/shareURL/MAIX/MaixPy/release/master) en choisissant celle qui conviendra à vos futurs usages. Les différentes versions sont décrites dans le fichier `readme.txt`.

TODO https://github.com/sipeed/MaixPy/blob/master/build.md#flash-burn-to-board

## Démarrage

Installez picocom ou minicom
```bash
brew install picocom
brew install minicom
```


Connectez vous à la console UART (le baud rate est `115200,8,N,1`):

```bash
minicom -D /dev/tty.usbserial-1420
```

Appuyez sur le bouton `Reset`.

```console
 __  __              _____  __   __  _____   __     __
|  \/  |     /\     |_   _| \ \ / / |  __ \  \ \   / /
| \  / |    /  \      | |    \ V /  | |__) |  \ \_/ /
| |\/| |   / /\ \     | |     > <   |  ___/    \   /
| |  | |  / ____ \   _| |_   / . \  | |         | |
|_|  |_| /_/    \_\ |_____| /_/ \_\ |_|         |_|

Official Site : https://www.sipeed.com
Wiki          : https://maixpy.sipeed.com

MicroPython v0.1.1-96-g71e5beaa7-dirty on 2019-03-08; Sipeed_M1 with kendryte-k210
Type "help()" for more information.
>>> help()
Welcome to MicroPython on the Sipeed Maix!

For generic online docs please visit https://maixpy.sipeed.com

Official website : http://www.sipeed.com


Control commands:
  CTRL-A        -- on a blank line, enter raw REPL mode                         
  CTRL-B        -- on a blank line, enter normal REPL mode                      
  CTRL-C        -- interrupt a running program                                  
  CTRL-D        -- on a blank line, do a soft reset of the board                
  CTRL-E        -- on a blank line, enter paste mode                            
                                                                                
For further help on a specific object, type help(obj)                           
For a list of available modules, type help('modules')                           
>>> help('modules')                                                             
KPU               errno             pye_mp            uio                       
Maix              fpioa_manager     random            ujson                     
__main__          gc                re                uos                       
_boot             hashlib           sensor            urandom                   
_thread           heapq             socket            ure                       
_webrepl          image             struct            usocket                   
array             json              sys               ustruct                   
audio             lcd               time              utime                     
binascii          machine           ubinascii         utimeq                    
board             math              ucollections      uzlib                     
builtins          math              ucryptolib        video                     
clock             micropython       uctypes           websocket                 
cmath             nes               uerrno            zlib                      
collections       network           uhashlib                                    
cpufreq           os                uheapq                                      
Plus any modules on the filesystem                                              
>>> import os
>>> os.listdir()
['labels.txt', 'detect.py']
```


## Informations système

Vérifiez la version du firmware à la console avec

```python
import sys
print("implementation:", sys.implementation)
print("platform:", sys.platform)
print("path:", sys.path)
print("Python version:", sys.version)
```

Affichez la version du firmware sur l'écran LCD avec

```python
try:
    import gc, lcd, image
    gc.collect()
    lcd.init()
    loading = image.Image(size=(lcd.width(), lcd.height()))
    loading.draw_rectangle((0, 0, lcd.width(), lcd.height()), fill=True, color=(255, 0, 0))
    info = "Welcome to MaixPy"
    loading.draw_string(int(lcd.width()//2 - len(info) * 5), (lcd.height())//4, info, color=(255, 255, 255), scale=2, mono_space=0)
    v = sys.implementation.version
    vers = 'V{}.{}.{} : maixpy.sipeed.com'.format(v[0],v[1],v[2])
    loading.draw_string(int(lcd.width()//2 - len(info) * 6), (lcd.height())//3 + 20, vers, color=(255, 255, 255), scale=1, mono_space=1)
    lcd.display(loading)
    del loading, v, info, vers
    gc.collect()
finally:
    gc.collect()
```

## Autres exemples

Testez les exemples disponibles dans les différents répertoires du [dépôt de scripts MicroPython](https://github.com/sipeed/MaixPy_scripts#directory-structure).

| directory | description |
| --------- | ----------- |
| application   | Some complex applications |
| basic         | basic micropython usage |
| board         | run python code, config your sipeed hardware |
| hardware      | hardware API usage demo |
| machine_vision | demo for vision related, including machine vision and AI processing related |
| modules       | external modules |
| multimedia    | normal multimedia processing, audio video game etc. |
| network       | network related |

En mode REPL, enfoncez ctrl-E pour copier-coller du code et terminez par ctrl-D pour exécuter le code collé.

Sinon, chargez les scripts en utilisant TODO


### Scanner I2C

```python
from machine import I2C # Import built-in library

i2c = I2C(I2C.I2C0, freq=100000, scl=28, sda=29) # Define an I2C object, use I2C0, frequency 100kHz, SCL pin is IO28, SDA pin is IO29
devices = i2c.scan() # call function to scan device
print(devices) # print device
```


### Capture d'images et affichage sur l'écran LCD

```python
import sensor
import image
import lcd

lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)
while True:
    img=sensor.snapshot()
    lcd.display(img)
```


### Détection d'object (avec Mobilenet)

Chargez le modèle Mobilenet sur la carte SD depuis [le dépôt](http://dl.sipeed.com/shareURL/MAIX/MaixPy/model).

Insérez la carte SD dans le lecteur.

Exécutez le programme suivant:

```python
import KPU as kpu
import sensor

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_windowing((224, 224))

model = kpu.load("/sd/mobilenet.kmodel") # load model
while(True):
    img = sensor.snapshot() # take picture by camera
    out = kpu.forward(task, img)[:] # inference, get one-hot output
    print(max(out)) # print max probability object ID
```

[Plus d'info](https://lemariva.com/blog/2020/01/maixpy-object-detector-mobilenet-and-yolov2-sipeed-maix-dock)


## Récupération de modèles entrainés

Créez un compte sur https://www.maixhub.com/modelInfo?modelId=11 ou https://www.maixhub.com/modelInfo?modelId=14

Récupérez l'application pour flasher le firmware de la carte.

Flashez le firmware https://dl.sipeed.com/fileList/MaixHub_Tools/key_gen_v1.2.bin avec l'application.

Connectez vous à la console UART et appuyez sur le bouton reset.

```
Please Send Bellow Data to Sipeed --> support@sipeed.com:
da24f8b24c57d2386b0a4f950b479d00
Generate key end
```

Recopiez et conservez la clé générée pour votre carte.

Récuperez les 3 fichiers du modèle souhaité (par exemple [1000_class_object_classification_model](https://www.maixhub.com/modelInfo?modelId=11)) au moyen de la clé qui vous est demandé pour le téléchargement.

Flashez le modele récupéré dans le fichier *.smodel avec l'application kflash_gui à l'adresse `0x500000`

Récupérez le firmware `maixpy_v*_minimum_with_kmodel_v4_support.bin` dans le [dépot](http://dl.sipeed.com/shareURL/MAIX/MaixPy/release/master).

Flashez ce firmware avec l'application kflash_gui à l'adresse `0x000000`.

Copiez dans la SDCard les fichiers labels.txt et main.py


```python
import os
os.listdir()

fileToRead = open("labels.txt")	
content = fileToRead.read()
print(content)
fileToRead.close()

fileToRead = open("detect.py")	
content = fileToRead.read()
print(content)
fileToRead.close()
```

L'errreur est la suivante
```
ValueError: [MAIXPY]kpu: load error:2002, ERR_KMODEL_VERSION: only support kmodel V3/V4 now
```

Meme probleme avec https://github.com/sipeed/MaixPy_scripts/blob/master/application/capture_image_tool/boot.py



## Personnalisation du démarrage

Start up scripts
    boot.py: runs when the device starts and sets up several configuration options;
    main.py: this is the main script that contains your code. It is executed immediately after the boot.py.


## Autres
* [Gimbal](https://github.com/sipeed/MaixPy_scripts/tree/master/application/gimbal)


## Misc

* [3mm PMMA Enclosure](./sipeed_maix_bit_enclosure.svg) by Germain Lemasson, FabMSTIC

## Références

* [MaixPy firmware](http://dl.sipeed.com/shareURL/MAIX/MaixPy/release/master)
* [Models](http://dl.sipeed.com/shareURL/MAIX/MaixPy/model)
* [Maix Train](https://github.com/sipeed/maix_train)
* [Sipeed Maix Bit](https://wiki.sipeed.com/soft/maixpy/en/develop_kit_board/maix_bit.html)
* [maixpy](https://wiki.sipeed.com/soft/maixpy/en/)
* [Scripts d'exemple](https://github.com/sipeed/maixpy_scripts)
* [Projet de reconnaissance d'images](https://github.com/Th3CracKed/M2M_Image_Recognition)
* [See Doc Section](https://www.seeedstudio.com/Sipeed-MAix-BiT-for-RISC-V-AI-IoT-1-p-2873.html)
