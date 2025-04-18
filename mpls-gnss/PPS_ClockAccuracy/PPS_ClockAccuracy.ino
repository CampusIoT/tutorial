// Check processor clock accuracy against GPS
//
// Connect the GPS to the Uno via 5V, GND.
// Connect the PPS signal to the input capture pin D8.

#define PPS_INPUT_PIN         8	  // 328 pin 14 (DIP), pin 12 (TQFP) (input capture)

// Pin operation macros
#define INPUT_PORT(pin)       (pin < 8 ? PIND : (pin < 14 ? PINB : PINC))
#define OUTPUT_PORT(pin)      (pin < 8 ? PORTD : (pin < 14 ? PORTB : PORTC))
#define PIN_MASK(pin)         (pin < 8 ? 1<<pin : (pin < 14 ? 1<<pin-8 : 1<<pin-14))
#define SET_PIN(pin, level)   (level == LOW ? (OUTPUT_PORT(pin) &= ~PIN_MASK(pin)) : (OUTPUT_PORT(pin) |= PIN_MASK(pin)))

volatile uint16_t captureTicks = 0;
volatile uint16_t captureRolls = 0;
volatile uint16_t rollovers = 0;
volatile bool captureFlag = false;

uint32_t prevCaptureTime = 0;

// =======================================================================================
ISR (TIMER1_CAPT_vect)
{
  captureTicks = ICR1;
  captureRolls = rollovers;
  captureFlag = true;
}

ISR (TIMER1_OVF_vect)
{
  rollovers++;
}
// =========================================================================================

void setup()
{
  Serial.begin(115200);
  Serial.println("\nHello\n");
  
  pinMode(PPS_INPUT_PIN, INPUT);
  // Set up timer 1 for input capture of PPS signal
  TCCR1A = 0;            // reset timer1
  TCCR1B = 0;             
  TCNT1 = 0;
  TCCR1B = bit(ICES1) | bit(CS10);        // no prescale; capture on rising edge
  TIMSK1 = bit(ICIE1) | bit(TOIE1);       // enable capture interrupt; enable overflow interrupt 
}

void loop()
{
  if (captureFlag) {
    uint16_t t = captureTicks;
    uint16_t r = captureRolls;
    captureFlag = false;
    
    uint32_t captureTime = (uint32_t(r) << 16) + uint32_t(t);
    uint32_t elapsed = captureTime - prevCaptureTime;
    prevCaptureTime = captureTime;
    Serial.print(elapsed);
    Serial.print(" cycles/sec, ");
    Serial.print(float(elapsed)/16.0 - 1000000.0, 1);
    Serial.print(" ppm");
    Serial.println();
  }
}