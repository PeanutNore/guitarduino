unsigned long startTime = 0;
unsigned long endTime = 0;
int duration = 0;

const int signalPin = A0; //establish pin 0 as the analog input
const float Goertzel[19] = {-0.002693840, -0.002519748, 0.005014695, 0.015641050, 0.000000000, 
                    -0.046914239, -0.048021820, 0.083481298, 0.294332820, 0.400000000, 
                    0.294332820, 0.083481298, -0.048021820, -0.046914239, 0.000000000,
                    0.015641050, 0.005014695, -0.002519748, -0.002693840}; 
                    // Incants the arcane numbers (Coefficients for Goertzel Algorithm)
float sampleFloat = 0;
unsigned int sampleIn = 0; //Stores the sample from the ADC
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
  sampleFloat = sampleAdj / 512.0; //transform into value from -1 to 1 for working sample
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleFloat; //add current sample to buffer as most recent
  sampleFloat = 0; //clears the working sample
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleFloat += Goertzel[i] * sampleBuffer[18-i];
  }
  sampleSum = sampleFloat * 512; //make the working sample an INT again
  sampleOut = map(sampleSum, -512, 511, 0, 63);
  //sampleOut = 63 - sampleOut; //Makes it a high pass filter instead of low pass
  DAConvert(sampleOut); //send the sample to the DAC
  sampleSum = 0; //reset the sum to zero
}

void HighPassFilter()
{
  sampleIn = analogRead(signalPin); //sample the input
  sampleAdj = sampleIn - 512; //center around 0
  sampleFloat = sampleAdj / 512.0; //transform into value from -1 to 1 for working sample
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleFloat; //add current sample to buffer as most recent
  sampleFloat = 0; //clears the working sample
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleFloat += Goertzel[i] * sampleBuffer[18-i];
  }
  sampleSum = sampleFloat * 512; //make the working sample an INT again
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
    LowPassFilter();
  } 
  while (modeSetting == 2)
  {
    HighPassFilter();
  }
}


void loop()
{
  startTime = micros();
  sampleIn = analogRead(signalPin); //sample the input
  for (int i = 1; i < 18; i++) //shift all the samples in the buffer one position lower
  {
    sampleBuffer[i-1] = sampleBuffer[i];
  }
  sampleBuffer[18] = sampleIn; //add current sample to buffer as most recent
  for (int i = 0; i < 19; i++) //Takess the sum of all samples in the buffer * their coefficients
  {
    sampleSum += Goertzel[i] * sampleBuffer[18-i];
  }
  sampleSum = constrain(sampleSum, 0, 1023); //Probably not necessary, but try adding this if the output sounds weird
  sampleOut = sampleSum >> 4;
  //sampleOut = 63 - sampleOut; //Makes it a high pass filter instead of low pass
  DAConvert(sampleOut); //send the sample to the DAC
  sampleSum = 0; //reset the sum to zero
  endTime = micros();
  duration = endTime - startTime;
  Serial.print("Run Time: ");
  Serial.println(duration);
  delay(500);
}
