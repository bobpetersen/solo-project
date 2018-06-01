#include <Adafruit_DHT.h>

#include <SparkFunMicroOLED.h>

#define DHTPIN 2 // what pin we're connected to

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

char resultstr[128]; // This is where we will put the data
MicroOLED oled;

void setup()
{
    Serial.begin(9600);
    Serial.println("DHTxx test!");

    dht.begin();
    Particle.variable("result", resultstr, STRING);

    oled.begin();     // Initialize the OLED
    oled.clear(ALL);  // Clear the display's internal memory
    oled.display();   // Display what's in the buffer (splashscreen)
    delay(1000);      // Delay 500 ms
    oled.clear(PAGE); // Clear the buffer.
    oled.display();   // Display what's in the buffer (splashscreen)
}

void loop()
{
    delay(5000);

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a
    // very slow sensor)
    float h = dht.getHumidity();
    // Read temperature as Celsius
    float t = dht.getTempCelcius();
    // Read temperature as Farenheit
    float f = dht.getTempFarenheit();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    float hi = dht.getHeatIndex();
    float dp = dht.getDewPoint();
    float k = dht.getTempKelvin();

    Serial.print("Humid: ");
    Serial.print(h);
    Serial.print("% - ");
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print("*C ");
    Serial.print(f);
    Serial.print("*F ");
    Serial.print(k);
    Serial.print("*K - ");
    Serial.print("DewP: ");
    Serial.print(dp);
    Serial.print("*C - ");
    Serial.print("HeatI: ");
    Serial.print(hi);
    Serial.println("*C");
    Serial.println(Time.timeStr());

    // double t = 32.27; // TODO: Replace with actual seonsor data
    // double h = 47;
    // double f = t * 1.8 + 32;
    sprintf(resultstr, "{\"humidity\":%4.2f,\"temp\":%4.2f}", h, f);
    Particle.publish("reading", resultstr);

    oled.setCursor(0, 0); // Set cursor to middle-left
    oled.print("t: ");
    oled.print(f);         // Print temperature value
    oled.setCursor(0, 32); // Set cursor bottom-left
    oled.print("h: ");
    oled.print(h);  // Print humidity value
    oled.display(); // Draw on the screen

    delay(5000);

    oled.clear(PAGE); // Clear the buffer.
    oled.display();   // Draw on the screen

    delay(10000);
}