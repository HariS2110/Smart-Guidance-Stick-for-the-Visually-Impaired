#include <SoftwareSerial.h>
#include <NMEAGPS.h>
#include <NewPing.h>

//Define the pins for the ultrasonic sensor
#define TRIGGER_PIN  5
#define ECHO_PIN     4
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//Define GPS Module Pins
#define GPS_TX_PIN 10
#define GPS_RX_PIN 11

#define WATER_SENSOR_PIN A0 // Analog pin for water sensor
#define BUTTON_PIN 7 // Pin for the button

SoftwareSerial gpsPort(GPS_TX_PIN, GPS_RX_PIN);
SoftwareSerial mySerial(8, 9); //Software serial for communication

NMEAGPS gps; //gps parser
gps_fix fix; //stores latest gps fix
uint8_t fixCount = 0; //count of gps fixes

#define BUZZER_PIN 6 // Define the pin connected to the buzzer

void setup()  
{
  Serial.begin(9600);
  mySerial.begin(9600);
  gpsPort.begin(9600);
  
  Serial.println("Initializing...");
  
  
  pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as an output
  pinMode(WATER_SENSOR_PIN, INPUT); // Set water sensor pin as input
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with internal pull-up resistor
  delay(1000);
}

void loop() 
{
  if (gps.available(gpsPort))
  {
    fix = gps.read();
    fixCount++;

    Serial.print("Distance: ");
    int distance = sonar.ping_cm();
    Serial.print(distance);
    Serial.println(" cm");

    int rainValue = analogRead(WATER_SENSOR_PIN);
    Serial.print("Rain Sensor Value: ");
    Serial.println(rainValue);

    if (distance < 70) // If an obstacle is detected within 70 cm
    {
      buzz(); // Buzz the buzzer
    }

    if (rainValue < 500) // If water sensor value is less than 500
    {
      buzzFast(); // Buzz the buzzer faster
    }

    if (digitalRead(BUTTON_PIN) == LOW) // If button is pressed
    {
      sendSMS(); // Send SMS
      Serial.println("Message sent");
      delay(500); // Debounce delay
    }

    if (fixCount >= 5)
    {
      fixCount = 0;
      Serial.println("Acquired Data");
      Serial.println("-------------");
      gpsdump();
      Serial.println("-------------");
      Serial.println();
    }
  }
}

void gpsdump()
{
  Serial.print("Latitude: ");
  Serial.println(fix.latitude(), 6); // Prints latitude with 6 decimal places
  
  Serial.print("Longitude: ");
  Serial.println(fix.longitude(), 6); // Prints longitude with 6 decimal places
}

void buzz()
{
  digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
  delay(200); // Buzz for 200 milliseconds
  digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
}

void buzzFast()
{
  digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
  delay(50); // Buzz for 50 milliseconds (faster beep)
  digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void sendSMS()
{
  mySerial.println("AT+CMGF=1"); // Set the SMS mode to text
  updateSerial();
  mySerial.println("AT+CMGS=\"+447392069406\""); // enter your phone number here (prefix country code)
  updateSerial();
  String googleMapsLink = "Hi, I need help. My location is: http://maps.google.com/maps?q=" + String(fix.latitude(), 6) + "," + String(fix.longitude(), 6);
  mySerial.print(googleMapsLink); // enter your message here
  updateSerial();
  mySerial.write(26); // End the message with Ctrl+Z
  delay(500);
}
