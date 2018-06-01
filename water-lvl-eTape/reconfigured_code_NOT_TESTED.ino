// This #include statement was automatically added by the Particle IDE.
#include <SparkFunMicroOLED.h>



MicroOLED oled;
 
void setup() {
    Serial.begin(9600);

    oled.begin();     // Initialize the OLED
    oled.clear(ALL);  // Clear the display's internal memory
    oled.display();   // Display what's in the buffer (splashscreen)
    delay(1000);      // Delay 500 ms
    oled.clear(PAGE); // Clear the buffer.
    oled.display();  
    
}
float R = 1000;      // resistance of resistor used in the circuit in ohms
float v;             // variable to hold sensor reading
float h;             // fluid height with respect to reference
float ho;            // reference height
int i = 0;           // counter
 
void loop() {
  // Measure sensor resistance.
   // put your main code here, to run repeatedly:
  v = analogRead(A0);             // read sensor
  v = 5*v/1023;                   // convert sensor reading to voltage
 
  // measure height for reference
  if ( i == 0)
  {
    ho = (1500 + R*(1 - 5/v))/140;  //this will print the baseline to the oled screen 
    i++;                            // you will have five seconds to place in tank before the second reading
    Particle.publish("baseline",ho);
    oled.setCursor(0, 0); // Set cursor to middle-left
    oled.print("base: "); // print h:
    oled.print(ho);  // Print value of h (e.g. 3)
  // Print humidity value
    oled.display(); // Draw on the screen

    delay(5000); // five seconds, only runs once to get baseline
  }
 
  h = (1500 + R*(1 - 5/v))/140 - ho + 1;   // calculate fluid height
                                           // in inches with respect to reference
                                           // 1 is activation height
                                           
    delay(100);                          // make easier to read

    Particle.publish("h",h);  // publishes fluid height referenced above
    Particle.publish("v",v);  // 
    oled.setCursor(0, 0); // Set cursor to middle-left
    oled.print("h: "); // print h:
    oled.print(h);  // Print value of h (e.g. 3)
    // h: 3
    oled.setCursor(0, 32); // Set cursor bottom-left
    oled.print("v: ");
    oled.print(v);  // Print temperature value
  // Print humidity value
    oled.display(); // Draw on the screen

    delay(500); // half second
}


float readResistance(int pin, int seriesResistance) {
  // Get ADC value.
  float resistance = analogRead(pin);
  // Convert ADC reading to resistance.
  resistance = (1023.0 / resistance) - 1.0;
  resistance = seriesResistance / resistance;
  return resistance;
}

float resistanceToVolume(float resistance, float zeroResistance, float calResistance, float calVolume) {
  if (resistance > zeroResistance || (zeroResistance - calResistance) == 0.0) {
    // Stop if the value is above the zero threshold, or no max resistance is set (would be divide by zero).
    return 0.0;
  }
  // Compute scale factor by mapping resistance to 0...1.0+ range relative to maxResistance value.
  float scale = (zeroResistance - resistance) / (zeroResistance - calResistance);
  // Scale maxVolume based on computed scale factor.
  return calVolume * scale;
}