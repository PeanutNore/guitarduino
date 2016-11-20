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
const float Goertzel[19] = {-0.00269, -0.00252, 0.00501, 0.01564, 0.00000, 
                    -0.04691, -0.04802, 0.08348, 0.29433, 0.40000, 
                    0.29433, 0.08348, -0.04802, -0.04691, 0.00000,
                    0.01564, 0.00501, -0.00251, -0.00269}; 
                    // Incants the arcane numbers (Coefficients for Goertzel Algorithm)
float sampleFloat = 0.0;
unsigned int sampleIn = 0; //Stores the sample from the ADC
unsigned int sampleABS = 0; //Stores the absolute value of the sample
int sampleSum = 0; //Stores the sum used in filter algorithm
float sampleBuffer[19]; //buffers samples used in filter algorithm
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
  sampleIn = analogRead(signalPin); //sample the input
  sampleAdj = sampleIn - 512; //center around 0
  sampleFloat = (float)sampleAdj / 512.0; //transform into value from -1 to 1 for working sample
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleFloat; //add current sample to buffer as most recent
  sampleFloat = 0.0; //clears the working sample
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleFloat += Goertzel[i] * sampleBuffer[18-i];
  }
  sampleFloat *= 512.0;//rescale
  sampleSum = (int)sampleFloat; //make the working sample an INT again
  sampleOut = map(sampleSum, -512, 511, 0, 63);
  //sampleOut = 63 - sampleOut; //Makes it a high pass filter instead of low pass
  DAConvert(sampleOut); //send the sample to the DAC
  sampleSum = 0; //reset the sum to zero
}

void HighPassFilter()
{
  sampleIn = analogRead(signalPin); //sample the input
  sampleAdj = sampleIn - 512; //center around 0
  sampleFloat = (float)sampleAdj / 512.0; //transform into value from -1 to 1 for working sample
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleFloat; //add current sample to buffer as most recent
  sampleFloat = 0.0; //clears the working sample
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleFloat += Goertzel[i] * sampleBuffer[18-i];
  }
  sampleFloat *= 512.0;//rescale
  sampleSum = (int)sampleFloat; //make the working sample an INT again
  sampleOut = map(sampleSum, -512, 511, 0, 63);
  sampleOut = 63 - sampleOut; //Makes it a high pass filter instead of low pass
  DAConvert(sampleOut); //send the sample to the DAC
  sampleSum = 0; //reset the sum to zero
  sampleFloat = 0;
}


void setup()
{
  //Serial.begin(9600);
  DDRB = B111111; //sets Port B to output
  DDRD = B00000010; //sets Port D to input on high bits - bits 0 and 1 are serial
  for (int i = 0; i < 19; i++)
  {
      sampleBuffer[i] = 0;
  }
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
  //Mode 5: SRR, ~1.98khz
  while (modeSetting == 5)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(392); 
  }
  //Mode 6LPF
   while (modeSetting == 6)
  {
      LowPassFilter();
  }
  //Mode 7: Instant Attack Compressor
  while (modeSetting == 7)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = sampleIn - 512; //Zero center the input
      sampleFloat = (float)sampleAdj / 512.0; 
      sampleFloat = (2.0 * sampleFloat) / (1.0 + abs(sampleFloat)); //Compress the sample
      sampleFloat *= 614.4; //A little make-up gain, rescale for output
      sampleAdj = (int)sampleFloat; 
      sampleAdj = constrain(sampleAdj, -512, 511);//Put sample in range for output
      sampleIn = sampleAdj + 512;//return to positive values only
      sampleOut = sampleIn >> 4;//toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 8: Insane but faster Non-Linear Distortion
  while (modeSetting == 8)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = sampleIn - 512; // center around 0
      if (sampleAdj < -448){
        sampleAdj = -512;}
      else if (sampleAdj < -384){
        sampleAdj -= 128;}
      else if (sampleAdj < -320){
        sampleAdj -= 112;}
      else if (sampleAdj < -256){
        sampleAdj -= 96;}
      else if (sampleAdj < -192){
        sampleAdj -= 80;}
      else if (sampleAdj < -128){
        sampleAdj -= 64;}
      else if (sampleAdj < -64){
        sampleAdj -= 48;}
      else if (sampleAdj < 0){
        sampleAdj -= 32;}
      else if (sampleAdj < 63){
        sampleAdj += 32;}
      else if (sampleAdj < 127){
        sampleAdj += 48;}
      else if (sampleAdj < 191){
        sampleAdj += 64;}
      else if (sampleAdj < 255){
        sampleAdj += 80;}
      else if (sampleAdj < 319){
        sampleAdj += 96;}
      else if (sampleAdj < 383){
        sampleAdj += 112;}
      else if (sampleAdj < 447){
        sampleAdj += 128;}
      else {
        sampleAdj = 511;}
      sampleAdj = constrain (sampleAdj, -512, 511);
      sampleIn = sampleAdj + 512;
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 9: Sane but slower Non-Linear
  while (modeSetting == 9)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = sampleIn - 512; // center around 0
      sampleFloat = (float)sampleAdj;
      sampleABS = abs(sampleAdj);
      if (sampleABS < 4){
        sampleFloat *= 1.3;}
      else if (sampleABS < 8){
        sampleFloat *= 1.4;}
      else if (sampleABS < 16){
        sampleFloat *= 1.5;}
      else if (sampleABS < 32){
        sampleFloat *= 1.6;}
      else if (sampleABS < 64){
        sampleFloat *= 1.7;}
      else if (sampleABS < 128){
        sampleFloat *= 1.9;}
      else if (sampleABS < 256){
        sampleFloat *= 2.0;}
      else {
        sampleFloat = 511;}
      sampleAdj = sampleFloat;
      sampleAdj = constrain (sampleAdj, -512, 511);
      sampleIn = sampleAdj + 512;
      sampleOut = sampleIn >> 4; //toss the 4 least significant bits
      DAConvert(sampleOut); //send the sample to the DAC   
  }
  //Mode 10: bitcrush (4 bit) + SRR ("hi fi")
  while (modeSetting == 10)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = map(sampleIn, 0, 1023, 0, 15); //toss the 6 least significant bits
      sampleOut = map(sampleOut, 0, 15, 0, 63); //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 11: bitcrush (5 bit) + SRR ("lo fi")
  while (modeSetting == 11)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleOut = map(sampleIn, 0, 1023, 0, 15); //toss the 6 least significant bits
      sampleOut = map(sampleOut, 0, 15, 0, 63); //shift to most significant bits for output
      DAConvert(sampleOut); //send the sample to the DAC
      delayMicroseconds(392);
  }
  //Mode 12: 16x gain
  while (modeSetting == 12)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -8192, 8191); //zero-center the input with 16x gain, store in adjustment variable
      sampleAdj = constrain(sampleAdj, -512, 511); //constrain to limits
      sampleOut = map(sampleAdj, -512, 511, 0, 63); //map to 6 bits for output
      DAConvert(sampleOut); //send the sample to the DAC
  }
  //Mode 13: SLAM!!! 64x gain
  while (modeSetting == 13)
  {
      sampleIn = analogRead(signalPin); //sample the input
      sampleAdj = map(sampleIn, 0, 1023, -32768, 32767); //zero-center the input with 64x gain, store in adjustment variable
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
      sampleAdj = sampleIn - 512; //zero-center the input, store in adjustment variable
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

