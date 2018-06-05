// This #include statement was automatically added by the Particle IDE.
#include <DS18B20.h>

// This #include statement was automatically added by the Particle IDE.
#include <SparkFunMicroOLED.h>

#include "math.h"
// MicroOLED oled;

const int MAXRETRY = 4;
const uint32_t msSAMPLE_INTERVAL = 500;
const uint32_t msMETRIC_PUBLISH = 1000;

DS18B20 ds18b20(D0, true); //Sets Pin D0 for Water Temp Sensor and
                           // this is the only sensor on bus
char szInfo[64];
double celsius;
double fahrenheit;
uint32_t msLastMetric;
uint32_t msLastSample;

MicroOLED oled;
char resultstr[128]; // This is where we will put the data

void setup()
{
    // Makes the resultstr variable available via the cload API as "result"
    // https://api.particle.io/v1/devices/ID_GOES_HERE/result?access_token=TOKEN_GOES_HERE
    Particle.variable("result", resultstr, STRING);

    // oled.begin();     // Initialize the OLED
    // oled.clear(ALL);  // Clear the display's internal memory
    // oled.display();   // Display what's in the buffer (splashscreen)
    // delay(1000);      // Delay 500 ms
    // oled.clear(PAGE); // Clear the buffer.
    // oled.display();   // Display what's in the buffer (splashscreen)
}

void loop()
{
    if (millis() - msLastSample >= msSAMPLE_INTERVAL)
    {
        getTemp();
    }

    if (millis() - msLastMetric >= msMETRIC_PUBLISH)
    {
        Serial.println("Publishing now.");
        publishData();
    }
    // oled.setCursor(0, 0); // Set cursor to middle-left
    // oled.print("szInfo: ");
    // oled.print(szInfo);         // Print temperature value
    // oled.setCursor(0, 32); // Set cursor bottom-left
    // oled.print("fahrenheit: ");
    // oled.print(fahrenheit);  // Print humidity value
    // oled.display(); // Draw on the screen

    // delay(5000);

    // oled.clear(PAGE); // Clear the buffer.
    // oled.display();   // Draw on the screen
    //sprintf(resultstr, "{\"humidity\":%4.2f,\"temp\":%4.2f}", h, f); // <- set the variable
    delay(1000);
}

void publishData()
{
    sprintf(szInfo, "%2.2f", fahrenheit);
    Particle.publish("dsTmp", szInfo);
    msLastMetric = millis();
}

void getTemp()
{
    float _temp;
    int i = 0;

    do
    {
        _temp = ds18b20.getTemperature();
    } while (!ds18b20.crcCheck() && MAXRETRY > i++);

    if (i < MAXRETRY)
    {
        celsius = _temp;
        fahrenheit = ds18b20.convertToFahrenheit(_temp);
        Serial.println(fahrenheit);
    }
    else
    {
        celsius = fahrenheit = NAN;
        Serial.println("Invalid reading");
    }
    msLastSample = millis();
}