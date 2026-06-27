# TI TMP75C

Thermo 22 Click is a compact add-on board that provides an accurate temperature measurement. This board features the TMP75C, a high-precision digital temperature sensor from Texas Instruments. The TMP75C houses an integrated digital temperature sensor with a 12-bit analog-to-digital converter (ADC), a reference circuit, and serial interface logic functions in one package. Characterized by its high accuracy (up to ±0.25°C typical) and high resolution of 0.0625°C, this temperature sensor provides temperature data to the host controller with a configurable I2C interface. This Click board™ is appropriate for thermal management and protection of various consumer, industrial, and environmental applications.

https://www.mikroe.com/thermo-22-click

https://download.mikroe.com/documents/datasheets/TMP75C_datasheet.pdf

https://github.com/jeremycole/Temperature_LM75_Derived

Install "I2C Temperature Sensors derived from the LM75@1.0.3"

Default address is 0x4F for the Thermo 22 Click.

Open "BasicUsage" skech in Examples

Set the default address like below

```c
/*
Read the temperature from an LM75-derived temperature sensor, and display it
in Celcius every 250ms. Any LM75-derived temperature should work.
*/

#include <Temperature_LM75_Derived.h>

// The Generic_LM75 class will provide 9-bit (±0.5°C) temperature for any
// LM75-derived sensor. More specific classes may provide better resolution.
Generic_LM75 temperature(0x4F);

void setup() {
  while(!Serial) {}
  
  Serial.begin(9600);

  Wire.begin();
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(temperature.readTemperatureC());
  Serial.println(" C");

  delay(250);
}
```




