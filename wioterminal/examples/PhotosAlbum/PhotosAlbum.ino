#include"TFT_eSPI.h"
#include "Seeed_FS.h" //Including SD card library
#include"RawImage.h"  //Including image processing library
TFT_eSPI tft;

#define ROOTDIR "/photos"
#define DELAY   2000

#define LOG Serial


#ifdef WIO_LITE_AI
#define DEV  SDMMC 
#else
#define DEV  SD
#ifdef _SAMD21_
#define SDCARD_SS_PIN 1
#define SDCARD_SPI SPI
#endif 
#endif

#include <stdbool.h>

bool strendwith(const char* str, const char* substr) {
    int lenOfStr = strlen(str);
    int lenOfSubstr = strlen(substr);
     
    bool endsWith = false;
    if (lenOfSubstr <= lenOfStr) {
        for (int i = 0; i < lenOfSubstr; i++) {
            if (str[i + lenOfStr - lenOfSubstr] != substr[i]) {
                endsWith = false;
                break;
            }
            endsWith = true;
        }
    }
    return endsWith;
}

bool strstartwith(const char *str, const char *prefix)
{
    return strncmp(prefix, str, strlen(prefix)) == 0;
}

void drawImages( fs::FS& fs, const char* dirname, int numTabs )
{
   File dir= fs.open(dirname);

   while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      dir.close();
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      LOG.print('\t');
    }
    char* name = entry.name();
    LOG.print(name);    
    if (entry.isDirectory()) {
      LOG.println("/");
      drawImages(fs,name, numTabs + 1);
    } else {
      // files have sizes, directories do not
      LOG.print("\t\t");
      LOG.print(entry.size(), DEC);
      LOG.print(" bytes");
      // MacOS adds files starting with ._
      if(strendwith(name,".bmp") && (strstr(name,"._")==NULL)) {
        drawImage<uint16_t>(name,0,0);
        delay(1000);         
      } else {
         LOG.print(" - not an image");
      }
      LOG.println("");
    }
    entry.close();
  }
}


void setupFS() {
  // Open LOG communications and wait for port to open:
  LOG.begin(115200);
  while (!LOG) {
    ; // wait for LOG port to connect. Needed for native USB port only
  }

  LOG.println("Initializing SD card...");

#ifdef WIO_LITE_AI
  if (!DEV.begin()) {
    LOG.println("initialization failed!");
  }
#else
  if (!DEV.begin(SDCARD_SS_PIN,SDCARD_SPI,4000000UL)) {
    LOG.println("initialization failed!");
  }    
#endif
  LOG.println("initialization done.");
}

void setupTFT() {
    tft.begin();
    tft.setRotation(3);
}
void setup() {
    setupFS();
    setupTFT();
}

void loop() {
  File root = DEV.open(ROOTDIR);
  drawImages(DEV,ROOTDIR,0);
  LOG.println("done!");
  root.close();
}
