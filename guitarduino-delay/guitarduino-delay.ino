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

int sampleIn = 0; //sets up a variable to store the sample
byte sampleOut = 0; //sets up a variable to convert the sample to 6 bits
int delaySample[256]; //array to store delay samples
byte delayStep = 0;

void DAConvert(byte sample);//sends a 6 bit sample to the DAC

void DAConvert(byte sample)
{
  PORTB = sample;
}

void setup()
{
  //Serial.begin(9600);
  DDRB = B111111;
  int i;
  for (i = 0; i < 256; i++)
  {
    delaySample[i] = 0;
  }
}


void loop()
{
  sampleIn = analogRead(signalPin); //sample the input
  sampleIn = map(sampleIn, 0, 1023, -512, 511);
  delaySample[delayStep] = sampleIn;
  if (abs(sampleIn) > abs(delaySample[delayStep - 255]))
  {
    sampleOut = map(sampleIn, -512, 511, 0, 63); //convert the sample to 6 bits  
  }
  else
  {
    sampleOut = map(delaySample[delayStep - 255], -512, 511, 0, 63);
  }
  DAConvert(sampleOut); //send the current sample to the DAC
  delayStep++;
  delayMicroseconds(50); //it takes 100 microseconds to sample, adjust for best sound
}
