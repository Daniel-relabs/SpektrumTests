
#include <Arduino.h>
#include <HardwareSerial.h>
#include "heltec.h"

char *inputString = 0;
char foundHeader = 0;
char message[16];
unsigned char buffer[64]; // buffer array for data receive over serial port
int count = 0;
char temp = 0;

typedef struct
{
  char fades;
  char system;
  int servo[7];

} formatted_message;

formatted_message last;

void clearBufferArray() // function to clear buffer array
{
  for (int i = 0; i < count; i++)
  {
    buffer[i] = NULL;
  } // clear all index of array with command NULL
}

void setup()
{
  Serial.begin(115200);
  Serial.println("this is a test");
  Serial1.begin(115200);
  Serial2.begin(9600);
  pinMode(17, OUTPUT);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 0, "Spektrum Tests");
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 10, "Fad");
  //Heltec.display->drawString(20, 10, String(45));
  Heltec.display->drawString(64, 10, "Sys");
  Heltec.display->drawString(0, 20, "Ch");
  Heltec.display->drawString(64, 20, "Ch");
  Heltec.display->drawString(0, 30, "Ch");
  Heltec.display->drawString(64, 30, "Ch");
  Heltec.display->drawString(0, 40, "Ch");
  Heltec.display->drawString(64, 40, "Ch");
  Heltec.display->drawString(0, 50, "Ch");
  Heltec.display->display();
}

void loop()
{

  char chain_id;
  char chan_value;

  //Read the Serial port and process

  char index = 0;

  //Update the display
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 0, "Spektrum Tests");
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 10, "Fad");
  Heltec.display->drawString(64, 10, "Sys");
  Heltec.display->drawString(0, 20, "Ch");
  Heltec.display->drawString(64, 20, "Ch");
  Heltec.display->drawString(0, 30, "Ch");
  Heltec.display->drawString(64, 30, "Ch");
  Heltec.display->drawString(0, 40, "Ch");
  Heltec.display->drawString(64, 40, "Ch");
  Heltec.display->drawString(0, 50, "Ch");
  Heltec.display->drawString(20, 10, String(last.fades, DEC));
  Heltec.display->drawString(84, 10, String(last.system, HEX));
  Heltec.display->drawString(20, 20, String((last.servo[0] & 0x7800) / 2048, DEC));
  Heltec.display->drawString(30, 20, String((last.servo[0] & 0x07FF), DEC));
  Heltec.display->drawString(84, 20, String((last.servo[1] & 0x7800) / 2048, DEC));
  Heltec.display->drawString(94, 20, String((last.servo[1] & 0x07FF), DEC));
  Heltec.display->drawString(20, 30, String((last.servo[2] & 0x7800) / 2048, DEC));
  Heltec.display->drawString(30, 30, String((last.servo[2] & 0x07FF), DEC));
  Heltec.display->drawString(84, 30, String((last.servo[3] & 0x7800) / 2048, DEC));
  Heltec.display->drawString(94, 30, String((last.servo[3] & 0x07FF), DEC));
  Heltec.display->drawString(20, 40, String((last.servo[4] & 0x7800) / 2048, DEC));
  Heltec.display->drawString(30, 40, String((last.servo[4] & 0x07FF), DEC));
  Heltec.display->drawString(84, 40, String((last.servo[5] & 0x7800) / 2048, DEC));
  Heltec.display->drawString(94, 40, String((last.servo[5] & 0x07FF), DEC));
  Heltec.display->drawString(20, 50, String((last.servo[6] & 0x7800) / 2048, DEC));
  Heltec.display->drawString(30, 50, String((last.servo[6] & 0x07FF), DEC));
  Heltec.display->display();
  //delay(10);

  if (temp > 100)
    temp = 0;
  else
    temp++;

  if (Serial1.available())
  {
    while (Serial1.available())
    {
      message[index] = Serial1.read();
      if (message[index] == 0xA2)
      {
        digitalWrite(17, HIGH);
        delayMicroseconds(10);
        digitalWrite(17, LOW);
        delayMicroseconds(10);
        foundHeader = 1;
      }
      else
      {
        digitalWrite(17, HIGH);
        delayMicroseconds(5);
        digitalWrite(17, LOW);
        delayMicroseconds(10);
      }
      index++;
    }
    last.fades = message[0];
    last.system = message[1];
    //last.servo[0] = message[2] * 256 + message[3];
    index = 0;
    while (index < 8)
    {
      // servo 0 use 2 and 3
      // servo 1 use 4 and 5
      // servo 2 use 6 and 7...
      // servo 6 use 14 and 15...
      last.servo[index] = message[(2 * index) + 2] * 256 + message[(2 * index) + 3];
      index++;
    }
    // Finished reading

    /*if (foundHeader)
    {
      Heltec.display->drawString(20, 10, String(last.fades, DEC));
      Heltec.display->drawString(84, 10, String(last.system, HEX));
      Heltec.display->drawString(20, 20, String(last.servo[0]));
      Heltec.display->drawString(84, 20, String(last.servo[1]));
      Heltec.display->drawString(20, 30, String(last.servo[2]));
      Heltec.display->drawString(84, 30, String(last.servo[3]));
      Heltec.display->drawString(20, 40, String(last.servo[4]));
      Heltec.display->drawString(84, 40, String(last.servo[5]));
      Heltec.display->drawString(20, 50, String(last.servo[6]));
      Heltec.display->display();
      delay(10);
    }
    foundHeader = 0;*/
  }
  if (Serial2.available()) // if date is coming from software serial port ==> data is coming from SoftSerial shield
  {
    while (Serial2.available()) // reading data into char array
    {
      buffer[count++] = Serial2.read(); // writing data into array
      if (count == 64)
        break;
    }
    Serial.write(buffer, count); // if no data transmission ends, write buffer to hardware serial port
    clearBufferArray();          // call clearBufferArray function to clear the stored data from the array
    count = 0;                   // set counter of while loop to zero 
  }
}
