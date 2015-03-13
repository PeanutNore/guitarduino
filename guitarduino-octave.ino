

const int signalPin = A0; //establish pin 0 as the analog input

int sampleIn = 0; //sets up a variable to store the sample
byte sampleOut = 0; //sets up a variable to convert the sample to 6 bits

void DAConvert(byte sample);//sends a 6 bit sample to the DAC

void DAConvert(byte sample)
{
  PORTB = sample;
}

void setup()
{
  //Serial.begin(9600);
  DDRB = B111111;
}

void loop()
{
  sampleIn = analogRead(signalPin); //sample the input
  sampleIn = map(sampleIn, 0, 1023, -512, 511); //center the sample around 0
  sampleIn = abs(sampleIn); //make negative samples positive. Doubles the frequency of the waveform
  sampleOut = map(sampleIn, 0, 512, 0, 63); //convert the sample to 6 bits
  DAConvert(sampleOut); //send the sample to the DAC
  delayMicroseconds(80); //it takes 100 microseconds to sample
}
