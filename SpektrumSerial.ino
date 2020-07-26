/*
  SerialPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
  attached to the Serial Monitor, and "Serial1" refers to the hardware serial
  port attached to pins 0 and 1. This sketch will emulate Serial passthrough
  using those two Serial ports on the boards mentioned above, but you can change
  these names to connect any two serial ports on a board that has multiple ports.

  created 23 May 2016
  by Erik Nyquist
*/

char *inputString = 0;
char foundHeader = 0;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
}

void loop()
{
  if (foundHeader)
  {
    ///Test
    digitalWrite(14, HIGH);
    delayMicroseconds(40);
    digitalWrite(14, LOW);
    foundHeader = FALSE;
  }
}

void serialEvent1()
{

  while (Serial1.available())
  {
    //Serial.print("there has been a serial event \n \r ");
    char temp = Serial1.read();
    if (temp == 162)
    {
      foundHeader = TRUE;
      //Serial.print("\r");
      //Serial.print(temp, DEC);
      digitalWrite(14, HIGH);
      delayMicroseconds(20);
      digitalWrite(14, LOW);
      delayMicroseconds(10);
      for (int i = 0; i < 15; i++)
      {
        temp = Serial1.read();
        //Serial.print(" ");
        //Serial.print(temp, BIN);
        digitalWrite(14, HIGH);
        delayMicroseconds(5);
        digitalWrite(14, LOW);
        delayMicroseconds(10);
      }
    }
    else
      return;

    /*if (temp == 162)
    
      foundHeader = 1;
      Serial.print(" the char was ");
      Serial.print(temp, DEC);
      Serial.print("\n\r");
      Serial1.readBytes(inputString, 30);
      Serial.print("Found a potential Header \n \r ");
      Serial.print(" And this is the message ");
      for (int i = 0; i < 30; i++)
      {
        Serial.print(inputString[i], DEC);
        Serial.print(" ");
      }
      Serial.print("\n\r");
      //foundHeader=0;
      return;
    }
    else
    {
      Serial.print("No header... returning \n \r ");
      return;
    }*/
  }
}
