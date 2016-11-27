#include <SoftwareSerial.h>

//SoftwareSerial mySerial(13,12); // RX, TX

const int ledPin = 13;      // the pin that the LED is attached to

const int redPin = 3;      // the pin that the red pin of the RGB LED is attached to
const int greenPin = 5;    // the pin that the green pin of the RGB LED is attached to
const int bluePin = 6;     // the pin that the blue pin of the RGB LED is attached to

#define HEADER        '|'
#define MESSAGE_BYTES  5  // the total bytes in a message

String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 
String t=":";

int MEMOSYN=0;

char octetReception;
char caractereReception;
char octetReceptionProc;
char caractereReceptionProc;
String chaineReception, Tram;
String chaineReceptionProc, TramProc;


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

  Ecriture();
  /*
    // read the most recent byte (which will be from 0 to 255):
   info = Serial.read();
   // set the brightness of the LED:
   analogWrite(ledPin, brightness);
   */
}

//-------------
//========================================================ECRITURE
void Ecriture() {

  while (Serial3.available() > 0) { // si un caractère en réception

    octetReception = Serial3.read(); // lit le 1er octet de la file d'attente
    if (octetReception == '\n') { // si Octet reçu est le saut de ligne

     Serial.println(chaineReception);
      chaineReception = ""; //RAZ le String de réception
      //delay(100); // pause
      break; // s||t de la boucle while
    }
    else { // si le caractère reçu n'est pas un saut de ligne
      caractereReception = char(octetReception); // récupere le caractere à partir du code Ascii
      chaineReception = chaineReception + caractereReception; // ajoute la caractère au String
      //Serial.println (chaineReception);
      //delay(1); // laisse le temps au caractères d'arriver
    }
  }
}

