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
void LowPassFilter();
void HighPassFilter();

void DAConvert(byte sample)
{
  PORTB = sample;
}

void LowPassFilter()
{
  const float b[19] = {-0.002693840, -0.002519748, 0.005014695, 0.015641050, 0.000000000, 
                    -0.046914239, -0.048021820, 0.083481298, 0.294332820, 0.400000000, 
                    0.294332820, 0.083481298, -0.048021820, -0.046914239, 0.000000000,
                    0.015641050, 0.005014695, -0.002519748, -0.002693840}; 
                    // Incants the arcane numbers (Coefficients for Goertzel Algorithm)
  int sampleInF = 0;
  int sampleSum = 0;
  int sampleBuffer[19];
  
  sampleInF = analogRead(signalPin); //sample the input
  sampleInF = map(sampleIn, 0, 1023, -512, 511);
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleInF; //add current sample to buffer as most recent
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleSum += b[i] * sampleBuffer[18-i];
  }
  sampleSum = constrain(sampleSum, -512, 511); //Probably not necessary, but try adding this if the output sounds weird
  sampleSum = map(sampleSum, -512, 511, 0, 1023);
  sampleOut = sampleSum >> 4;
  //sampleOut = 63 - sampleOut; //Makes it a high pass filter instead of low pass
  DAConvert(sampleOut); //send the sample to the DAC
  sampleSum = 0; //reset the sum to zero
}

void HighPassFilter()
{
  const float b[19] = {-0.002693840, -0.002519748, 0.005014695, 0.015641050, 0.000000000, 
                    -0.046914239, -0.048021820, 0.083481298, 0.294332820, 0.400000000, 
                    0.294332820, 0.083481298, -0.048021820, -0.046914239, 0.000000000,
                    0.015641050, 0.005014695, -0.002519748, -0.002693840}; 
                    // Incants the arcane numbers (Coefficients for Goertzel Algorithm)
  int sampleInF = 0;
  int sampleSum = 0;
  int sampleBuffer[19];
  
  sampleInF = analogRead(signalPin); //sample the input
  sampleInF = map(sampleIn, 0, 1023, -512, 511);
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleInF; //add current sample to buffer as most recent
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleSum += b[i] * sampleBuffer[18-i];
  }
  sampleSum = constrain(sampleSum, -512, 511); //Probably not necessary, but try adding this if the output sounds weird
  sampleSum = map(sampleSum, -512, 511, 0, 1023);
  sampleOut = sampleSum >> 4;
  sampleOut = 63 - sampleOut; //Makes it a high pass filter instead of low pass
  DAConvert(sampleOut); //send the sample to the DAC
  sampleSum = 0; //reset the sum to zero
}


void setup()
{
  //Serial.begin(9600);
  DDRB = B111111; //sets Port B to output
  DDRD = B00000010; //sets Port D to input on high bits - bits 0 and 1 are serial
  modeSetting = PIND >> 2; //reads the mode switches on Port D
  // create loops here to do something different based on the modes
  //Mode 0 in loop() - 8.7khz input/output
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
      delayMicroseconds(280); 
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
  //Mode 8: Low Pass Filter
  while (modeSetting == 8)
  {
      LowPassFilter();
  }
  //Mode 9: High Pass Filter
  while (modeSetting == 9)
  {
      HighPassFilter();      
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
  //Mode 12: 8x gain
  while (modeSetting == 12)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -4096, 4095); //zero-center the input with 8x gain, store in adjustment variable
      sampleAdj = constrain(sampleAdj, -512, 511); //constrain to limits
      sampleOut = map(sampleAdj, -512, 511, 0, 63); //map to 6 bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 13: 16x gain
  while (modeSetting == 13)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -8192, 8191); //zero-center the input with 16x gain, store in adjustment variable
      sampleAdj = constrain(sampleAdj, -512, 511); //constrain to limits
      sampleOut = map(sampleAdj, -512, 511, 0, 63); //map to 6 bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 14: square wave w/ hysteresis
  while (modeSetting == 14)
  {
      sampleIn = analogRead(signalPin); //sample the input
      if (sampleIn > 521)
      {
        sampleOut = 63; //
      }
      if (sampleIn < 501)
      {
        sampleOut = 0;
      }
      DAConvert(sampleOut);
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

