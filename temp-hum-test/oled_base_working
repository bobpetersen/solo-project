#include <Adafruit_DHT.h>

#include <SparkFunMicroOLED.h>


char resultstr[128]; // This is where we will put the data
MicroOLED oled;

void setup() {

    Particle.variable("result", resultstr, STRING);

    oled.begin();       // Initialize the OLED
    oled.clear(ALL);    // Clear the display's internal memory
    oled.display();     // Display what's in the buffer (splashscreen)
    delay(1000);         // Delay 500 ms
    oled.clear(PAGE);   // Clear the buffer.
    oled.display();     // Display what's in the buffer (splashscreen)
}

void loop() {
    double t = 32.27; // TODO: Replace with actual seonsor data
    double h = 47;
    double f = t * 1.8 + 32;
    sprintf(resultstr, "{\"humidity\":%4.2f,\"temp\":%4.2f}", h, f);
    Particle.publish("reading", resultstr);
    
    oled.setCursor(0, 0);  // Set cursor to middle-left
    oled.print("t: ");
    oled.print(f);          // Print temperature value
    oled.setCursor(0, 32);  // Set cursor bottom-left
    oled.print("h: ");
    oled.print(h);          // Print humidity value
    oled.display();         // Draw on the screen
    
    delay(5000);
    
    oled.clear(PAGE);   // Clear the buffer.
    oled.display();         // Draw on the screen
    
    delay(10000);
}