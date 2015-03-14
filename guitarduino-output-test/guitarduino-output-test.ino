const int signalPin = A0; //establish pin 0 as the analog input

byte sampleOut = 0; //sets up a variable to convert the sample to 6 bits



void DAConvert(byte sample);//sends a 6 bit sample to the DAC



void DAConvert(byte sample)
{
  PORTB = sample;
}

void setup()
{
  Serial.begin(9600);
  DDRB = B111111;
}


void loop()
{
  DAConvert(sampleOut); //send the sample to the DAC
  sampleOut++;
  //Serial.print(sampleIn);
  //Serial.print(' ');
  //Serial.println(int(sampleOut));
  //delay(100);
  delayMicroseconds(100); //it takes 100 microseconds to sample
}

