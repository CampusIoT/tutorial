/*
    Listfiles

    This example shows how print out the files in a
    directory on a SD card

    The circuit:
    SD card attached to SPI bus or SDMMC


    created   Nov 2010
    by David A. Mellis
    modified 9 Apr 2012
    by Tom Igoe
    modified 2 Feb 2014
    by Scott Fitzgerald
    modified 18 July 2021
    by Hongtai.liu

    This example code is in the public domain.

*/
#include <Seeed_Arduino_FS.h>


#ifdef WIO_LITE_AI
#define DEV  SDMMC 
#else
#define DEV  SD
#ifdef _SAMD21_
#define SDCARD_SS_PIN 1
#define SDCARD_SPI SPI
#endif 
#endif


#define LOG Serial


void setup() {
  // Open LOG communications and wait for port to open:
  pinMode(LED_BUILTIN, OUTPUT);
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

  File root = DEV.open("/");
  printDirectory(root, 0);

  LOG.println("  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -");
  listDir(DEV,"/",0);

  LOG.println("done!");
  root.close();
}

void loop() {
  // nothing happens after setup finishes.
    digitalWrite(LED_BUILTIN, LOW);  
    delay(50);                    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);   
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      LOG.print('\t');
    }
    LOG.print(entry.name());
    if (entry.isDirectory()) {
      LOG.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      LOG.print("\t\t");
      LOG.print(entry.size(), DEC);
      LOG.println(" bytes");
    }
    entry.close();
  }
}

void listDir( fs::FS& fs, const char* dirname, int numTabs )
{
   File dir= fs.open(dirname);

   while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      LOG.print('\t');
    }
    LOG.print(entry.name());
    if (entry.isDirectory()) {
      LOG.println("/");
      listDir(fs,entry.name(), numTabs + 1);
    } else {
      // files have sizes, directories do not
      LOG.print("\t\t");
      LOG.print(entry.size(), DEC);
      LOG.println(" bytes");
    }
    entry.close();
  }
}
