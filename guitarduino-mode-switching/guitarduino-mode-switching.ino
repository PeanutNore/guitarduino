

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
int sampleAdj = 0; // For "Adjusting" the sample when negative values are needed
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
  //Mode 1: SRR, ~4.46khz
  while (modeSetting == 1)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(112); 
  }
  //Mode 2: SRR, ~3.57khz
  while (modeSetting == 2)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(168); 
  }
  //Mode 3: SRR, ~2.98khz
  while (modeSetting == 3)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(224); 
  }
  //Mode 4: SRR, ~2.55khz
  while (modeSetting == 4)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(280); /
  }
  //Mode 5: SRR, ~2.23khz
  while (modeSetting == 5)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(336); 
  }
  //Mode 6: SRR, ~1.98khz
   while (modeSetting == 6)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(392); 
  }
  //Mode 7: SRR, ~1.79khz
  while (modeSetting == 7)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(448); 
  }
  //Mode 8: bitcrush (5 bit) + SRR, ~3.57khz
  while (modeSetting == 8)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(168);
  }
  //Mode 9: bitcrush (5 bit) + SRR, ~2.55khz
  while (modeSetting == 9)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(280);
  }
  //Mode 10: bitcrush (5 bit) + SRR, ~1.98khz
  while (modeSetting == 10)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(392);
  }
  //Mode 11: bitcrush (5 bit) + SRR, ~1.62khz
  while (modeSetting == 11)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 5; //toss the 6 least significant bits
      sampleOut = sampleIn << 1; //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(504);
  }
  //Mode 12: 4x gain
  while (modeSetting == 12)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -512, 511); //zero-center the input, store in adjustment variable
      sampleAdj *= 4; //apply gain
      sampleAdj = constrain(sampleAdj, -512, 511); //constrain to limits
      sampleOut = map(sampleAdj, -512, 511, 0, 63); //map to 6 bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 13: 8x gain
  while (modeSetting == 13)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -512, 511); //zero-center the input, store in adjustment variable
      sampleAdj *= 8; //apply gain
      sampleAdj = constrain(sampleAdj, -512, 511); //constrain to limits
      sampleOut = map(sampleAdj, -512, 511, 0, 63); //map to 6 bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 14: 16x gain
  while (modeSetting == 14)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -512, 511); //zero-center the input, store in adjustment variable
      sampleAdj *= 16; //apply gain
      sampleAdj = constrain(sampleAdj, -512, 511); //constrain to limits
      sampleOut = map(sampleAdj, -512, 511, 0, 63); //map to 6 bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 15: octave up (frequecy doubler / rectifier)
  while (modeSetting == 15)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -512, 511); //zero-center the input, store in adjustment variable
      sampleAdj = abs(sampleAdj); //"rectify" the sample (doubles frequency)
      sampleOut = map(sampleAdj, 0, 512, 0, 63); //map to 6 bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
}


void loop()
{
  sampleIn = analogRead(signalPin); //sample the input
  sampleOut = sampleIn >> 4; //toss the 4 least significant bits
  DAConvert(sampleOut); //send the sample to the DAC
  //delayMicroseconds(80); //it takes about 115 microseconds to run the above code, add delay here to decrease sample rate
}

