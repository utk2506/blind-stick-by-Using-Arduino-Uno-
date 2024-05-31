#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

int theft_Sensor = 4;
String textForSMS;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin); // for gps
SoftwareSerial SIM900(7, 8);    // for gsm module

const int pushButtonPin = 5;

void setup()
{
  SIM900.begin(19200);
  Serial.begin(9600);
  ss.begin(GPSBaud);
  delay(5000);
  Serial.println("Logging time completed!");

  pinMode(pushButtonPin, INPUT_PULLUP);
}

void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \"+919798461659\"");
  delay(100);
  SIM900.println(message);
  delay(100);
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  delay(5000);
}

void loop()
{
  if (digitalRead(pushButtonPin) == LOW)
  {
    sendGPSMessage();
    delay(1000); // Adjust this delay based on your requirements
  }
}
void sendGPSMessage()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read()));

  if (gps.location.isValid())
  {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();

    String mylati = String(latitude, 6);
    String mylong = String(longitude, 6);

    // Construct the Google Maps link
    textForSMS = "Button pressed - Location: http://maps.google.com/maps?q=" + mylati + "," + mylong;
    
    // Send the SMS
    sendSMS(textForSMS);
    
    Serial.println("Button pressed - Message sent.");
  }
  else
  {
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();

    String mylati = String(latitude, 6);
    String mylong = String(longitude, 6);

    // Construct the Google Maps link
    textForSMS = "Button pressed - Location: http://maps.google.com/maps?q=" + mylati + "," + mylong;
    
    // Send the SMS
    sendSMS(textForSMS);
    
    Serial.println("Button pressed - Message sent.");
    Serial.println("Button pressed - Invalid GPS data.");
    
  }

  // Reset GPS data for the next iteration
  gps = TinyGPSPlus();
}
