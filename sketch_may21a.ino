#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Parallel LCD Display Configuration
// LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);
// RS (Pin 4) -> Arduino Pin 12
// E (Pin 6)  -> Arduino Pin 11
// D4 (Pin 11) -> Arduino Pin 5
// D5 (Pin 12) -> Arduino Pin 4
// D6 (Pin 13) -> Arduino Pin 3
// D7 (Pin 14) -> Arduino Pin 2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // <<< DECLARATION for parallel LCD

void setup() 
{
    Serial.begin(9600);
    Serial.println("DIY Smart Temperature and Humidity Monitor with Arduino!");
    dht.begin();
    lcd.begin(16,2);

    // Print a welcome message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp & Humidity");
  lcd.setCursor(0, 1); // Set cursor to column 0, row 1 (bottom row)
  lcd.print("Monitor Online!");
  delay(2000);

}
void loop() {
  lcd.clear();
    delay (2000);
    // Read Humidity Values
    float humidity= dht.readHumidity();
    //Read Temperature in Celcius
    float temperature= dht.readTemperature();
if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error: Failed to read from DHT sensor! Check your wiring.");
    return; 
    // Display error on LCD
    lcd.setCursor(0, 0);
    lcd.print("DHT Error!");
    lcd.setCursor(0, 1);
    lcd.print("Check Wiring.");
    delay(3000); // Show error message for 3 seconds
    return;
}
//Print readings on serial monitor
// First, print "humidity:"
Serial.print("Humidity: ");
//Print humidity value
Serial.print(humidity);
Serial.println("%  ");

//Secondly, Print readings on Temperature
Serial.print("temperature: ");
//Print temperature value
Serial.print(temperature);
Serial.println("C  ");

//LCD Readings
//Print Temperature readings


lcd.setCursor(0,0);
lcd.print("temp:" );
lcd.print(temperature, 1); // Print temperature with 1 decimal place
  lcd.print((char)223); // Special character for degree symbol (°)
  lcd.print("C");

  // Print Humidity readings
  lcd.setCursor(0, 1); // Column 0, Row 1
  lcd.print("Hum: ");
  lcd.print(humidity, 1); // Print humidity with 1 decimal place
  lcd.print(" %");
}