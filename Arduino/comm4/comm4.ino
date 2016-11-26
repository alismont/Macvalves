#include <SoftwareSerial.h>

//SoftwareSerial mySerial(13,12); // RX, TX

const int ledPin = 13;      // the pin that the LED is attached to

const int redPin = 3;      // the pin that the red pin of the RGB LED is attached to
const int greenPin = 5;    // the pin that the green pin of the RGB LED is attached to
const int bluePin = 6;     // the pin that the blue pin of the RGB LED is attached to

#define HEADER        '|'
#define MESSAGE_BYTES  5  // the total bytes in a message

void setup()
{
  // initialize the serial communication:
//  Serial.begin(9600);
  // initialize the ledPin as an output:
  pinMode(ledPin, OUTPUT);
  
  // bluetooth serial
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop() {

  while ( Serial3.available() > 0)
  {
    //if( Serial3.read() == HEADER)
    //{
      int brightness = Serial3.read();

      int red = Serial3.read(); 
      Serial.println(red); 
 
      int green = Serial3.read();
      Serial.println(green);
       
      int blue = Serial3.read();
      Serial.println(blue); 
      
    //}
  }

  /*
    // read the most recent byte (which will be from 0 to 255):
   info = Serial.read();
   // set the brightness of the LED:
   analogWrite(ledPin, brightness);
   */
}