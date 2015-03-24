

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
byte modeSetting = 0; //Storse mode switch settings
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
  modeSetting = PIND >> 2; //reads the mode switches on Port D
  // create loops here to do something different based on the modes
  while (modeSetting == 1)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(112); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
  }
  while (modeSetting == 2)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(168); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
  }
  while (modeSetting == 3)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(224); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
  }
  while (modeSetting == 4)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(280); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
  }
  while (modeSetting == 5)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(336); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
  }
   while (modeSetting == 6)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(392); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
  }
  while (modeSetting == 7)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(448); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
  }
  while (modeSetting == 8)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  while (modeSetting == 9)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(112);
  }
  while (modeSetting == 10)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(168);
  }
  while (modeSetting == 11)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(224);
  }
  while (modeSetting == 12)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(280);
  }
  while (modeSetting == 13)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(336);
  }
  while (modeSetting == 14)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(392);
  }
  while (modeSetting == 15)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(448);
  }
}


void loop()
{
  sampleIn = analogRead(signalPin); //sample the input
  sampleOut = sampleIn >> 4; //toss the 4 least significant bits
  DAConvert(sampleOut); //send the sample to the DAC
  //delayMicroseconds(80); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
}

