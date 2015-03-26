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
const float b[19] = {-0.002693840, -0.002519748, 0.005014695, 0.015641050, 0.000000000, 
                    -0.046914239, -0.048021820, 0.083481298, 0.294332820, 0.400000000, 
                    0.294332820, 0.083481298, -0.048021820, -0.046914239, 0.000000000,
                    0.015641050, 0.005014695, -0.002519748, -0.002693840}; 
                    // Incants the arcane numbers (Coefficients for Goertzel Algorithm)

unsigned int sampleIn = 0; //sets up a variable to store the sample
unsigned int sampleSum = 0;
byte sampleOut = 0; //sets up a variable to convert the sample to 6 bits
unsigned int sampleBuffer[19];



void DAConvert(byte sample);//sends a 6 bit sample to the DAC



void DAConvert(byte sample)
{
  PORTB = sample;
}

void setup()
{
  //Serial.begin(9600);
  DDRB = B111111;
  for (int i = 0; i < 19; i++)
  {
    sampleBuffer[i] = 0;
  }
}


void loop()
{
  sampleIn = analogRead(signalPin); //sample the input
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleIn; //add current sample to buffer as most recent
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleSum += b[i] * sampleBuffer[18-i];
  }
  //sampleSum = constrain(sampleSum, 0, 1023); //Probably not necessary, but try adding this if the output sounds weird
  sampleOut = sampleSum >> 4;
  //sampleOut = 63 - sampleOut; //Makes it a high pass filter instead of low pass
  DAConvert(sampleOut); //send the sample to the DAC
  sampleSum = 0; //reset the sum to zero
}
