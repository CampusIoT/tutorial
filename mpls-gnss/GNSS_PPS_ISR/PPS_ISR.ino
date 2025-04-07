
#define PPS_PIN     13 // INT_1
//#define PPS_LED   12

void setup () {
  Serial.begin(115200);
  
  pinMode(PPS_PIN, INPUT);

#ifdef PPS_LED
  pinMode(PPS_LED, OUTPUT);
  // Check to make sure LED is working
  digitalWrite(PPS_LED, HIGH);
  delay(1000);
  digitalWrite(PPS_LED, LOW);
#endif

  Serial.println(__DATE__);
  Serial.println(__TIME__);
  
  // Attach an interrupt to interrupt #1, calls program "pps_interrupt", happens on rising (low to high)
  attachInterrupt(1, pps_interrupt, RISING);
}

void loop () {  
  delay(10000);
}

static int cpt = 0;

void pps_interrupt(){
  Serial.print(".");
  if(cpt++ % 50 == 0) {
    Serial.println();
  }
#ifdef PPS_LED
  digitalWrite(PPS_LED, HIGH);
  delay(100);
  digitalWrite(PPS_LED, LOW);
#endif
}
