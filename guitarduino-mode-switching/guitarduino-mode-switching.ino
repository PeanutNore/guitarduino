/*  GUITARDUINO Digital Guitar Effects Processor
    Copyright (C) 2011-2015  Samuel Brown

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

const int signalPin = A0; //establish pin 0 as the analog input

unsigned int sampleIn = 0; //Stores the sample from the ADC
byte sampleOut = 0; //Stores the sample to send to the DAC
byte modeInput = 0; //Storse mode switch settings
byte modeA = 0; //Stores the highest 2 mode switches, "Mode A" on the device
byte modeB = 0; //Stores the lowest 2 mode switches, "Mode B" on the device
const boolean runLoop = true; //If a loop is running, it should run until the device is reset. Might not be needed.

void DAConvert(byte sample);//sends a 6 bit sample to the DAC



void DAConvert(byte sample)
{
  PORTB = sample;
}

void setup()
{
  //Serial.begin(9600);
  DDRB = B111111; //sets Port B to output
  DDRD = B00000010; //sets Port D to input on high bits - bits 0 and 1 are serial
  modeInput = PIND; //reads the mode switches on Port D
  modeInput = modeInput >> 2; //shift over to lowest bits
  modeA = modeInput & B00001100;
  modeA = modeA >> 2;
  modeB = modeInput & B00000011;
  /* create loops here to do something different based on the modes
  Example:
  while (modeA & 1 == B11)//Runs forever if Mode A was set to "1"
  {
      //do stuff
  }
  End Example */
}


void loop()
{
  sampleIn = analogRead(signalPin); //sample the input
  sampleOut = sampleIn >> 4; //toss the 4 least significant bits
  DAConvert(sampleOut); //send the sample to the DAC
  //delayMicroseconds(80); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
}

