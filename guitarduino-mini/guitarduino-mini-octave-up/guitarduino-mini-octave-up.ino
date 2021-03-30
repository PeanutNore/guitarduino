const int inputPin = A3; //establish pin 3 (pin 2 of the DIP) as the analog input
const int outputPin = 1; //establish pin 1 (pin 6 of the DIP) as the output
unsigned int sampleIn = 0; //Stores the sample from the ADC
int sampleADJ = 0;//Stores a signed version of the sample
unsigned int sampleABS = 0; //Stores the absolute value of the sample

void setup() {
  pinMode (inputPin, INPUT);
  pinMode (outputPin, OUTPUT);
}

void loop() {
  sampleIn = analogRead(inputPin); //sample the input
  sampleADJ = sampleIn - 512; //zero-center the sample
  sampleABS = abs(sampleADJ); //take the absolute value of the sample
  if (sampleABS > 300)
      {
        digitalWrite(outputPin, HIGH);
      }
  if (sampleIn < 300)
      {
        digitalWrite(outputPin, LOW);
      }
}

